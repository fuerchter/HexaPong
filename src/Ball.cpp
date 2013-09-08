#include "Ball.h"

Ball::Ball(shared_ptr<EntityManager> manager, EntityType type, Physics physics):
Entity(manager, type, physics)
{

}

void Ball::update(float deltaTime)
{
	//cout << "I'M A BALL" << endl;
}

void Ball::draw(sf::RenderWindow &window)
{
	Entity::draw(window);
}