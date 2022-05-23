#pragma once
#include <vector>
#include <tuple>
using namespace std;

class mine {
private:
	int size;
public:
	mine(int x);
	void cal_num(int x, int y,int** board);
	void console_print(int** checked, int** board);
	void blank_check(int x, int y,int**checked,int**board);
	void explode(int**checked, int**board);
	void clear(vector<tuple<int, int>>v, int** checked, int** board, time_t start);
	void setsize(int x);
};