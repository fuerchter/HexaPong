#include "Paddle.h"

Paddle::Paddle(shared_ptr<EntityManager> manager, EntityType type):
Entity(manager, type)
{
	
}

void Paddle::update(float deltaTime)
{
	cout << "I'M A PADDLE" << endl;
}

void Paddle::draw(sf::RenderWindow &window)
{

}