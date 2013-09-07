#ifndef PHYSICS
#define PHYSICS

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

class Physics
{
public:

private:
	sf::Vector2f velocity_;
	sf::ConvexShape convexShape_;
};

#endif