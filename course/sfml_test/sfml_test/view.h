#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

View view; //�������� sfml ������ "���", ������� � �������� �������
//�������� ������ �� ������
void getplayercoordinates(float x, float y) {
	view.setCenter(x+15, y+15);
}