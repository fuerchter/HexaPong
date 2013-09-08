#ifndef BALL
#define BALL

#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(shared_ptr<EntityManager> manager, EntityType type, Physics physics);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow &window) override;
private:
};

#endif