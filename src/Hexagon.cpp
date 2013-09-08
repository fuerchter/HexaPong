#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager, EntityType type, Physics physics):
Entity(manager, type, physics)
{
	physics_.uniformScale(100);
}

void Hexagon::update(float deltaTime)
{
	physics_.rotate(20*deltaTime);
	//cout << "I'M A HEXAGON" << endl;
}

void Hexagon::draw(sf::RenderWindow &window)
{
	Entity::draw(window);
}