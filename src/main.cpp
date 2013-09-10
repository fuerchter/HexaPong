#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "EntityManager.h"
#include "LevelBorder.h"
#include "Block.h"
#include "Hexagon.h"
#include "Ball.h"

int main (int argc, const char * argv[])
{	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "name", sf::Style::Close);
	
	//EntityManager is ptr because Entity needs a ptr to EntityManager (the reverse applies as well)
	shared_ptr<EntityManager> manager=make_shared<EntityManager>();
	
	shared_ptr<LevelBorder> levelBorder=make_shared<LevelBorder>(manager, window.getSize());
	manager->push(levelBorder);

	//Level construction
	/*//The two points at the outside of the LevelBorder
	pair<sf::Vector2f, sf::Vector2f> outerEdge(levelBorder->getPhysics().getGlobalPoint(0), levelBorder->getPhysics().getGlobalPoint(1));
	
	sf::Vector2f outerVector=outerEdge.second-outerEdge.first;
	
	//The middle of outerEdge and the middle of the screen
	pair<sf::Vector2f, sf::Vector2f> heightEdge(sf::Vector2f(outerVector.x/2, outerVector.y/2)+outerEdge.first, sf::Vector2f(window.getSize().x/2, window.getSize().y/2));
	
	sf::Vector2f heightVector=heightEdge.second-heightEdge.first;
	float heightLength=Math::length(heightVector);
	
	outerVector=Math::normalize(outerVector);
	heightVector=Math::normalize(heightVector);
	
	float blockHeight=20;
	float blockRowOffset=5;
	int rowCount=heightLength/(blockHeight+blockRowOffset);
	for(int i=1; i<=rowCount; i++)
	{
		sf::Vector2f currentRow=heightVector*(blockHeight+blockRowOffset)*i+heightEdge.first;
		
		//cout << position.x << " " << position.y << endl;
		shared_ptr<Block> block=make_shared<Block>(manager, position, 30, sf::Vector2f(40, blockHeight));
		manager->push(block);
	}*/
	
	shared_ptr<Hexagon> hexagon=make_shared<Hexagon>(manager, window.getSize());
	manager->push(hexagon);
	
	shared_ptr<Ball> ball=make_shared<Ball>(manager);
	manager->push(ball);
	
	sf::Clock clock;
	sf::Time previousTick=clock.getElapsedTime();
	sf::Time deltaTime;
	
	sf::Time counter=clock.getElapsedTime();
	int fps=0;
	
	while(window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}
		
		deltaTime=clock.getElapsedTime()-previousTick;
		previousTick=clock.getElapsedTime();
		
		fps++;
		counter+=deltaTime;
		if(counter.asSeconds()>=1)
		{
			//cout << fps << endl;
			fps=0;
			counter=sf::Time::Zero;
		}
		
		//UPDATE SECTION
		manager->update(deltaTime.asSeconds());
		//UPDATE SECTION
		
		window.clear();
		
		//DRAW SECTION
		manager->draw(window);
		//DRAW SECTION
		
		window.display();
	}
}