#pragma once
#include "Console.h"
#define SAFE_DELETE(p) if (p!=nullptr){delete p;p = nullptr;}

const int UI_HEIGHT = 6;//아무 숫자 / 위에 있는 동무
const int UI_WIDTH = 10;//아무 숫자 / 옆에 있는 친구
const int MAP_HEIGHT = 13;
const int MAP_WIDTH = 15;
const int MARGIN = 2;

const int EMPTY_TYPE = 0;
const int BOMB_TYPE = 9;


const COLOR GROUND_COLOR = COLOR::LIGHT_YELLOW;
const COLOR SELECT_COLOR = COLOR::MINT;
const COLOR GRASS_COLOR = COLOR::LIGHT_GREEN;
const COLOR FLAG_COLOR = COLOR::RED;
const COLOR NumColors[10]{
	COLOR::WHITE,
	COLOR::BLUE,
	COLOR::GREEN,
	COLOR::LIGHT_RED,
	COLOR::VIOLET,
	COLOR::YELLOW,
	COLOR::SKYBLUE,
	COLOR::BLACK,
	COLOR::GRAY,
	COLOR::RED
};