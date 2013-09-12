#include "EntityManager.h"

void EntityManager::update(float deltaTime)
{
	//first calculate the physics
	updatePhysics(deltaTime);
	updateEntities(deltaTime);
	removeEntities();
}

void EntityManager::updatePhysics(float deltaTime)
{
	//if entity i removes another entity it will cause a crash. also should it call both i and j's onCollision once a collision was found?
	for(unsigned int i=0; i<entities_.size(); i++)
	{
		//cout << i << " " << entities_.size() << endl;
		entities_[i]->getPhysics().update(deltaTime);
		
		//Check physics of current entity against physics of all the others
		Physics myPhysics=entities_[i]->getPhysics();
		for(unsigned int j=0; j<entities_.size(); j++)
		{
			if(i!=j)
			{
				Physics otherPhysics=entities_[j]->getPhysics();
				//Only if the rectangles overlap also compute a line/rect intersection
				if(myPhysics.rectsOverlap(otherPhysics))
				{
					sf::Vector2f myIntersection=myPhysics.rectOverlapsLines(otherPhysics);
					entities_[i]->onCollision(myIntersection, entities_[j]);
					//cout << i << " colliding with " << j << endl;
				}
			}
		}
	}
}

void EntityManager::updateEntities(float deltaTime)
{
	for(auto entity : entities_)
	{
		entity->update(deltaTime);
	}
}

void EntityManager::removeEntities()
{
	for(auto entity : marked_)
	{
		entities_.erase(entity);
	}
	marked_.clear();
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

void EntityManager::remove(shared_ptr<Entity> entity)
{
	//Might want to put find into its own function
	auto it=find(entities_.begin(), entities_.end(), entity);
	if(it!=entities_.end())
	{
		marked_.push_back(it);
	}
}