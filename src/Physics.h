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
	//Has to be called on construction
	void setShape(shared_ptr<sf::Shape> shape);
	shared_ptr<sf::Shape> getShape();
	
	//Collision functions
	//my rectangle/other rectangle
	bool rectsOverlap(Physics physics);
	//my rectangle/any other line (corresponding line is returned)
	sf::Vector2f rectOverlapsLines(Physics physics);
	void reflect(sf::Vector2f other);
	bool movingTowards(Physics physics);
	
	sf::Vector2f getGlobalPoint(unsigned int index);
	
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
private:	
	sf::Vector2f direction_;
	float speed_;
	shared_ptr<sf::Shape> shape_;
};

#endif