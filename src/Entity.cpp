#include "Entity.h"

Entity::Entity(shared_ptr<EntityManager> manager, EntityType type, Physics physics)
{
	manager_=manager;
	manager->push(shared_ptr<Entity>(this));
	type_=type;
	physics_=physics;
}

void Entity::draw(sf::RenderWindow &window)
{
	physics_.draw(window);
}