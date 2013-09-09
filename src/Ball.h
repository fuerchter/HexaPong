#ifndef BALL
#define BALL

#include "Entity.h"

class Ball : public Entity
{
public:
	Ball(shared_ptr<EntityManager> manager);
	virtual void update(float deltaTime) override;
private:
};

#endif