#include "EntityManager.h"

void EntityManager::update(float deltaTime)
{
	int i=0;
	//for(int i=0; i<entities_.size(); i++)
	{
		entities_[i]->update(deltaTime);
		
		Physics myPhysics=entities_[i]->getPhysics();
		int j=1;
		//for(int j=0; j<entities_.size(); j++)
		{
			if(i!=j)
			{
				Physics otherPhysics=entities_[j]->getPhysics();
				cout << myPhysics.rectsOverlap(otherPhysics) << " " << myPhysics.linesOverlap(otherPhysics) << endl;
			}
		}
	}
	entities_[1]->update(deltaTime);
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