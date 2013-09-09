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
	void setShape(shared_ptr<sf::Shape> shape);
	shared_ptr<sf::Shape> getShape();
	//Collision of my rectangle with other rectangle
	bool rectsOverlap(Physics physics);
	//Returns whether one of my lines collides with other rectangle, the corresponding line is saved into intersectedLine
	bool linesOverlap(Physics physics);
	sf::Vector2f getGlobalPoint(unsigned int index);
	void draw(sf::RenderWindow &window);
private:
	//Returns tLine and tEdge as pair, edge is either horizontal or vertical
	pair<float, float> lineIntersection(pair<sf::Vector2f, sf::Vector2f> line, pair<sf::Vector2f, sf::Vector2f> edge, bool horizontal);
	bool tCheck(pair<float, float> t);
	bool lineOverlapsRect(pair<sf::Vector2f, sf::Vector2f> line, sf::FloatRect rect);
	
	sf::Vector2f velocity_;
	shared_ptr<sf::Shape> shape_;
	pair<sf::Vector2f, sf::Vector2f> intersectedLine_;
};

#endif