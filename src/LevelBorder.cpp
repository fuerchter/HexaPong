#include "LevelBorder.h"

LevelBorder::LevelBorder(shared_ptr<EntityManager> manager):
Entity(manager, EntityType::ELevelBorder)
{
	sf::Vector2u windowSize=manager->getWindowSize();
	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(windowSize.y/2, 6);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(windowSize.x/2, windowSize.y/2);
	shape->setFillColor(sf::Color::White);
	physics_.setShape(shape);
}