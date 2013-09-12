#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager, sf::Vector2u windowSize):
Entity(manager, Entity::EHexagon)
{
	//Initializing physics shape with 6 sided CircleShape
	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(50, 6);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(windowSize.x/2, windowSize.y/2);
	physics_.setShape(shape);
	
	for(unsigned int i=0; i<shape->getPointCount(); i+=2)
	{
		pair<sf::Vector2f, sf::Vector2f> outerEdge(physics_.getGlobalPoint(i), physics_.getGlobalPoint((i+1)%shape->getPointCount()));
		shared_ptr<Paddle> paddle=make_shared<Paddle>(manager_, outerEdge, sf::Vector2f(windowSize.x/2.0, windowSize.y/2.0), 10);
		paddles_.push_back(paddle);
		manager_->push(paddle);
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
		paddle->rotate(angle);
	}
}