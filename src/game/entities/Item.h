#ifndef ITEM
#define ITEM

#include "../Entity.h"
#include "../ItemType.h"
#include "Hexagon.h"

class Item : public Entity
{
public:
	Item(shared_ptr<EntityManager> manager, ItemType type, sf::Vector2f position, sf::Vector2f direction);
	virtual void onCollision(sf::Vector2f lineIntersection, shared_ptr<Entity> collider) override;
private:
	ItemType type_;
};

#endif