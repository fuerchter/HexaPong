#ifndef LEVEL
#define LEVEL

#include "EntityManager.h"
#include "LevelBorder.h"
#include "Block.h"
#include "Hexagon.h"
#include "Ball.h"

class Level
{
public:
	Level(sf::Vector2u windowSize, sf::Vector2f blockSize, sf::Vector2f blockOffset);
	void placeBlocks(sf::Vector2u windowSize, sf::Vector2f blockSize, sf::Vector2f blockOffset, shared_ptr<LevelBorder> levelBorder);
	void update(float deltaTime);
	void draw(sf::RenderWindow &window);
private:
	shared_ptr<EntityManager> manager_;
};

#endif