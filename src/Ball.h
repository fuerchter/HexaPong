#ifndef BALL
#define BALL

#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(shared_ptr<EntityManager> manager);
	virtual void update(float deltaTime) override;
	virtual void onCollision(sf::Vector2f lineIntersection) override;
private:
};

#endif