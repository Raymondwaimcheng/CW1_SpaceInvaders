
#pragma once

class Game {
public:
	Game();
	void Run();


private:
	void Draw();
	void Input();
	void Logic();
	void SpawnBuff();
	void CheckBuffCollision();

	bool gameover;
	int x, y;
	static const int maxBullets = 5;
	int bulletX[maxBullets], bulletY[maxBullets];
	static const int maxEnemies = 3;
	int enemyX[maxEnemies], enemyY[maxEnemies];
	int score;
	int lives;
	int buffX, buffY;  // Buff position
	bool buffActive;   // Flag to check if buff is currently active
	int buffTimer;     // Timer for buff spawn
	static const int buffSpawnTime = 10000;
	//int gameEndTime;
	//static const int gameEnd= 5000;

	enum Direction { STOP = 0, LEFT, RIGHT };
	Direction dir;

	char board[20][20];
};
