#include "Paddle.h"

Paddle::Paddle(shared_ptr<EntityManager> manager, int index, pair<sf::Vector2f, sf::Vector2f> outerEdge, sf::Vector2f midScreen, float length):
Entity(manager, EntityType::EPaddle), index_(index)
{
	shared_ptr<sf::ConvexShape> shape=make_shared<sf::ConvexShape>(4);
	shape->setPoint(0, outerEdge.second);
	shape->setPoint(1, outerEdge.first);
	sf::Vector2f firstToMid=Math::normalize(outerEdge.first-midScreen);
	shape->setPoint(2, outerEdge.first+firstToMid*length);
	sf::Vector2f secondToMid=Math::normalize(outerEdge.second-midScreen);
	shape->setPoint(3, outerEdge.second+secondToMid*length);
	shape->setOrigin(midScreen);
	shape->setPosition(midScreen);
	shape->setFillColor(sf::Color(37, 165, 255));
	physics_.setShape(shape);
}

void Paddle::rotate(float angle)
{
	physics_.getShape()->rotate(angle);
}

int Paddle::getIndex()
{
	return index_;
}