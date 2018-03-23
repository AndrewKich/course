// sfml_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <SFML\Graphics.hpp>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(600, 600), "SFML Test");
	Texture tanktexture;
	tanktexture.loadFromFile("images/tank.png");
	Sprite tank;
	tank.setTexture(tanktexture);
	tank.setTextureRect(IntRect(0, 0, 80, 98));
	tank.setColor(Color::Yellow);
	tank.setPosition(0,0);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Keyboard::isKeyPressed(Keyboard::Left)) { tank.move(-0.1, 0); tank.setTextureRect(IntRect(90, 100, 196, 196)); }
		if (Keyboard::isKeyPressed(Keyboard::Right)) { tank.move(0.1, 0); tank.setTextureRect(IntRect(0, 100, 80, 196)); }
		if (Keyboard::isKeyPressed(Keyboard::Up)) { tank.move(0, -0.1); tank.setTextureRect(IntRect(0, 0, 80, 98));  }
		if (Keyboard::isKeyPressed(Keyboard::Down)) { tank.move(0, 0.1); tank.setTextureRect(IntRect(90, 0, 196, 98)); }
		if (Mouse::isButtonPressed(Mouse::Left)) tank.setColor(Color::Red);
		if (Mouse::isButtonPressed(Mouse::Right)) tank.setColor(Color::Yellow);

		window.clear();
		window.draw(tank);
		window.display();
	}

	return 0;
}