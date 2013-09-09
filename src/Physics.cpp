#include "Physics.h"

void Physics::setShape(shared_ptr<sf::Shape> shape)
{
	shape_=shape;
}

shared_ptr<sf::Shape> Physics::getShape()
{
	return shape_;
}

bool Physics::rectsOverlap(Physics physics)
{
	sf::FloatRect myRect=shape_->getGlobalBounds();
	sf::FloatRect otherRect=physics.getShape()->getGlobalBounds();
	return myRect.intersects(otherRect);
}

bool Physics::linesOverlap(Physics physics)
{
	sf::FloatRect rect=physics.getShape()->getGlobalBounds();
	
	//Get all lines of the current shape
	for(int i=0; i<shape_->getPointCount(); i++)
	{
		//cout << "Line no: " << i << endl;
		pair<sf::Vector2f, sf::Vector2f> line;
		line.first=getGlobalPoint(i);
		line.second=getGlobalPoint((i+1)%shape_->getPointCount());
		
		if(lineOverlapsRect(line, rect))
		{
			intersectedLine_=line;
			return true;
		}
	}
	return false;
}

sf::Vector2f Physics::getGlobalPoint(unsigned int index)
{
	sf::Vector2f res=shape_->getPoint(index);
	sf::Transform transform=shape_->getTransform();
	res=transform.transformPoint(res);
	return res;
}

void Physics::draw(sf::RenderWindow &window)
{
	if(shape_)
	{
		window.draw(*shape_);
	}
}

pair<float, float> Physics::lineIntersection(pair<sf::Vector2f, sf::Vector2f> line, pair<sf::Vector2f, sf::Vector2f> edge, bool horizontal)
{
	//Implementation of (1-tLine)*lineStart+tLine*lineEnd=(1-tEdge)*edgeStart+tEdge*edgeEnd
	pair<float, float> t;
	if(horizontal)
	{
		t.first=(edge.first.y-line.first.y)/(line.second.y-line.first.y);
		t.second=(line.first.x-edge.first.x+t.first*(line.second.x-line.first.x))/(edge.second.x-edge.first.x);
	}
	else
	{
		t.first=(edge.first.x-line.first.x)/(line.second.x-line.first.x);
		t.second=(line.first.y-edge.first.y+t.first*(line.second.y-line.first.y))/(edge.second.y-edge.first.y);
	}
	return t;
}

bool Physics::tCheck(pair<float, float> t)
{
	return (t.first>=0 && t.first<=1 && t.second>=0 && t.second<=1);
}

bool Physics::lineOverlapsRect(pair<sf::Vector2f, sf::Vector2f> line, sf::FloatRect rect)
{
	pair<sf::Vector2f, sf::Vector2f> edge;
	pair<float, float> t;
	
	//Test with top edge
	edge.first.x=rect.left;
	edge.first.y=rect.top;
	edge.second.x=rect.left+rect.width;
	edge.second.y=rect.top;
	
	t=lineIntersection(line, edge, true);

	if(tCheck(t))
	{
		return true;
	}
	//cout << "Top edge " << t.first << " " << t.second << endl;
	
	//Test with bottom edge
	edge.first.x=rect.left;
	edge.first.y=rect.top+rect.height;
	edge.second.x=rect.left+rect.width;
	edge.second.y=rect.top+rect.height;
	
	t=lineIntersection(line, edge, true);
	
	if(tCheck(t))
	{
		return true;
	}
	//cout << "Bottom edge " << t.first << " " << t.second << endl;
	
	//Test with left edge
	edge.first.x=rect.left;
	edge.first.y=rect.top;
	edge.second.x=rect.left;
	edge.second.y=rect.top+rect.height;
	
	t=lineIntersection(line, edge, false);
	
	if(tCheck(t))
	{
		return true;
	}
	//cout << "Left edge " << t.first << " " << t.second << endl;
	
	//Test with right edge
	edge.first.x=rect.left+rect.width;
	edge.first.y=rect.top;
	edge.second.x=rect.left+rect.width;
	edge.second.y=rect.top+rect.height;
	
	t=lineIntersection(line, edge, false);
	
	if(tCheck(t))
	{
		return true;
	}
	
	return false;
	//cout << "Right edge " << t.first << " " << t.second << endl;
}