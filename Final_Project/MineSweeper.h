#pragma once
#include "Game.h"
#include <tuple>
#include <ctime>
#include <random>

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
	void consolePrint(int, int);
public:
	MineSweeper(Player&);
	~MineSweeper();
	
	int run();
};