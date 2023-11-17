#pragma once

class Player
{
public:
	Player(int x, int y);
	~Player();
	void Move();
	bool ChangeDir(char key);
	int GetX() const { return x; };
	int GetY() const { return y; };
	void Shoot();

private:
	int x, y;
};