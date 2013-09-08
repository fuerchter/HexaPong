#ifndef PHYSICS
#define PHYSICS

#include <iostream>
using namespace std;

#include <cmath>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class Physics
{
public:
	void createCircleShape(int pointCount);
	void uniformScale(float factor);
	void rotate(float offset);
	void draw(sf::RenderWindow &window);
private:
	sf::Vector2f velocity_;
	sf::ConvexShape convexShape_;
};

#endif