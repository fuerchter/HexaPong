#include "Level.h"

Level::Level(sf::Vector2u windowSize, sf::Vector2f blockSize, sf::Vector2f blockOffset):
manager_(make_shared<EntityManager>(windowSize))
{
	file<> xmlFile("assets/levels/level.xml");
	xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	
	xml_node<> *triangle=doc.first_node()->first_node();
	vector<string> triangles;
	while(triangle)
	{
		string triangleData=triangle->first_attribute()->value();
		triangles.push_back(triangleData);
		triangle=triangle->next_sibling();
	}

	shared_ptr<LevelBorder> levelBorder=make_shared<LevelBorder>(manager_);
	manager_->push(levelBorder);
	
	shared_ptr<Hexagon> hexagon=make_shared<Hexagon>(manager_);
	manager_->push(hexagon);
	
	shared_ptr<sf::CircleShape> hexagonShape=static_pointer_cast<sf::CircleShape>(hexagon->getPhysics().getShape());
	vector<int> colCounts;
	colCounts.push_back(12);
	colCounts.push_back(16);
	colCounts.push_back(32);
	colCounts.push_back(48);
	placeBlocks(windowSize, hexagonShape->getRadius(), sf::Vector2f(20, 10), colCounts);
	
	shared_ptr<Ball> ball=make_shared<Ball>(manager_);
	manager_->push(ball);
}

int Level::oldPlaceBlocks(sf::Vector2u windowSize, sf::Vector2f blockSize, sf::Vector2f blockOffset, shared_ptr<LevelBorder> levelBorder, vector<string> triangles)
{
	int blockCount=0;
	Physics borderPhysics=levelBorder->getPhysics();
	for(unsigned int point=0; point<borderPhysics.getShape()->getPointCount(); point++)
	{
		//The two points at the outside of the LevelBorder
		pair<sf::Vector2f, sf::Vector2f> colEdge(borderPhysics.getGlobalPoint(point), borderPhysics.getGlobalPoint((point+1)%borderPhysics.getShape()->getPointCount()));
		
		sf::Vector2f colVector=colEdge.second-colEdge.first;
		
		//The middle of colEdge and the middle of the screen
		pair<sf::Vector2f, sf::Vector2f> rowEdge(sf::Vector2f(colVector.x/2, colVector.y/2)+colEdge.first, sf::Vector2f(windowSize.x/2, windowSize.y/2));
		
		sf::Vector2f rowVector=rowEdge.second-rowEdge.first;
		float rowLength=Math::length(rowVector)*1/2; //Arbitrary factor, otherwise blocks might spawn inside the hexagon
		
		colVector=Math::normalize(colVector);
		rowVector=Math::normalize(rowVector);
		
		float angle=0;
		if(point<borderPhysics.getShape()->getPointCount()/2)
		{
			angle=Math::angle(sf::Vector2f(1, 0), colVector);
		}
		else
		{
			angle=Math::angle(sf::Vector2f(-1, 0), colVector);
		}
		//cout << angle << endl;
		
		unsigned int blockCountTriangle=0;
		int rowCount=rowLength/(blockSize.y+blockOffset.y);
		for(int row=0; row<rowCount; row++)
		{
			float rowFactor=(blockSize.y+blockOffset.y)*row;
			
			//Moving along on both inner edges of the triangle with rowFactor steps
			sf::Vector2f firstPosition=colEdge.first+Math::normalize(rowEdge.second-colEdge.first)*rowFactor;
			sf::Vector2f secondPosition=colEdge.second+Math::normalize(rowEdge.second-colEdge.second)*rowFactor;
			
			colVector=secondPosition-firstPosition;
			float colLength=Math::length(colVector);
			colVector=Math::normalize(colVector);
			
			int colCount=colLength/(blockSize.x+blockOffset.x);
			
			for(int col=0; col<colCount; col++)
			{
				float colFactor=(blockSize.x+blockOffset.x)*col;
				
				sf::Vector2f finalPosition=firstPosition+colVector*colFactor;
				
				blockCountTriangle++;
				ItemType type=ItemType::INone;
				if(point<triangles.size() && blockCountTriangle<triangles[point].size())
				{
					type=(ItemType)(triangles[point][blockCountTriangle]-'0');
				}
				shared_ptr<Block> block=make_shared<Block>(manager_, finalPosition, angle, sf::Vector2f(blockSize.x, blockSize.y), type);
				manager_->push(block);
			}
		}
		blockCount+=blockCountTriangle;
	}
	return blockCount;
}

void Level::placeBlocks(sf::Vector2u windowSize, float hexagonRadius, sf::Vector2f blockSize, vector<int> colCounts)
{
	sf::Vector2f midScreen(windowSize.x/2.0, windowSize.y/2.0);	
	float startDistance=hexagonRadius*3;
	//offset between each row
	float offsetHeight=(midScreen.y-startDistance-blockSize.y*colCounts.size())/colCounts.size();
	
	for(unsigned int y=0; y<colCounts.size(); y++)
	{
		//offset between each col
		float offsetAngle=360.0/colCounts[y];
		float totalDistance=startDistance+y*offsetHeight;
		
		for(int x=0; x<colCounts[y]; x++)
		{
			float finalAngle=x*offsetAngle;
			sf::Vector2f rotatedVector=Math::rotate(sf::Vector2f(0, -1), finalAngle);
			sf::Vector2f finalPosition(midScreen+rotatedVector*totalDistance);
			
			shared_ptr<Block> block=make_shared<Block>(manager_, finalPosition, finalAngle, sf::Vector2f(blockSize.x, blockSize.y));
			manager_->push(block);
		}
	}
}

void Level::update(float deltaTime)
{
	if(manager_)
	{
		manager_->update(deltaTime);
		if(manager_->getEntities(EntityType::EBlock).empty())
		{
			//cout << "You Win" << endl;
		}
		if(manager_->getDone())
		{
			manager_.reset();
		}
	}
	else
	{
		//cout << "Game Over" << endl;
	}
}
void Level::draw(sf::RenderWindow &window)
{
	if(manager_)
	{
		manager_->draw(window);
	}
}