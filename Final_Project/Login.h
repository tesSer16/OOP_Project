#pragma once
#include "Color.h"
#include <conio.h>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

struct Player {
	int coins;
	char userID[20]{};
	char userPW[20]{};
};

class Login {
private:
	vector<Player> userVector;

	Player login();
	Player registration();
	int askOptions();
public:
	Player user;
	Login();
	void run();
	Player getUser() { return user; }
	void save();

	Player(Login::* options[2])();
};