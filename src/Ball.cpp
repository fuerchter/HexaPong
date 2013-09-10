#include "Ball.h"

Ball::Ball(shared_ptr<EntityManager> manager):
Entity(manager, Entity::EBall)
{	

	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(5);
	sf::FloatRect bounds=shape->getLocalBounds();
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	
	//Endless
	/*physics_.setDirection(sf::Vector2f(20, 0.5));
	physics_.setSpeed(120);
	shape->setPosition(500, 200);*/
	//Corner Glitch
	/*physics_.setDirection(sf::Vector2f(20, 5));
	physics_.setSpeed(30);
	shape->setPosition(500, 350);*/
	
	physics_.setDirection(sf::Vector2f(20, 0));
	physics_.setSpeed(120);
	shape->setPosition(500, 350);
	
	shape->setFillColor(sf::Color::Red);
	physics_.setShape(shape);
}

void Ball::update(float deltaTime)
{
	Entity::update(deltaTime);
}

void Ball::onCollision(sf::Vector2f lineIntersection)
{
	if(lineIntersection!=sf::Vector2f())
	{
		//cout << lineIntersection.x << " " << lineIntersection.y << endl;
		physics_.reflect(lineIntersection);
	}
}