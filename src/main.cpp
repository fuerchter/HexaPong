#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "EntityManager.h"
#include "Hexagon.h"
#include "Ball.h"

int main (int argc, const char * argv[])
{	
	sf::RenderWindow window(sf::VideoMode(1280, 720), "name", sf::Style::Close);
	
	//EntityManager is ptr because Entity needs a ptr to EntityManager (the reverse applies as well)
	shared_ptr<EntityManager> manager=make_shared<EntityManager>();
	
	shared_ptr<Hexagon> hexagon=make_shared<Hexagon>(manager, Entity::EHexagon, window.getSize());
	manager->push(hexagon);
	
	shared_ptr<Ball> ball=make_shared<Ball>(manager, Entity::EBall);
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