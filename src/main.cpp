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
	
	//Neither should be cutting!
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(-0.5, 0), sf::Vector2f(0.5, 0));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(0, 0), sf::Vector2f(1, 0));
	
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(0.5, 0), sf::Vector2f(1.5, 0));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(0, 0), sf::Vector2f(1, 0));
	
	
	//Non-cutting and parallel
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(5, 7), sf::Vector2f(2, 10));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(4, 6), sf::Vector2f(1, 9));
	
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(0, 0), sf::Vector2f(1, 0));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(0, 1), sf::Vector2f(1, 1));
	
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(0, 0), sf::Vector2f(1, 0));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(-2, 0), sf::Vector2f(-1, 0));
	
	//Non-cutting and non-parallel
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(5, 7), sf::Vector2f(2, 10));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(4, 4), sf::Vector2f(4.5, 6.5));
	
	//Cutting and non-parallel
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(0, 0), sf::Vector2f(1, 0));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(0.5, -0.5), sf::Vector2f(0.5, 0.5));
	
	//pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(5, 7), sf::Vector2f(2, 10));
	//pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(4, 4), sf::Vector2f(3, 10));
	
	pair<sf::Vector2f, sf::Vector2f> first(sf::Vector2f(5, 2), sf::Vector2f(8, 8));
	pair<sf::Vector2f, sf::Vector2f> second(sf::Vector2f(9, 4), sf::Vector2f(4, 3)); //angle issues?
	float segmentAngle=Math::segmentAngle(first, second);
	cout << "segmentAngle " << segmentAngle << endl;
	if(segmentAngle!=0)
	{
		sf::Vector2f intersection=Math::segmentIntersection(first, second, segmentAngle);
		cout << intersection.x << " " << intersection.y << endl;
		cout << "First cut " << Math::isPointOnSegment(intersection, first) << endl;
		cout << "Second cut " << Math::isPointOnSegment(intersection, second) << endl;
	}
	
	//pair<sf::Vector2f, sf::Vector2f> test(sf::Vector2f(0, 0), sf::Vector2f(1, 0));
	//cout << Math::isPointOnSegment(sf::Vector2f(0.5, 0), test) << endl;
	
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