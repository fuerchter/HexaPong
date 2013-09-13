#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

#include "SFML/Graphics.hpp"

#include "EntityType.h"
#include "Entity.h"

class Entity;

class EntityManager
{
public:
	EntityManager(sf::Vector2u windowSize);
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void push(shared_ptr<Entity> entity);
	void remove(int id);
	unsigned int size();
	sf::Vector2u getWindowSize();
	void setDone(bool done);
	bool getDone();
	vector<shared_ptr<Entity>> getEntities(EntityType type);
private:
	void updatePhysics(float deltaTime);
	void updateEntities(float deltaTime);
	void removeEntities();
	
	vector<shared_ptr<Entity>> entities_;
	vector<int> marked_;
	sf::Vector2u windowSize_;
	bool done_;
};

#endif