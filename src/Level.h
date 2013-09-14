#ifndef LEVEL
#define LEVEL

#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
using namespace rapidxml;

#include "EntityManager.h"
#include "LevelBorder.h"
#include "Block.h"
#include "Hexagon.h"
#include "Ball.h"

class Level
{
public:
	Level(sf::Vector2u windowSize, sf::Vector2f blockSize);
	bool getDone();
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
private:
	int oldPlaceBlocks(sf::Vector2u windowSize, sf::Vector2f blockSize, sf::Vector2f blockOffset, shared_ptr<LevelBorder> levelBorder, vector<string> triangles);
	void placeBlocks(sf::Vector2u windowSize, float hexagonRadius, sf::Vector2f blockSize, vector<string> rows);
	
	shared_ptr<EntityManager> manager_;
	bool done_;
};

#endif