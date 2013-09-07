#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager, EntityType type):
Entity(manager, type)
{
}

void Hexagon::update(float deltaTime)
{
	cout << "I'M A HEXAGON" << endl;
}

void Hexagon::draw(sf::RenderWindow &window)
{

}