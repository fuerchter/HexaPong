#ifndef BLOCK
#define BLOCK

#include "../Entity.h"
#include "Item.h"

class Block : public Entity
{
public:
	Block(shared_ptr<EntityManager> manager, sf::Vector2f position, float rotation, sf::Vector2f size, ItemType item=ItemType::INone);
	void remove();
private:
	ItemType item_;
};

#endif