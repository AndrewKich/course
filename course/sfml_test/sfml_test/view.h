#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

View view; //объ€вили sfml объект "вид", который и €вл€етс€ камерой
//слежение камеры за персом
void getplayercoordinates(float x, float y) {
	view.setCenter(x+15, y+15);
}