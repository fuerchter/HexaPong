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
	Hexagon(shared_ptr<EntityManager> manager, sf::Vector2u windowSize);
	virtual void update(float deltaTime) override;
	void rotate(float angle);
private:
	vector<shared_ptr<Paddle>> paddles_;
};

#endif