#pragma once
#include "Game.h"
#include <vector>
#include <tuple>
#include <ctime>
#include <iostream>
#include <random>
#include <windows.h>

using namespace std;

class MineSweeper : public Game{
private:
	// member variables
	int size;
	int mineCount;
	int checkCount;
	int flagCount;
	int goal;
	int** board;
	int** checked;
	tuple<int, int>* mines;
	clock_t start;

	// member functions
	void setMine();
	void calNum(int x, int y);
	void explode();
	void clear();
	void check(int x, int y);
	void blankCheck(int x, int y);
	void consolePrint();
public:
	MineSweeper(Player);
	~MineSweeper();
	
	void run();
	void saveData();
	void help();
};