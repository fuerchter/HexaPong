#ifndef ENTITY
#define ENTITY

#include "EntityManager.h"
#include "Physics.h"

#include "SFML/Graphics.hpp"

class EntityManager;

class Entity
{
public:
	enum EntityType
	{
		None,
		Hexagon,
		//Paddle
	};
	Entity(shared_ptr<EntityManager> manager, EntityType type, Physics physics);
	virtual void update(float deltaTime)
	{
	
	}
	virtual void draw(sf::RenderWindow &window);
protected:
	shared_ptr<EntityManager> manager_;
	EntityType type_;
	Physics physics_;
private:
	
};

#endif