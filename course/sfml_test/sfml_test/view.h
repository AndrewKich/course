#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

View view; //�������� sfml ������ "���", ������� � �������� �������
//�������� ������ �� ������

void getplayercoordinates(float x, float y) {
	view.setCenter(x+15, y+15);
	if (Keyboard::isKeyPressed(Keyboard::Space))
		view.setSize(2 * map_width * 32, 2 * map_height * 32);
	else view.setSize(map_width * 32, map_height * 32);
}