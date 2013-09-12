#ifndef ENTITYMANAGER
#define ENTITYMANAGER

#include <algorithm>
#include <memory>
#include <vector>
#include <iostream>
using namespace std;

#include "SFML/Graphics.hpp"

#include "Entity.h"

class Entity;

class EntityManager
{
public:
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
	void push(shared_ptr<Entity> entity);
	void remove(shared_ptr<Entity> entity);
private:
	void updatePhysics(float deltaTime);
	void updateEntities(float deltaTime);
	void removeEntities();
	
	vector<shared_ptr<Entity>> entities_;
	vector<vector<shared_ptr<Entity>>::iterator> marked_;
};

#endif