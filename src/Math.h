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
	//General functions
	static float toDegree(float radian);
	static float toRadian(float degree);
	static pair<float, float> toSlopeIntercept(sf::Vector2f direction, sf::Vector2f origin);
	
	//Vector functions
	static float length(sf::Vector2f vector);
	static sf::Vector2f normalize(sf::Vector2f vector);
	static float dot(sf::Vector2f first, sf::Vector2f second);
	static float angle(sf::Vector2f first, sf::Vector2f second);
	static sf::Vector2f orthogonal(sf::Vector2f vector);
	static sf::Vector2f reflect(sf::Vector2f first, sf::Vector2f second);
	
	//Collision functions
	static bool lineOverlapsRect(pair<sf::Vector2f, sf::Vector2f> line, sf::FloatRect rect);
	//Intersection of two lines which are defined by two points each
	static pair<float, float> lineIntersection(pair<sf::Vector2f, sf::Vector2f> line, pair<sf::Vector2f, sf::Vector2f> edge, bool horizontal);
	//Intersection of two lines in slopeIntercept notation
	static sf::Vector2f slopeInterceptIntersection(pair<float, float> first, pair<float, float> second);
private:
	static bool tCheck(pair<float, float> t);

	static constexpr float PI=4.0*atan(1.0);
};

#endif