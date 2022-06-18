#pragma once
#include "Login.h"
#include <conio.h>
#include <string>
#include "Color.h"

class Game {
protected:
	Player user;
public: 
	Game(Player& u) {
		user = u;
	}
	virtual int run() = 0;
};