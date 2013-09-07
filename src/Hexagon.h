#ifndef HEXAGON
#define HEXAGON

#include <iostream>
using namespace std;

#include "Entity.h"

class Hexagon : public Entity
{
public:
	Hexagon(EntityManager &manager, EntityType type);
	virtual void update(float deltaTime) override;
	virtual void draw(sf::RenderWindow &window) override;
private:
};

#endif