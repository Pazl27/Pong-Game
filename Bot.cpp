#include "raylib.h"
#include "Bot.h"

Bot::Bot(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speedY = 3;
	this->score = 0;
}

void Bot::draw()
{
	DrawRectangle(x, y, width, height, WHITE);
}

void Bot::hacks(float ballY)
{
	if (y + height / 2 - GetRandomValue(25, 50) > ballY) {
		y = y - speedY;
	}
	if (y + height / 2 + GetRandomValue(25,50) <= ballY) {
		y = y + speedY;
	}
	if (y <= 0) {
		y = 0;
	}
	if (y >= 600-this->height) {
		y = 600-this->height;
	}
}
