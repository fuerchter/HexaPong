#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager):
Entity(manager, EntityType::EHexagon)
{
	int pointCount=6;
	sf::Vector2u windowSize=manager_->getWindowSize();
	//Initializing physics shape with 6 sided CircleShape
	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(50, pointCount);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(windowSize.x/2, windowSize.y/2);
	shape->setFillColor(sf::Color(255, 109, 37));
	physics_.setShape(shape);
	
	paddles_.resize(pointCount);
	for(int i=0; i<pointCount; i+=2)
	{
		insertPaddle(i);
	}
}

void Hexagon::update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotate(-50*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotate(50*deltaTime);
	}
}

void Hexagon::rotate(float angle)
{
	physics_.getShape()->rotate(angle);
	for(auto paddle : paddles_)
	{
		if(paddle)
		{
			paddle->rotate(angle);
		}
	}
}

void Hexagon::insertPaddle(int index)
{
	int pointCount=physics_.getShape()->getPointCount();
	sf::Vector2u windowSize=manager_->getWindowSize();
	if(!paddles_[index])
	{
		pair<sf::Vector2f, sf::Vector2f> outerEdge(physics_.getGlobalPoint(index), physics_.getGlobalPoint((index+1)%pointCount));
		shared_ptr<Paddle> paddle=make_shared<Paddle>(manager_, outerEdge, sf::Vector2f(windowSize.x/2.0, windowSize.y/2.0), 10);
		paddles_.insert(paddles_.begin()+index, paddle);
		manager_->push(paddle);
	}
}

void Hexagon::removePaddle(int index)
{
	if(paddles_[index])
	{
		manager_->remove(paddles_[index]->getId());
		paddles_[index].reset();
	}
}