#pragma once
#include <vector>
#include <tuple>
#include <ctime>
using namespace std;

class MineSweeper {
private:
	// member variables
	int size;
	int mineCount;
	int checkCount;
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
	MineSweeper();
	~MineSweeper();
	
	void run();  // input Player object
};