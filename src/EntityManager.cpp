#include "EntityManager.h"

void EntityManager::update(float deltaTime)
{
	for(auto entity : entities_)
	{
		entity->update(deltaTime);
	}
}

void EntityManager::draw(sf::RenderWindow &window)
{
	for(auto entity : entities_)
	{
		entity->draw(window);
	}
}

void EntityManager::push(shared_ptr<Entity> entity)
{
	entities_.push_back(entity);
}