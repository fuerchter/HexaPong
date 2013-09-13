#include "Ball.h"

Ball::Ball(shared_ptr<EntityManager> manager):
Entity(manager, EntityType::EBall)
{	

	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(5);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	
	//Endless
	/*physics_.setDirection(sf::Vector2f(20, 0.5));
	physics_.setSpeed(120);
	shape->setPosition(500, 200);*/
	//Corner Glitch
	/*physics_.setDirection(sf::Vector2f(-20, 10));
	physics_.setSpeed(30);
	shape->setPosition(500, 340);*/
	
	physics_.setDirection(sf::Vector2f(20, 0));
	physics_.setSpeed(120);
	shape->setPosition(500, 350);
	shape->setFillColor(sf::Color(255, 109, 37));
	//shape->setFillColor(sf::Color::Black);
	physics_.setShape(shape);
}

void Ball::update(float deltaTime)
{
	//only the things that have to be updated but don't need the physics happen here
	//e.g. animation-stuff
}

void Ball::onCollision(sf::Vector2f lineIntersection, shared_ptr<Entity> collider)
{
	bool towards = physics_.movingTowards(collider->getPhysics());
	
	if(lineIntersection!=sf::Vector2f())
	{
		switch(collider->getType())
		{
			case EntityType::EHexagon:
			{
				manager_->setDone(true);
				break;
			}
			case EntityType::ELevelBorder:
			{
				//LevelBorder will reflect it towards the Hexagon
				sf::Vector2f ownPosition=physics_.getShape()->getPosition();
				sf::Vector2f midScreen(manager_->getWindowSize().x/2.0, manager_->getWindowSize().y/2.0);
				physics_.setDirection(midScreen-ownPosition);
				break;
			}
			case EntityType::EBlock:
			{
				if(towards)
				{
					physics_.reflect(lineIntersection);
				}
				static_pointer_cast<Block>(collider)->remove();
				manager_->remove(collider->getId());
				break;
			}
			case EntityType::EItem:
			{
				break;
			}
			default:
			{
				if(towards)
				{
					physics_.reflect(lineIntersection);
				}
				break;
			}
		}
	}
}