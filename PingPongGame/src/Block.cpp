#include "../include/Block.h"
#include "raylib.h"

Block::Block(float x, float y, float width, float height)
{
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->speedY = 300;
	this->score = 0;
}

void Block::draw()
{
	DrawRectangle(x, y, width, height, WHITE);
}


