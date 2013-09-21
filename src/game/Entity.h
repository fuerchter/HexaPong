#ifndef ENTITY
#define ENTITY

#include "EntityType.h"
#include "EntityManager.h"
#include "../engine/Physics.h"

#include "SFML/Graphics.hpp"

class EntityManager;

class Entity
{
public:
	static const int ID_NOT_REGISTERED = -1;
	Entity(shared_ptr<EntityManager> manager, EntityType type);
	int getId();
	void setId(int id);
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