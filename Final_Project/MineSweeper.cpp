#include <iostream>
#include <random>
#include "MineSweeper.h"

using namespace std;

MineSweeper::MineSweeper(){
	// size input
	cout << "Choose N that length of mine square" << endl;
	cin >> size;

	// initializing required arrays
	board = new int* [size];
	for (int i = 0; i < size; i++) {
		board[i] = new int[size]{};
	}

	checked = new int* [size];
	for (int i = 0; i < size; i++) {
		checked[i] = new int[size]{};
	}

	mineCount = size * size * 15 / 100;  // set number of mine to 15% of its size
	mines = new tuple<int, int> [mineCount];

	// initialize timer
	start = -1;

	// initialize counter
	checkCount = 0;
	goal = size * size - mineCount;
}

MineSweeper::~MineSweeper() {
	// array deallocation
	for (int i = 0; i < size; i++) {
		delete[] board[i];
	}
	delete[] board;

	for (int i = 0; i < size; i++) {
		delete[] checked[i];
	}
	delete[] checked;

	delete[] mines;
}

void MineSweeper::setMine() {
	// initializing random module
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, size - 1);

	// Mine Setting
	for (int cnt = 0; cnt < mineCount; cnt++) {
		while (1) {
			int mine_x = dis(gen);
			int mine_y = dis(gen);
			if (board[mine_x][mine_y] == -1) continue;  // if there is already mine, continue 
			
			mines[cnt] = { mine_x, mine_y };
			board[mine_x][mine_y] = -1;  // set board to indicate tere is mine
			break;
		}
	}

	// calculate number of each board's blocks
	for (int i = 0; i < mineCount; i++) {
		int x = get<0>(mines[i]);
		int y = get<1>(mines[i]);
		calNum(x, y);
	}

	// start timer
	start = clock();
}

void MineSweeper::calNum(int x, int y) {
	// add 1 to each 8 blocks around mine
	for (int dx = -1; dx < 2; dx++) {
		for (int dy = -1; dy < 2; dy++) {
			int nx = x + dx;
			int ny = y + dy;
			
			if (0 <= nx && nx < size && 0 <= ny && ny < size) {
				if (board[nx][ny] == -1) continue;  // if there is mine, do not add 1
				board[nx][ny] += 1;
			}
		}
	}
	// cout << endl;
}

void MineSweeper::consolePrint() {
	// clear console screen and print each blocks if it is checked
	system("cls");
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

void MineSweeper::blankCheck(int x, int y) {
	// check 4 directions 
	check(x, y);
	int dx[4] = { -1, 0, 0, 1 };
	int dy[4] = { 0, 1, -1, 0 };

	for (int i = 0; i < 4; i++) {
		int nx = x + dx[i];
		int ny = y + dy[i];
		if (0 <= nx && nx < size && 0 <= ny && ny < size && !checked[nx][ny]) {
			// if new block is black too, call blankCheck recursively
			if (!board[nx][ny]) blankCheck(nx, ny);
			else check(nx, ny);
		}
	}
}

void MineSweeper::explode() {
	consolePrint();
	cout << "MINE EXPLODED!!!..." << endl;
	cin.get();
	cin.get();
}

void MineSweeper::clear(){
	// check all mines to show the result board
	for (int i = 0; i < mineCount; i++) {
		int x = get<0>(mines[i]);
		int y = get<1>(mines[i]);
		checked[x][y] = 1;
	}
	consolePrint();

	// time calculating (edit required)
	clock_t end = clock();
	double time = (double) ((double) end - start) / CLOCKS_PER_SEC;
	cout << "CLEAR!" << endl<< "During time : " << time << endl;
}

void MineSweeper::check(int x, int y) {
	checked[x][y] = 1;
	checkCount++;
}

void MineSweeper::run() {
	// set mine
	setMine();

	// start timer
	start = clock();

	// game start
	while (1) {
		if (checkCount == goal) {
		clear();
		break;
		}

		consolePrint();
		int x, y;
		try {
			cout << "Please input x, y coordinate (ex: 3 4)-> ";
			cin >> x >> y;
			if (x < 0 || x >= size || y < 0 || y >= size) {
				throw exception("out of range!");
			}
			else if (checked[x][y]) {
				throw exception("already checked!");
			}
		}
		catch (exception error) {
			cout << "Invalid Input!";
			cin.get();
			cin.get();
			continue;
		}

		if (board[x][y] == 0) {
			blankCheck(x, y);
			continue;
		}
		else if (board[x][y] == -1) {
			checked[x][y] = 1;
			explode();
			break;
		}
		else check(x, y);
	}
}