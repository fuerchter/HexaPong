#include "Item.h"

Item::Item(shared_ptr<EntityManager> manager, ItemType type, sf::Vector2f position, sf::Vector2f direction):
Entity(manager, EntityType::EItem), type_(type)
{
	shared_ptr<sf::RectangleShape> shape=make_shared<sf::RectangleShape>(sf::Vector2f(20, 20));
	sf::FloatRect bounds=shape->getLocalBounds();
	shape->setOrigin(bounds.width/2, bounds.height/2);
	shape->setPosition(position);
	
	switch(type)
	{
		case ItemType::IEnable:
			shape->setFillColor(sf::Color::Green);
			break;
		case ItemType::IDisable:
			shape->setFillColor(sf::Color::Red);
			break;
		default:
			break;
	}
	
	physics_.setShape(shape);
	physics_.setDirection(direction);
	physics_.setSpeed(60);
}

void Item::onCollision(sf::Vector2f lineIntersection, shared_ptr<Entity> collider)
{
	if(lineIntersection!=sf::Vector2f())
	{
		switch(collider->getType())
		{
			case EntityType::EHexagon:
			{
				switch(type_)
				{
					case ItemType::IEnable:
					{
						shared_ptr<Hexagon> hexagon=static_pointer_cast<Hexagon>(collider);
						int paddleIndex=hexagon->getPhysics().getPointFromVector(lineIntersection);
						hexagon->insertPaddle(paddleIndex);
						break;
					}
					default:
					{
						break;
					}
				}
				manager_->remove(id_);
				break;
			}
			case EntityType::EPaddle:
			{
				switch(type_)
				{
					case ItemType::IDisable:
					{
						//Remove the paddle we hit
						shared_ptr<Hexagon> hexagon=static_pointer_cast<Hexagon>(manager_->getEntities(EntityType::EHexagon)[0]);
						int paddleIndex=hexagon->getPhysics().getPointFromVector(lineIntersection);
						hexagon->removePaddle(paddleIndex);
						break;
					}
					default:
					{
						break;
					}
				}
				manager_->remove(id_);
				break;
			}
			default:
			{
				break;
			}
		}
	}
}