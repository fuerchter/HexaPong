#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "Level.h"

int main (int argc, const char * argv[])
{	
	sf::ContextSettings settings;
	//settings.antialiasingLevel=4;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "HexaPong", sf::Style::Close, settings);
	
	sf::Font font;
	font.loadFromFile("assets/fonts/Hexa.ttf");
	sf::Text text("HexaPong", font, 60);
	sf::Text prompt("Press enter to start!", font, 30);
	prompt.setPosition(0, 75);
	
	Level level(window.getSize(), sf::Vector2f(20, 10));
	bool ingame=false;
	
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
		if(!ingame)
		{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				level=Level(window.getSize(), sf::Vector2f(20, 10));
				ingame=true;
			}
		}
		else
		{
			level.update(deltaTime.asSeconds());
			if(level.getDone())
			{
				ingame=false;
			}
		}
		//UPDATE SECTION
		
		window.clear();
		
		//DRAW SECTION
		if(!ingame)
		{
			window.draw(text);
			window.draw(prompt);
		}
		else
		{
			level.draw(window);
		}
		//DRAW SECTION
		
		window.display();
	}
}