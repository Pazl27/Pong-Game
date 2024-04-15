#include "raylib.h"
#include <iostream>
#include <string>
#include "../include/Bot.h"
#include "../include/Ball.h"
#include "../include/Block.h"

using namespace std;

bool started= false;
bool multiplayer = false;
const char* winnerText = nullptr;

int randomDirection() {
	int number = GetRandomValue(0, 1);
	if (number == 0){
		return -1;
	}
	else {
		return 1;
	}
}

int main() {

	InitWindow(800, 600, "Game");
	SetTargetFPS(120);

	Ball ball(GetScreenWidth() / 2, GetScreenHeight() / 2, 200*randomDirection(), 200);
	Block leftPannel(50, GetScreenHeight() / 2 - 50, 10, 100);
	Block rightPannel(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100);
	Bot ai(GetScreenWidth() - 50 - 10, GetScreenHeight() / 2 - 50, 10, 100);
	
	while (!WindowShouldClose()){

		if (ball.y <= 0) {
			ball.speedY *= -1;
			ball.y = 0;
		}

		if (ball.y >= GetScreenHeight()){
			ball.speedY *= -1;
			ball.y = GetScreenHeight();
		}

		if (IsKeyDown(KEY_W)) {
			if (leftPannel.y >= 0 ) {
				leftPannel.y -= leftPannel.speedY * GetFrameTime();
			}	
		}
		if (IsKeyDown(KEY_S)) {
			if (leftPannel.y + leftPannel.height <= GetScreenHeight()) {
				leftPannel.y += leftPannel.speedY * GetFrameTime();
			}
			
		}


		//Multiplayer
		if (multiplayer) {
			if (IsKeyDown(KEY_I)) {
				if (rightPannel.y >= 0) {
					rightPannel.y -= rightPannel.speedY * GetFrameTime();
				}
			
			}
			if (IsKeyDown(KEY_K)) {
				if (rightPannel.y + rightPannel.height <= GetScreenHeight()) {
					rightPannel.y += rightPannel.speedY * GetFrameTime();
				}
			
			}
		}


		if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ leftPannel.x,leftPannel.y,leftPannel.width,leftPannel.height })) {
			if (ball.speedX < 0) {
				ball.speedX *= -1.1f;
				ball.speedY = (ball.y - (leftPannel.y+ leftPannel.height/2)) / (leftPannel.height / 2) * ball.speedX;
			}
		}
		if (!multiplayer) {
			if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ ai.x,ai.y,ai.width,ai.height })) {
				if (ball.speedX > 0) {
					ball.speedX *= -1.1f;
					ball.speedY = (ball.y - (ai.y + ai.height / 2)) / (ai.height / 2) * -ball.speedX;
				}
			}
		}
		
		//Multipalyer
		if (multiplayer) {
			if (CheckCollisionCircleRec(Vector2{ ball.x,ball.y }, ball.radius, Rectangle{ rightPannel.x,rightPannel.y,rightPannel.width,rightPannel.height })) {
				if (ball.speedX > 0) {
					ball.speedX *= -1.1f;
					ball.speedY = (ball.y - ai.y) / (rightPannel.height / 2) * -ball.speedX;
				}
			}
		}
		

		if (ball.x < 0 && multiplayer) {
			rightPannel.score++;
			ball.x = GetScreenWidth() / 2;
			ball.randomStartY();
			ball.speedY = GetRandomValue(-200,200);
			ball.speedX = -200;
		}
		if (ball.x > GetScreenWidth()) {
			leftPannel.score++;
			ball.x = GetScreenWidth() / 2;
			ball.randomStartY();
			ball.speedY = GetRandomValue(-200,200);
			ball.speedX = 200;
		}
		if (ball.x < 0 && !multiplayer) {
			ai.score++;
			ball.x = GetScreenWidth() / 2;
			ball.randomStartY();
			ball.speedY = GetRandomValue(-200,200);
			ball.speedX = -200;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		//WinnerStuff
		if (leftPannel.score == 5) {
			started = false;
			winnerText = "left Player won!";
			int textWidth = MeasureText(winnerText, 40);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 200, 40, WHITE);
		}
		if (rightPannel.score == 5) {
			started = false;
			winnerText = "right Player won!";
			int textWidth = MeasureText(winnerText, 40);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 200, 40, WHITE);
		}
		if (ai.score == 5) {
			started = false;
			winnerText = "you are a bot!";
			int textWidth = MeasureText(winnerText, 40);
			DrawText(winnerText, GetScreenWidth() / 2 - textWidth / 2, GetScreenHeight() / 2 - 200, 40, WHITE);
		}

		if (!started) {
			if (IsKeyPressed(KEY_SPACE)) {
				started = true;
				ai.score = 0;
				leftPannel.score = 0; 
				rightPannel.score = 0;
			}
			if (IsKeyPressed(KEY_M)) {
				multiplayer = true;
			}
			if (IsKeyPressed(KEY_O) && multiplayer) {
					multiplayer = false;
			}
			const char* text = "Press me";
			int textWidth = MeasureText(text, 40);
			DrawText(text, GetScreenWidth() / 2 - textWidth/2, GetScreenHeight() / 2 - 20, 40, ORANGE);
			if (multiplayer) {
				DrawText(TextFormat("Multiplayer activated"), 10, GetScreenHeight() - 20, 10, RED);
				int mulitWidth = MeasureText(TextFormat("Press O to switch Multiplayer off"), 20);
				DrawText(TextFormat("Press O to switch Multiplayer off"), GetScreenWidth() / 2 - mulitWidth / 2, GetScreenHeight() / 2 + 20, 20, RED);
			}
			else if (!multiplayer) {
				DrawText(TextFormat("Multiplayer deactivated"), 10, GetScreenHeight() - 20, 10, RED);
				int mulitWidth = MeasureText(TextFormat("Press M for Multiplayer"), 20);
				DrawText(TextFormat("Press M for Multiplayer"), GetScreenWidth() / 2 - mulitWidth / 2, GetScreenHeight() / 2 + 20, 20, RED);
			}
			
		}
		else {
			ball.x += ball.speedX * GetFrameTime();
			ball.y += ball.speedY * GetFrameTime();
			ai.hacks(ball.y);
			ball.draw();

			leftPannel.draw();
			if (multiplayer) {
				rightPannel.draw();
			}
			else {
				ai.draw();
			}

			DrawLine(GetScreenWidth() / 2, 0, GetScreenWidth() / 2, GetScreenHeight(), WHITE);
			DrawRing(Vector2{ (float)GetScreenWidth() / 2,(float)GetScreenHeight() / 2 }, 100, 101, 0, 360, 200, WHITE);
			DrawText(TextFormat("%i", leftPannel.score), 5, 5, 20, ORANGE);
			if (multiplayer) {
				DrawText(TextFormat("%i", rightPannel.score), GetScreenWidth() - 15, 5, 20, ORANGE);
			}
			if(!multiplayer) {
				DrawText(TextFormat("%i", ai.score), GetScreenWidth() - 15, 5, 20, ORANGE);
			}
			
		}
		
		EndDrawing();

	}

	CloseWindow();

	return 0;
}
