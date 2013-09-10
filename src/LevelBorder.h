#ifndef LEVELBORDER
#define LEVELBORDER

#include "Entity.h"

class LevelBorder : public Entity
{
public:
	LevelBorder(shared_ptr<EntityManager> manager, sf::Vector2u windowSize);
private:
};

#endif