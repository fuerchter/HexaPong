#include "EntityManager.h"

void EntityManager::update(float deltaTime)
{
	for(int i=0; i<entities_.size(); i++)
	{
		entities_[i]->update(deltaTime);
		
		//Check physics of current entity against physics of all the others
		Physics myPhysics=entities_[i]->getPhysics();
		for(int j=0; j<entities_.size(); j++)
		{
			if(i!=j)
			{
				Physics otherPhysics=entities_[j]->getPhysics();
				//Only if the rectangles overlap also compute a line/rect intersection
				if(myPhysics.rectsOverlap(otherPhysics))
				{
					entities_[i]->onCollision(myPhysics.rectOverlapsLines(otherPhysics));
				}
			}
		}
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