#pragma once
#include <string>

class Player {
private:
	int coins;
	string userID;
public:
	void loadData();
	void changeCoins();
};