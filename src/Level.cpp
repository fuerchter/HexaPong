#include "Level.h"

Level::Level(sf::Vector2u windowSize, sf::Vector2f blockSize, sf::Vector2f blockOffset):
manager_(make_shared<EntityManager>())
{
	shared_ptr<LevelBorder> levelBorder=make_shared<LevelBorder>(manager_, windowSize);
	manager_->push(levelBorder);
	
	placeBlocks(windowSize, blockSize, blockOffset, levelBorder);
	
	shared_ptr<Hexagon> hexagon=make_shared<Hexagon>(manager_, windowSize);
	manager_->push(hexagon);
	
	shared_ptr<Ball> ball=make_shared<Ball>(manager_);
	manager_->push(ball);
}

void Level::placeBlocks(sf::Vector2u windowSize, sf::Vector2f blockSize, sf::Vector2f blockOffset, shared_ptr<LevelBorder> levelBorder)
{
	int blockCount=0;
	Physics borderPhysics=levelBorder->getPhysics();
	for(int point=0; point<borderPhysics.getShape()->getPointCount(); point++)
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
		
		int rowCount=rowLength/(blockSize.y+blockOffset.y);
		for(int row=1; row<=rowCount; row++)
		{
			float rowFactor=(blockSize.y+blockOffset.y)*row;
			
			//Moving along on both inner edges of the triangle with rowFactor steps
			sf::Vector2f firstPosition=colEdge.first+Math::normalize(rowEdge.second-colEdge.first)*rowFactor;
			sf::Vector2f secondPosition=colEdge.second+Math::normalize(rowEdge.second-colEdge.second)*rowFactor;
			
			colVector=secondPosition-firstPosition;
			float colLength=Math::length(colVector);
			colVector=Math::normalize(colVector);
			
			int colCount=colLength/(blockSize.x+blockOffset.x);
			
			for(int col=1; col<=colCount; col++)
			{
				float colFactor=(blockSize.x+blockOffset.x)*col;
				
				sf::Vector2f finalPosition=firstPosition+colVector*colFactor;
				
				blockCount++;
				shared_ptr<Block> block=make_shared<Block>(manager_, finalPosition, angle, sf::Vector2f(blockSize.x, blockSize.y));
				manager_->push(block);
			}
		}
	}
	cout << blockCount << endl;
}

void Level::update(float deltaTime)
{
	manager_->update(deltaTime);
}
void Level::draw(sf::RenderWindow &window)
{
	manager_->draw(window);
}