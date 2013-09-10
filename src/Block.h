#ifndef BLOCK
#define BLOCK

#include "Entity.h"

class Block : public Entity
{
public:
	Block(shared_ptr<EntityManager> manager, sf::Vector2f position, float rotation, sf::Vector2f size);
private:
};

#endif