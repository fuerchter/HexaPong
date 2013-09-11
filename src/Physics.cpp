#include "Physics.h"

void Physics::setDirection(sf::Vector2f direction)
{
	direction_=Math::normalize(direction);
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
		if(Math::lineOverlapsRect(otherLine, myRect))
		{
			//cout << otherLine.first.x << " " << otherLine.first.y << " " << otherLine.second.x << " " << otherLine.second.y << endl;
			return Math::normalize(otherLine.first-otherLine.second);
		}
	}
	return sf::Vector2f();
}

void Physics::reflect(sf::Vector2f other)
{
	direction_=Math::reflect(direction_, other);
}

bool Physics::movingTowards(Physics physics)
{
	sf::Vector2f myPosition=shape_->getPosition();
	sf::Vector2f otherPosition=physics.getShape()->getPosition();
	
	//Vector from my midPoint to the other physics object's midPoint
	sf::Vector2f myToOther=Math::normalize(myPosition-otherPosition);
	
	//cout << direction_.x << " " << direction_.y << " " << myToOther.x << " " << myToOther.y << endl;
	float angle=Math::angle(direction_, myToOther);
	//cout << angle << endl;
	return (angle>90 || angle<-90);
}

sf::Vector2f Physics::getGlobalPoint(unsigned int index)
{
	sf::Vector2f res=shape_->getPoint(index);
	sf::Transform transform=shape_->getTransform();
	res=transform.transformPoint(res);
	return res;
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