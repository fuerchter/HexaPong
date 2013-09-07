#ifndef ENTITY
#define ENTITY

#include "EntityManager.h"

#include "SFML/Graphics.hpp"

class EntityManager;

class Entity
{
public:
	enum EntityType
	{
		None,
		Hexagon
	};
	Entity(shared_ptr<EntityManager> manager, EntityType type);
	virtual void update(float deltaTime)
	{
	
	}
	virtual void draw(sf::RenderWindow &window)
	{
	
	}
protected:
	EntityType type_;
	shared_ptr<EntityManager> manager_;
private:
	
};

#endif