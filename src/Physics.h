#ifndef PHYSICS
#define PHYSICS

#include <memory>
#include <iostream>
using namespace std;

#include <cmath>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

#include "Math.h"

class Physics
{
public:
	void setDirection(sf::Vector2f direction);
	void setSpeed(float speed);
	void setShape(shared_ptr<sf::Shape> shape);
	shared_ptr<sf::Shape> getShape();
	
	//Collision of my rectangle with other rectangle
	bool rectsOverlap(Physics physics);
	//Returns whether my rect collides with any other line, the corresponding line is returned
	sf::Vector2f rectOverlapsLines(Physics physics);
	
	sf::Vector2f getGlobalPoint(unsigned int index);
	
	void reflect(sf::Vector2f other);
	
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
private:	
	sf::Vector2f direction_;
	float speed_;
	shared_ptr<sf::Shape> shape_;
};

#endif