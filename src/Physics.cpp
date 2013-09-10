#include "Physics.h"

void Physics::setDirection(sf::Vector2f direction)
{
	direction_=normalize(direction);
}

void Physics::setSpeed(float speed)
{
	speed_=speed;
}

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

sf::Vector2f Physics::rectOverlapsLines(Physics physics)
{
	sf::FloatRect myRect=shape_->getGlobalBounds();
	
	int otherPointCount=physics.getShape()->getPointCount();
	
	//Get all lines of the other shape
	for(int i=0; i<otherPointCount; i++)
	{
		//cout << "Line no: " << i << endl;
		pair<sf::Vector2f, sf::Vector2f> otherLine;
		otherLine.first=physics.getGlobalPoint(i);
		otherLine.second=physics.getGlobalPoint((i+1)%otherPointCount);
		
		//If any of them intersects with myRect save the intersected vector
		if(lineOverlapsRect(otherLine, myRect))
		{
			//cout << otherLine.first.x << " " << otherLine.first.y << " " << otherLine.second.x << " " << otherLine.second.y << endl;
			return normalize(sf::Vector2f(otherLine.first.x-otherLine.second.x, otherLine.first.y-otherLine.second.y));
		}
	}
	return sf::Vector2f();
}

sf::Vector2f Physics::getGlobalPoint(unsigned int index)
{
	sf::Vector2f res=shape_->getPoint(index);
	sf::Transform transform=shape_->getTransform();
	res=transform.transformPoint(res);
	return res;
}

void Physics::reflect(sf::Vector2f other)
{
	//Normal has to point out of the shape?
	sf::Vector2f normal=orthogonal(other);
	//cout << other.x << " " << other.y << " " << normal.x << " " << normal.y << endl;
	sf::Vector2f newDirection=direction_-2*(dot(direction_, other))*other;
	//cout << direction_.x << " " << direction_.y << " " << other.x << " " << other.y << " " << newDirection.x << " " << newDirection.y << endl;
	direction_=-newDirection;
}

void Physics::update(float deltaTime)
{
	shape_->move(direction_.x*speed_*deltaTime, direction_.y*speed_*deltaTime);
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

float Physics::length(sf::Vector2f vector)
{
	return sqrt(vector.x*vector.x+vector.y*vector.y);
}

sf::Vector2f Physics::normalize(sf::Vector2f vector)
{
	float divisor=length(vector);
	vector.x/=divisor;
	vector.y/=divisor;
	return vector;
}

float Physics::dot(sf::Vector2f first, sf::Vector2f second)
{
	return first.x*second.x+first.y*second.y;
}

sf::Vector2f Physics::orthogonal(sf::Vector2f vector)
{
	sf::Vector2f res;
	if(vector.x==0 && vector.y==0)
	{
		
	}
	else
	{
		res.x=-vector.y;
		res.y=vector.x;
	}
	/*else if(vector.x==0)
	{
		res.y=1;
	}
	else if(vector.y==0)
	{
		res.x=1;
	}
	else
	{
		res.x=1;
		res.y=vector.x/-vector.y;
		res=normalize(res);
	}*/
	return res;
}