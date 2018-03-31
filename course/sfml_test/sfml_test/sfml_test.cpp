// sfml_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "map.h"
#include "view.h"
#include <SFML\Graphics.hpp>
using namespace sf;

class Player {
private: float x, y;
public:
	float w, h, dx, dy, speed; //координаты игрока х и у, высота ширина, ускорение (по х и по у), сама скорость
	int dir; //направление движения игрока
	String File; //файл с расширением
	Image image; //сфмл изображение
	Texture texture; //сфмл текстура
	Sprite sprite; //сфмл спрайт

	Player(String F, float X, float Y, float W, float H) { //Конструктор с параметрами(формальными) для класса Player
		dx = 0; dy = 0; speed = 0; dir = 0;
		File = F;//имя файла+расширение
		w = W; h = H;//высота и ширина
		image.loadFromFile("images/" + File); //запихиваем в image наше изображение, вместо File мы передадим то, что пропишем при создании объекта
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}

	void interactionWithMap() {
		for(int i=y/32; i<(y+h)/32; i++)
			for (int j = x / 32; j < (x + h) / 32; j++) {
				if (Map[i][j] == '1') {
					if (dx > 0) x = j * 32 - w;
					if (dx < 0) x = j * 32 + w;
					if (dy > 0) y = i * 32 - h;
					if (dy < 0) y = i * 32 + h;
				}
			}
	}

	void update() {
		switch (dir) {
		case 0: dx = speed; dy = 0; break; //движение вправо
		case 1: dx = -speed; dy = 0; break; //влево
		case 2: dx = 0; dy = speed; break; //вниз
		case 3: dx = 0; dy = -speed; break;//вверх
		}

		x += dx;
		y += dy;
		speed = 0;	//остановка перса после отжатия кнопки. не написать - будет идти без остановки аки змейка.
		sprite.setPosition(x, y);
		interactionWithMap();
	}

	float getPlayerCoordinateX() {
		return x;
	}
	float getPlayerCoordinateY() {
		return y;
	}
};

int main()
{
	Texture map_texture;
	map_texture.loadFromFile("images/map.png");
	Sprite map;
	map.setTexture(map_texture);
	RenderWindow window(VideoMode(map_width * 32, map_height * 32), "SFML Test");
	Player p("tank.png", 32,32, 32, 32);
	view.reset(FloatRect(0, 0, map_width * 32, map_height * 32));

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)	
				window.close();
		}

		window.clear();
		window.setView(view);

		for (int i = 0; i < map_height; i++)
			for (int j = 0; j < map_width; j++) {
				if (Map[i][j] == '1') map.setTextureRect(IntRect(0, 0, 32, 32));
				if (Map[i][j] == '0') map.setTextureRect(IntRect(32, 0, 64, 32));
				map.setPosition(j * 32, i * 32);
				window.draw(map);
			}

		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			p.dir = 1; p.speed = 32;
			p.sprite.setTextureRect(IntRect(0, 32, 32, 64));
			; continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			p.dir = 0; p.speed = 32;
			p.sprite.setTextureRect(IntRect(32, 32, 64, 64));
			; continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			p.dir = 3; p.speed = 32;
			p.sprite.setTextureRect(IntRect(0, 0, 32, 32));
			; continue;
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			p.dir = 2; p.speed = 32;
			p.sprite.setTextureRect(IntRect(32, 0, 64, 32));
			; continue;
		}
		p.update();
		window.draw(p.sprite);
		window.display();
		getplayercoordinates(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
	}
	return 0;
}