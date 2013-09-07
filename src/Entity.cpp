#include "Entity.h"

Entity::Entity(EntityManager &manager, EntityType type)
{
	manager.push(shared_ptr<Entity>(this));
	manager_=make_shared<EntityManager>(manager);
	type_=type;
}