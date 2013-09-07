#ifndef ENTITYMANAGER
#define ENTITYMANAGER

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
	//remove
private:
	vector<shared_ptr<Entity>> entities_;
};

#endif