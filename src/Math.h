#ifndef MATH
#define MATH

#include <iostream>
#include <utility>
using namespace std;

#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"

class Math
{
public:
	//Vector functions
	static float length(sf::Vector2f vector);
	static sf::Vector2f normalize(sf::Vector2f vector);
	static float dot(sf::Vector2f first, sf::Vector2f second);
	static sf::Vector2f orthogonal(sf::Vector2f vector);
	static sf::Vector2f reflect(sf::Vector2f first, sf::Vector2f second);
	
	//Collision functions
	static bool lineOverlapsRect(pair<sf::Vector2f, sf::Vector2f> line, sf::FloatRect rect);
	static pair<float, float> lineIntersection(pair<sf::Vector2f, sf::Vector2f> line, pair<sf::Vector2f, sf::Vector2f> edge, bool horizontal);
	static bool tCheck(pair<float, float> t);
private:
};

#endif