#include "Entity.h"

Entity::Entity(shared_ptr<EntityManager> manager, EntityType type)
{
	manager_=manager;
	type_=type;
}

Physics Entity::getPhysics()
{
	return physics_;
}

void Entity::update(float deltaTime)
{
	physics_.update(deltaTime);
}

void Entity::draw(sf::RenderWindow &window)
{
	physics_.draw(window);
}