#include "EntityManager.h"

EntityManager::EntityManager(sf::Vector2u windowSize):
windowSize_(windowSize), done_(false)
{
	
}

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
		if(entities_[i])
		{
			//cout << i << " " << entities_.size() << endl;
			entities_[i]->getPhysics().update(deltaTime);
			
			//Check physics of current entity against physics of all the others
			Physics myPhysics=entities_[i]->getPhysics();
			for(unsigned int j=0; j<entities_.size(); j++)
			{
				if(entities_[j] && i!=j)
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
}

void EntityManager::updateEntities(float deltaTime)
{
	for(auto entity : entities_)
	{
		if(entity)
		{
			entity->update(deltaTime);
		}
	}
}

void EntityManager::removeEntities()
{
	for(auto id : marked_)
	{
		entities_[id].reset();
	}
	marked_.clear();
}

void EntityManager::draw(sf::RenderWindow &window)
{
	for(auto entity : entities_)
	{
		if(entity)
		{
			entity->draw(window);
		}
	}
}

void EntityManager::push(shared_ptr<Entity> entity)
{
	entity->setId(size());
	entities_.push_back(entity);
}

void EntityManager::remove(int id)
{
	if(id != Entity::ID_NOT_REGISTERED)
	{
		marked_.push_back(id);
	}
}

unsigned int EntityManager::size()
{
	return entities_.size();
}

sf::Vector2u EntityManager::getWindowSize()
{
	return windowSize_;
}

void EntityManager::setDone(bool done)
{
	done_=done;
}

bool EntityManager::getDone()
{
	return done_;
}

vector<shared_ptr<Entity>> EntityManager::getEntities(EntityType type)
{
	vector<shared_ptr<Entity>> res;
	for(unsigned int i=0; i<entities_.size(); i++)
	{
		if(entities_[i] && entities_[i]->getType()==type)
		{
			res.push_back(entities_[i]);
		}
	}
	return res;
}