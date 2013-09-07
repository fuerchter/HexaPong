#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager, EntityType type):
Entity(manager, type)
{

}

void Hexagon::update(float deltaTime)
{
	/*if(type_==Entity::Hexagon)
	{
		cout << "BLA" << endl;
	}
	else
	{
		cout << "UUUU" << endl;
	}*/
}

void Hexagon::draw(sf::RenderWindow &window)
{
	/*sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
	window.draw(shape);*/
}