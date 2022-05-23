#include <iostream>
#include <cstdlib>
#include <tuple>
#include <vector>
#include <map>
#include <random>
#include "mine.h"

using namespace std;

int main() {
	int usersize;
	
	cout << "Choose N that length of mine square" << endl;
	cin >> usersize;
	mine user1(usersize);
	random_device rd;
	mt19937 gen(rd());

	uniform_int_distribution<int> dis(0, usersize - 1);

	int** board = new int* [usersize];
	for (int i = 0; i < usersize; i++) {
		board[i] = new int[usersize];
	}
	for (int i = 0; i < usersize; i++) {
		for (int j = 0; j < usersize; j++) {
			board[i][j] = 0;
		}
	}

	vector<tuple<int,int>> mine_array;
	for (int i = 0; i < usersize; i++) {
		while (1) {
			int mine_x = dis(gen);
			int mine_y = dis(gen);
			if (board[mine_x][mine_y] == 0) {
				mine_array.emplace_back(make_tuple(mine_x, mine_y));
				board[mine_x][mine_y] = -1;
				break;
				cout << "wow" << endl;
			}
		}
	}

	
	int** checked = new int* [usersize];
	for (int i = 0; i < usersize; i++) {
		checked[i] = new int[usersize];
	}
	for (int i = 0; i < usersize; i++) {
		for (int j = 0; j < usersize; j++) {
			checked[i][j] = 0;
		}
	}

	for (int i = 0; i < mine_array.size(); i++) {
		int x = get<0>(mine_array[i]);
		int y = get<1>(mine_array[i]);
		cout << x << " " << y << endl;
		board[x][y] = -1;
		user1.cal_num(x, y, board);
	}

	int cnt = 0;
	int goal = usersize * usersize - mine_array.size();
	time_t start = time(NULL);
	while (1) {
		user1.console_print(checked, board);
		int x = -1;
		int y = -1;
		try {
			cout << "Please input x cordinate -> ";
			cin >> x;
			cout << "Please input y cordinate -> ";
			cin >> y;
		}
		catch (exception error) {
			cout << "Invalid Input!";
			continue;
		}	
		if (board[x][y] == 0) {
			user1.blank_check(x, y, checked, board);
			continue;
		}
		else if (board[x][y] == -1) {
			checked[x][y] = 1;
			user1.explode(checked, board);
			break;
		}
		else if (cnt == goal) {
			user1.clear(mine_array, checked, board, start);
			break;
		}
		checked[x][y] = 1;
		cnt += 1;
	}
	

	for (int i = 0; i < usersize; i++) {
		delete[] checked[i];
	}
	delete[] checked;
	for (int i = 0; i < usersize; i++) {
		delete[] board[i];
	}
	delete[] board;

	
}

/*

*/