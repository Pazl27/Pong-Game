#pragma once
class Ball
{
public:
	float x, y;
	float radius;
	float speedX, speedY;

	void draw();
	Ball(float x, float y, float speedX, float speedY);
	void randomStartY();
};

