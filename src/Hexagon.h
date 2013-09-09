#ifndef HEXAGON
#define HEXAGON

#include <memory>
#include <iostream>
using namespace std;

#include "Entity.h"

class Hexagon : public Entity
{
public:
	Hexagon(shared_ptr<EntityManager> manager, EntityType type);
	virtual void update(float deltaTime) override;
private:
};

#endif