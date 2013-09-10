#ifndef PHYSICS
#define PHYSICS

#include <utility>
#include <memory>
#include <iostream>
using namespace std;

#include <cmath>

#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"

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
	//Returns tLine and tEdge as pair, edge is either horizontal or vertical
	pair<float, float> lineIntersection(pair<sf::Vector2f, sf::Vector2f> line, pair<sf::Vector2f, sf::Vector2f> edge, bool horizontal);
	bool tCheck(pair<float, float> t);
	bool lineOverlapsRect(pair<sf::Vector2f, sf::Vector2f> line, sf::FloatRect rect);
	
	//Vector functions
	float length(sf::Vector2f vector);
	sf::Vector2f normalize(sf::Vector2f vector);
	float dot(sf::Vector2f first, sf::Vector2f second);
	sf::Vector2f orthogonal(sf::Vector2f vector);
	
	sf::Vector2f direction_;
	float speed_;
	shared_ptr<sf::Shape> shape_;
};

#endif