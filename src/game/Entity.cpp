#include "Entity.h"

Entity::Entity(shared_ptr<EntityManager> manager, EntityType type)
{
	manager_=manager;
	id_=Entity::ID_NOT_REGISTERED;
	type_=type;
}

void Entity::setId(int id)
{
	id_=id;
}

int Entity::getId()
{
	return id_;
}

EntityType Entity::getType()
{
	return type_;
}

Physics Entity::getPhysics()
{
	return physics_;
}

void Entity::draw(sf::RenderWindow &window)
{
	physics_.draw(window);
}