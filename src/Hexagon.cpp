#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager, sf::Vector2u windowSize):
Entity(manager, Entity::EHexagon)
{
	//Initializing physics shape with 6 sided CircleShape
	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(50, 6);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(windowSize.x/2, windowSize.y/2);
	physics_.setShape(shape);
}

void Hexagon::update(float deltaTime)
{
	shared_ptr<sf::Shape> physicsShape=physics_.getShape();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		physicsShape->rotate(-50*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		physicsShape->rotate(50*deltaTime);
	}
}