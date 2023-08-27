#pragma once
class Bot
{
public:
	float x, y;
	float width, height;
	float speedY;
	int score;

	Bot(float x, float y, float width, float height);
	void draw();
	void hacks(float y);
};

