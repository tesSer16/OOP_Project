#pragma once
#include "Player.h"

class Game {
private:
	Player user;
public:
	Game(Player);
	virtual void run() = 0;
	virtual void saveData() = 0;
	virtual void quit() = 0;
	virtual void help() = 0;
};