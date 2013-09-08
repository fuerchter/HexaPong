#ifndef HEXAGON
#define HEXAGON

#include <memory>
#include <iostream>
using namespace std;

#include "Entity.h"
#include "Paddle.h"

class Hexagon : public Entity
{
public:
	Hexagon(shared_ptr<EntityManager> manager, EntityType type, Physics physics);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow &window) override;
private:
	//shared_ptr<Paddle> test_;
};

#endif