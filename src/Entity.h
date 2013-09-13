#ifndef ENTITY
#define ENTITY

#include "EntityType.h"
#include "EntityManager.h"
#include "Physics.h"

#include "SFML/Graphics.hpp"

class EntityManager;

class Entity
{
public:
	Entity(shared_ptr<EntityManager> manager, EntityType type);
	int getId();
	EntityType getType();
	Physics getPhysics();
	virtual void update(float deltaTime)
	{
	
	}
	virtual void draw(sf::RenderWindow &window);
	virtual void onCollision(sf::Vector2f lineIntersection, shared_ptr<Entity> collider)
	{
	
	}
protected:
	shared_ptr<EntityManager> manager_;
	int id_;
	EntityType type_;
	Physics physics_;
private:
	
};

#endif