#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager, EntityType type):
Entity(manager, type)
{
	physics_.createCircleShape(6);
	physics_.uniformScale(100);
}

void Hexagon::update(float deltaTime)
{
	physics_.rotate(20*deltaTime);
	//cout << "I'M A HEXAGON" << endl;
}