#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Player {
	int coins = 0;
	string userID = "";
};

class Login {
private:
	Player user;
public:
	Login();
	void login();
	void registration();
	void save(string temp_pw);
	int isValidID(string str);
	int isValidPW(string str);
	Player playerData();
};