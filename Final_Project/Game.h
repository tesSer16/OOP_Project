#pragma once
#include "Player.h"

class Game {
protected:
	Player user;
public: 
	Game(Player u) {
		user = u;
	}
	virtual void run() = 0;
	virtual void saveData() = 0;
	virtual void help() = 0;
};