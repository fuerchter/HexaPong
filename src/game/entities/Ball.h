#ifndef BALL
#define BALL

#include "../Entity.h"
#include "Block.h"

class Ball : public Entity
{
public:
	Ball(shared_ptr<EntityManager> manager);
	virtual void update(float deltaTime) override;
	virtual void onCollision(sf::Vector2f lineIntersection, shared_ptr<Entity> collider) override;
private:
};

#endif