#include "Block.h"

Block::Block(shared_ptr<EntityManager> manager, sf::Vector2f position, float rotation, sf::Vector2f size, ItemType item):
Entity(manager, EntityType::EBlock)
{
	shared_ptr<sf::RectangleShape> shape=make_shared<sf::RectangleShape>(size);
	sf::FloatRect bounds=shape->getLocalBounds();
	shape->setOrigin(bounds.width/2, bounds.height/2);
	shape->setPosition(position);
	shape->setRotation(rotation);
	shape->setFillColor(sf::Color(37, 165, 255));
	physics_.setShape(shape);
	
	item_=item;
}

void Block::remove()
{
	switch(item_)
	{
		case ItemType::INone:
			break;
		default:
			sf::Vector2f ownPosition=physics_.getShape()->getPosition();
			sf::Vector2f midScreen(manager_->getWindowSize().x/2.0, manager_->getWindowSize().y/2.0);
			shared_ptr<Item> item=make_shared<Item>(manager_, item_, ownPosition, midScreen-ownPosition);
			manager_->push(item);
			break;
	}
}