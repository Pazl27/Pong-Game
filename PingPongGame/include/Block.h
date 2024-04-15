#pragma once
class Block
{
public:
	float x, y;
	float width, height;
	float speedY;
	int score;

	Block(float x, float y, float width, float height);
	void draw();
};

