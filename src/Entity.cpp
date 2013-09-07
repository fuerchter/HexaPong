#include "Entity.h"

Entity::Entity(shared_ptr<EntityManager> manager, EntityType type)
{
	manager_=manager;
	manager->push(shared_ptr<Entity>(this));
	type_=type;
}