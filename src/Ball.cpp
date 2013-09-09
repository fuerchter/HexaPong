#include "Ball.h"

Ball::Ball(shared_ptr<EntityManager> manager):
Entity(manager, Entity::EBall)
{
	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(5);
	sf::FloatRect bounds=shape->getLocalBounds();
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(700, 400);
	physics_.setShape(shape);
}

void Ball::update(float deltaTime)
{
	shared_ptr<sf::Shape> physicsShape=physics_.getShape();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		physicsShape->move(0, -40*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		physicsShape->move(0, 40*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		physicsShape->move(-40*deltaTime, 0);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		physicsShape->move(40*deltaTime, 0);
	}
}