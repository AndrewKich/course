// sfml_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "map.h"
#include "view.h"
#include <SFML\Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

class Entity {
public: float x, y, w, h, dx, dy, speed;
		Texture texture;
		Sprite sprite;
		String name; //различие по именам
		bool life;	//жив/нет

		Entity(Image &image, float X, float Y, float W, float H, String Name) {
			x = X; y = Y; w = W; h = H; name = Name;
			dx = 0; dy = 0; speed = 0;
			life = true;
			texture.loadFromImage(image);
			sprite.setTexture(texture);
		}

		FloatRect getRect() {	//ф-я получения координат  иразмеров прямоугольника для проверки столкновений
			return FloatRect(x, y, w, h);
		}
};

class Player :public Entity {
public:
	float x, y; // коррдинаты игрока
	int dir; //направление движения игрока
	int keys=0;	//кол-во ключей
	enum { left, right, up, down } state;

	Player(Image &image, float X, float Y, float W, float H, String Name):Entity(image,X,Y,W,H,Name) { //Конструктор с параметрами(формальными) для класса Player
		dx = 0; dy = 0; speed = 0; dir = 0;
		w = W; h = H;//высота и ширина
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		x = X; y = Y;//координата появления спрайта
		sprite.setTextureRect(IntRect(0, 0, w, h));
	}

	void interactionWithMap() {
		for(int i=y/32; i<(y+h)/32; i++)
			for (int j = x / 32; j < (x + h) / 32; j++) {
				if (Map[i][j] == 'k') { keys++; Map[i][j] = '0'; }
				if (Map[i][j] == 'd'&&keys > 0) { keys--; Map[i][j] = '0'; }
				else if (Map[i][j] != '0') {
					if (dx > 0) x = j * 32 - w;
					if (dx < 0) x = j * 32 + w;
					if (dy > 0) y = i * 32 - h;
					if (dy < 0) y = i * 32 + h;
				}
			}
	}

	void control() {
		if (Keyboard::isKeyPressed(Keyboard::Left)) {
			dir = left; speed = 0.2;
			sprite.setTextureRect(IntRect(0, 32, 32, 64));
		}
		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			dir = right; speed = 0.2;
			sprite.setTextureRect(IntRect(32, 32, 64, 64));
		}
		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			dir = up; speed = 0.2;
			sprite.setTextureRect(IntRect(0, 0, 32, 32));		
		}
		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			dir = down; speed = 0.2;
			sprite.setTextureRect(IntRect(32, 0, 64, 32));
		}
	}

	void update(float time) {
		control();
		switch (dir) {
		case right: dx = speed; dy = 0; break; //движение вправо
		case left: dx = -speed; dy = 0; break; //влево
		case down: dx = 0; dy = speed; break; //вниз
		case up: dx = 0; dy = -speed; break;//вверх
		}

		x += dx*time;
		y += dy*time;
		speed = 0;	//остановка перса после отжатия кнопки. не написать - будет идти без остановки аки змейка.
		interactionWithMap();
		sprite.setPosition(x, y);
	}

	float getPlayerCoordinateX() {
		return x;
	}
	float getPlayerCoordinateY() {
		return y;
	}
};

class Enemy :public Entity {
public:
	Enemy(Image &image, float X, float Y, int W, int H, String Name) :Entity(image, X, Y, W, H, Name) {
	if (name == "Disc") {
		sprite.setTextureRect(IntRect(0, 0, w, h));
		dx = 0.15;
	}
}

	void interactionWithMap(float Dx) {
		for (int i = y / 32; i<(y + h) / 32; i++)
			for (int j = x / 32; j < (x + h) / 32; j++) {
				if (Map[i][j] != '0') {
					if (Dx > 0) { x = j * 32 - w; dx = -dx; }
					if (Dx < 0) { x = j * 32 + w; dx = -dx; }
				}
			}
	}
	
	void update(float time) {
		if (name == "Disc") {
			interactionWithMap(dx);
			x += dx*time;
			sprite.setPosition(x, y);
		}
	}
};

int main()
{
	srand(time(NULL));
	Texture map_texture, keys;
	map_texture.loadFromFile("images/map.png");
	Sprite map;
	map.setTexture(map_texture);
	Image hero;
	hero.loadFromFile("images/tank.png");
	Image discImage;
	discImage.loadFromFile("images/disc.png");

	RenderWindow window(VideoMode(map_width * 32, map_height * 32), "SFML Test");
	Player p(hero, 32, 32, 32, 32, "Player");
	Enemy disc(discImage, 256, 256, 32, 32, "Disc");
	view.reset(FloatRect(0, 0, map_width * 32, map_height * 32));

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart(); time /= 800;

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
				if (Map[i][j] == '0') map.setTextureRect(IntRect(32, 0, 32, 32));
				if (Map[i][j] == '1') map.setTextureRect(IntRect(0, 0, 32, 32));
				if (Map[i][j] == 'd') map.setTextureRect(IntRect(0, 32, 32, 32));
				if (Map[i][j] == 'k') map.setTextureRect(IntRect(32, 32, 32, 32));
				map.setPosition(j * 32, i * 32);
				window.draw(map);
			}

		p.update(time); 
		disc.update(time);
		//безобидный враг
		if(disc.sprite.getGlobalBounds().intersects(p.sprite.getGlobalBounds())) { 
			//если спрайты пересекаются, разворачиваем врага, а игрока отталкиваем
			disc.dx = -disc.dx; p.y += pow(-1,rand()%2)*32;
		}
		window.draw(p.sprite); window.draw(disc.sprite);
		window.display();
		getplayercoordinates(p.getPlayerCoordinateX(), p.getPlayerCoordinateY());
	}
	return 0;
}