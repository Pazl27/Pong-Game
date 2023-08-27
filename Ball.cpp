#include "Ball.h"
#include "raylib.h"

Ball::Ball(float x, float y, float speedX, float speedY)
{
	this->x = x;
	this->y = y;
	this->speedX = speedX;
	this->speedY = speedY;
	this->radius = 5;
}

void Ball::randomStartY()
{
	this->y = GetRandomValue(100, 500);
}

void Ball::draw()
{
	DrawCircle(x, y, radius, WHITE);
}
