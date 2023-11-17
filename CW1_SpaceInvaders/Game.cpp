#include "Game.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

const int width = 20;
const int height = 20;

Game::Game() {
	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height - 1;
	
	for (int i = 0; i < maxBullets; ++i) {
		bulletX[i] = -1;
		bulletY[i] = -1;
	}

	for (int i = 0; i < maxEnemies; ++i) {
		enemyX[i] = rand() % width;
		enemyY[i] = 0;
	}

	score = 0;
	lives = 3;
	buffActive = false;
	buffTimer = 0;

	for (int i = 0; i < height; ++i)
		for (int j = 0; j < width; ++j)
			board[i][j] = ' ';
}

void Game::Run() {

	while (!gameover) {
		Draw();
		Input();
		Logic();
		Sleep(50);
	}

	system("cls");
	cout << "Game Over!" << endl;
	cout << "Your Score: " << score << endl;

}

void Game::Draw() {
	system("cls");

	for (int i = 0; i < width + 2; ++i)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			if (j == 0)
				cout << "#";
			if (i == y && j == x)
				cout << "A"; // player
			else {
				bool bulletDrawn = false;
				for (int k = 0; k < maxBullets; ++k) {
					if (bulletX[k] == j && bulletY[k] == i) {
						cout << "|"; // bullet
						bulletDrawn = true;
						break;
					}
				}
				if (!bulletDrawn) {
					bool enemyDrawn = false;
					// Check if the current position is occupied by an enemy
					for (int k = 0; k < maxEnemies; ++k) {
						if (enemyX[k] == j && enemyY[k] == i) {
							cout << "E"; // enemy
							enemyDrawn = true;
							break;
						}
					}

					if (!enemyDrawn) {
						if (buffActive && j == buffX && i == buffY) {
							cout << "*"; // buff
						}
						else {
							cout << board[i][j];
						}
					}
				}
			}

			if (j == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; ++i)
		cout << "#";
	cout << endl;

	cout << "Score: " << score << " Lives: " << lives << endl;
}

void Game::Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'q':
			gameover = true;
			break;
		case ' ':
			for (int i = 0; i < maxBullets; ++i) {
				if (bulletY[i] == -1) {
					bulletX[i] = x;
					bulletY[i] = y - 1;
					break;
				}
			}
			break;
		}
	}
	else {
		dir = STOP; // No key is being pressed
	}
}

void Game::Logic() {
	// Move player
	switch (dir) {
	case LEFT:
		if (x > 0) {
			x--;
		}
		break;
	case RIGHT:
		if (x < width - 1) {
			x++;
		}
		break;
	default:
		break;
	}

	//Bullet
	for (int i = 0; i < maxBullets; ++i) {
		if (bulletY[i] > -1) {
			bulletY[i]--;

			// Check if bullet hit enemy
			for (int j = 0; j < maxEnemies; ++j) {
				if (bulletX[i] == enemyX[j] && bulletY[i] == enemyY[j]) {
					score++;
					bulletX[i] = -1;
					bulletY[i] = -1;
					enemyX[j] = rand() % width;
					enemyY[j] = 0;
				}
			}

			// Check if bullet out of map
			if (bulletY[i] < 0) {
				bulletX[i] = -1;
				bulletY[i] = -1;
			}
		}
	}

	// Move enemy
	for (int i = 0; i < maxEnemies; ++i) {
		enemyY[i]++;

		// Check if player hits an enemy
		if (x == enemyX[i] && y == enemyY[i]) {
			if (lives > 1) {
				lives--;
			}
			else{
				gameover = true;
			}
			break;
		}

		// Check if enemy reaches the bottom
		if (enemyY[i] == height) {
			enemyX[i] = rand() % width;
			enemyY[i] = 0;
		}
	}

	// Handle buff logic
	buffTimer += 100;
	if (buffTimer >= buffSpawnTime) {
		SpawnBuff();
		buffTimer = 0;
	}

	CheckBuffCollision();
}

void Game::SpawnBuff() {
	//Spawn buff
	buffActive = true;
	buffX = rand() % width;
	buffY = 0;
}

void Game::CheckBuffCollision() {
	if (buffActive) {
		if (x == buffX && y == buffY) {
			lives++;
			buffActive = false;
		}
		//Check if reach bottom
		else if (buffY == height - 1) {
			buffActive = false;
		}
		else {
			buffY++;
		}
	}
}

