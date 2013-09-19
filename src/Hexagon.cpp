#include "Hexagon.h"

Hexagon::Hexagon(shared_ptr<EntityManager> manager):
Entity(manager, EntityType::EHexagon)
{
	int pointCount=6;
	sf::Vector2u windowSize=manager_->getWindowSize();
	//Initializing physics shape with 6 sided CircleShape
	shared_ptr<sf::CircleShape> shape=make_shared<sf::CircleShape>(50, pointCount);
	shape->setOrigin(shape->getRadius(), shape->getRadius());
	shape->setPosition(windowSize.x/2, windowSize.y/2);
	shape->setFillColor(sf::Color(255, 109, 37));
	physics_.setShape(shape);
	
	paddles_.resize(pointCount);
	for(int i=0; i<pointCount; i++)
	{
		paddles_.insert(paddles_.begin()+i, shared_ptr<Paddle>());
		//cout << "All paddles initialized to " << !!paddles_[i] << endl;
	}
	
	for(int i=3; i<pointCount; i++)
	{
		insertPaddle(i);
	}
}

void Hexagon::update(float deltaTime)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		rotate(-75*deltaTime);
	}
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		rotate(75*deltaTime);
	}
}

void Hexagon::rotate(float angle)
{
	physics_.getShape()->rotate(angle);
	for(auto paddle : paddles_)
	{
		if(paddle)
		{
			paddle->rotate(angle);
		}
	}
}

void Hexagon::insertPaddle(int index)
{
	//cout << "Adding paddle " << index << " " << !!paddles_[index] << endl;
	int pointCount=physics_.getShape()->getPointCount();
	sf::Vector2u windowSize=manager_->getWindowSize();
	if(!paddles_[index])
	{
		pair<sf::Vector2f, sf::Vector2f> outerEdge(physics_.getGlobalPoint(index), physics_.getGlobalPoint((index+1)%pointCount));
		shared_ptr<Paddle> paddle=make_shared<Paddle>(manager_, index, outerEdge, sf::Vector2f(windowSize.x/2.0, windowSize.y/2.0), 10);
		paddles_[index] = paddle;
		manager_->push(paddle);
		//cout << "My id: " << id_ << " paddle id: " << paddles_[index]->getId() << endl;
	}
	//cout << "Added paddle " << index << " " << !!paddles_[index] << endl;
}

void Hexagon::removePaddle(int index)
{
	//cout << "Removing paddle " << index << " " << !!paddles_[index] << endl;
	if(paddles_[index])
	{
		manager_->remove(paddles_[index]->getId());
		paddles_[index].reset();
	}
	//cout << "Removed paddle " << index << " " << !!paddles_[index] << endl;
}