#include "LevelBorder.h"

LevelBorder::LevelBorder(shared_ptr<EntityManager> manager, sf::Vector2u windowSize):
Entity(manager, Entity::ELevelBorder)
{
	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(windowSize.y/2, 6);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(windowSize.x/2, windowSize.y/2);
	shape->setFillColor(sf::Color::Green);
	physics_.setShape(shape);
}