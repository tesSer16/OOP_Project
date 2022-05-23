#include <iostream>
#include <Windows.h>
#include "mine.h"
#include <vector>
#include <tuple>
#include <map>
#include <ctime>

using namespace std;

mine::mine(int x){
	setsize(x);
}
void mine::setsize(int x) {
	size = x;
}
void mine::cal_num(int x, int y, int** board) {
	for (int dx = -1; dx < 2; dx++) {
		for (int dy = -1; dy < 2; dy++) {
			int nx = x + dx;
			int ny = y + dy;
			
			if (0 <= nx && nx < size && 0 <= ny && ny < size) {
				if (board[nx][ny] == -1) continue;
				// cout << dx << " " << dy << endl;
				board[nx][ny] += 1;
			}
		}
	}
	// cout << endl;
}
void mine::console_print(int** checked, int** board) {
	cout << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (!checked[i][j]) {
				cout << "бс ";
			}
			else {
				if (board[i][j] >= 0) {
					cout << board[i][j] << " ";
				}
				else {
					cout << "б╪ ";
				}
			}
		}
		cout << endl;
	}
}
void mine::blank_check(int x, int y, int** checked, int** board) {
	checked[x][y] = 1;
	int dx[4] = { -1, 0, 0, 1 };
	int dy[4] = { 0, 1, -1, 0 };

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 <= nx and nx < size and 0 <= ny and ny < size and not checked[nx][ny]) {
			if (not board[nx][ny]) {
				blank_check(nx, ny, checked, board);
			}
			else {
				checked[nx][ny] = 1;
			}
		}
	}
}
void mine::explode(int **checked,int**board) {
	mine::console_print(checked, board);
	cout << "MINE EXPLODED!!!...." << endl;
}
void mine::clear(vector<tuple<int, int>>v, int **checked,int**board,time_t start){
	for (int i = 0; i < v.size(); i++) {
		int x = get<0>(v[i]);
		int y = get<1>(v[i]);
		checked[x][y] = 1;
	}
	mine::console_print(checked, board);
	time_t end = time(NULL);
	time_t duration = (double)(end - start);
	cout << "CLEAR!" << endl<< "During time : " << duration << endl;
}