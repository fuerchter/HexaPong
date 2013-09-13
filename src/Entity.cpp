#include "Entity.h"

Entity::Entity(shared_ptr<EntityManager> manager, EntityType type)
{
	manager_=manager;
	id_=manager_->size();
	type_=type;
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