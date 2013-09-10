#include "Block.h"

Block::Block(shared_ptr<EntityManager> manager, sf::Vector2f position, float rotation, sf::Vector2f size):
Entity(manager, Entity::EBlock)
{
	shared_ptr<sf::RectangleShape> shape=make_shared<sf::RectangleShape>(size);
	sf::FloatRect bounds=shape->getLocalBounds();
	shape->setOrigin(bounds.width/2, bounds.height/2);
	shape->setPosition(position);
	shape->setRotation(rotation);
	physics_.setShape(shape);
}