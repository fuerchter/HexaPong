#include "Physics.h"

void Physics::createCircleShape(int pointCount)
{
	convexShape_=sf::ConvexShape();
	convexShape_.setPointCount(pointCount);
	float offsets=360.0/pointCount;
	for(int i=0; i<pointCount; i++)
	{
		float toRadian=4*atan(1)/180;
		sf::Vector2f finalPosition;
		finalPosition.x=cos((i*offsets)*toRadian);
		finalPosition.y=sin((i*offsets)*toRadian);
		convexShape_.setPoint(i, finalPosition);
	}
	
	convexShape_.setOutlineColor(sf::Color::Red);
	convexShape_.setOutlineThickness(3);
	convexShape_.setPosition(100, 100);
	convexShape_.setFillColor(sf::Color::Transparent);
}

void Physics::uniformScale(float factor)
{
	for(int i=0; i<convexShape_.getPointCount(); i++)
	{
		sf::Vector2f newPos=convexShape_.getPoint(i);
		newPos.x*=factor;
		newPos.y*=factor;
		convexShape_.setPoint(i, newPos);
	}
}

void Physics::rotate(float offset)
{
	for(int i=0; i<convexShape_.getPointCount(); i++)
	{
		sf::Vector2f oldPos=convexShape_.getPoint(i);
		sf::Vector2f newPos;
		newPos.x=oldPos.x*cos(offset*4*atan(1)/180)+oldPos.y*-sin(offset*4*atan(1)/180);
		newPos.y=oldPos.x*sin(offset*4*atan(1)/180)+oldPos.y*cos(offset*4*atan(1)/180);
		convexShape_.setPoint(i, newPos);
	}
}

void Physics::draw(sf::RenderWindow &window)
{
	window.draw(convexShape_);
}