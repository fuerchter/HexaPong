#ifndef PADDLE
#define PADDLE

#include <utility>
using namespace std;

#include "SFML/System.hpp"

#include "Entity.h"
#include "Math.h"

class Paddle : public Entity
{
public:
	Paddle(shared_ptr<EntityManager> manager, pair<sf::Vector2f, sf::Vector2f> outerEdge, sf::Vector2f midScreen, float length);
	void rotate(float angle);
private:
};

#endif