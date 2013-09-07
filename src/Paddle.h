#ifndef PADDLE
#define PADDLE

#include "Entity.h"

class Paddle : public Entity
{
public:
	Paddle(shared_ptr<EntityManager> manager, EntityType type);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow &window) override;
private:
};

#endif