#include "MineSweeper.h"

using namespace std;

MineSweeper::MineSweeper(Player u) : Game(u) {
	// size input
	while (1) {
		cout << "Choose N that length of mine square 5 ~ 20 (ex: 4)" << endl;
		cout << ">>> ";
		cin >> size;
		if (4 < size && size < 21)
			break;
		cout << "Invalid size" << endl;
		cin.get();
		cin.get();
	}
	

	// initializing required arrays
	board = new int* [size];
	for (int i = 0; i < size; i++) {
		board[i] = new int[size]{};
	}

	checked = new int* [size];
	for (int i = 0; i < size; i++) {
		checked[i] = new int[size]{};
	}

	mineCount = size * size * 10 / 100;  // set number of mine to 10% of its size
	mines = new tuple<int, int> [mineCount];

	// initialize timer
	start = -1;

	// initialize counter
	checkCount = 0;
	flagCount = 0;
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
}

void MineSweeper::consolePrint(int x = 0, int y = 0) {
	// clear console screen and print each blocks if it is checked
	system("cls");

	// horizontal coordinate number print
	setColor(11);
	if (size > 10) {
		cout << "   ";
		for (int i = 0; i < size; i++) {
			if (i / 10)
				cout << i / 10 << " ";
			else
				cout << "  ";
		}
		cout << endl;
	}
	cout << (size > 10 ? "   " : "  ");
	for (int i = 0; i < size; i++) {
		cout << i % 10 << " ";
	}
	cout << endl;

	int val1 = 1, val2 = 0;
	for (int i = 0; i < size; i++) {
		setColor(11);
		if (i > 9)
			cout << i << " ";
		else
			cout << " " << i << " ";
		setColor(15);
		for (int j = 0; j < size; j++) {
			if (i == x && j == y) {
				val1 = 0;
				val2 = 1;
			}
			if (!checked[i][j]) {
				setColor(15 * val1 + 11 * val2);
				cout << "¡á ";
			}
			else if (checked[i][j] == 2) {
				setColor(12 * val1 + 11 * val2);
				cout << "¢Ò ";
				
			}
			else {
				if (board[i][j] >= 0) {
					setColor(15 * val1 + 11 * val2);
					cout << board[i][j];
					setColor(15);
					cout << " ";
				}
				else {
					setColor(12);
					cout << "¡Ø ";
				}
			}
			setColor(15);
			val1 = 1;
			val2 = 0;
		}
		if (i == 1) {
			cout << "\t\tMine : " << mineCount - flagCount << " / " << mineCount;
		}
		else if (i == 2) {
			cout << "\t\tFlag : " << flagCount;
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
	static const char* GameOver[9] = {
		"  ______                                                                                ",
		" /      W                                                                               ",
		"/$$$$$$  | ______   _____  ____    ______          ______   __     __ ______    ______  ",
		"$$ | _$$/ /      W /     W/    W  /      W        /      W /  W   /  /      W  /      W ",
		"$$ |/    |$$$$$$  |$$$$$$ $$$$  |/$$$$$$  |      /$$$$$$  |$$  W /$$/$$$$$$  |/$$$$$$  |",
		"$$ |$$$$ |/    $$ |$$ | $$ | $$ |$$    $$ |      $$ |  $$ | $$  /$$/$$    $$ |$$ |  $$/ ",
		"$$ W__$$ /$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/       $$ W__$$ |  $$ $$/ $$$$$$$$/ $$ |      ",
		"$$    $$/$$    $$ |$$ | $$ | $$ |$$       |      $$    $$/    $$$/  $$       |$$ |      ",
		" $$$$$$/  $$$$$$$/ $$/  $$/  $$/  $$$$$$$/        $$$$$$/      $/    $$$$$$$/ $$/       "
	};
	consolePrint();
	cout << "---------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < 9; i++) {
		cout << GameOver[i] << endl;
	}
	cout << endl;
	cout << "---------------------------------------------------------------------------------------" << endl;
	printSystem();
	cout << " MINE EXPLODED!!!..." << endl;
	printSystem();
	cout << " Press any button to try again." << endl;
}

void MineSweeper::clear(){
	static const char* GameClear[9] = {
		"  ______                                           ______   __                                __ ",
		" /      W                                         /      W /  |                              /  |",
		"/$$0$$$$  | ______   _____  ____    ______       /$$$$$$  |$$ |  ______    ______    ______  $$ |",
		"$$ | _$$/ /      W /     W/    W  /      W       $$ |  $$/ $$ | /      W  /      W  /      W $$ |",
		"$$ |/    |$$$$$$  |$$$$$$ $$$$  |/$$$$$$  |      $$ |      $$ |/$$$$$$  | $$$$$$  |/$$$$$$  |$$ |",
		"$$ |$$$$ |/    $$ |$$ | $$ | $$ |$$    $$ |      $$ |   __ $$ |$$    $$ | /    $$ |$$ |  $$/ $$/ ",
		"$$ W__$$ /$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/       $$ W__/  |$$ |$$$$$$$$/ /$$$$$$$ |$$ |       __ ",
		"$$    $$/$$    $$ |$$ | $$ | $$ |$$       |      $$    $$/ $$ |$$       |$$    $$ |$$ |      /  |",
		" $$$$$$/  $$$$$$$/ $$/  $$/  $$/  $$$$$$$/        $$$$$$/  $$/  $$$$$$$/  $$$$$$$/ $$/       $$/ "
	};
	// check all mines to show the result board
	for (int i = 0; i < mineCount; i++) {
		int x = get<0>(mines[i]);
		int y = get<1>(mines[i]);
		checked[x][y] = 1;
	}
	consolePrint();
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < 9; i++) {
		cout << GameClear[i] << endl;
	}
	cout << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;

	// time calculating (edit required)
	clock_t end = clock();
	double time = (double) ((double) end - start) / CLOCKS_PER_SEC;
	printSystem();
	cout << " Game Clear!" << endl;
	printSystem();
	cout << " During time : ";
	setColor(10);
	cout << time;
	setColor(15);
	cout << " (s)" << endl;
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
	int x = 0, y = 0;
	char c;
	while (1) {
		if (checkCount == goal) {
			clear();
			break;
		}

		consolePrint(x, y);
		cout << "-------------------------------------------" << endl;
		cout << "Press the button on each blocks (1: check mine / 2: flag up / 3: cancel flag)" << endl;

		// keyboard input	
		while (1) {
			if (_kbhit()) {
				c = _getch();
				if (c == -32) {
					c = _getch();
					// up
					if (c == 72 && x > 0) {
						x--;
						break;
					}
					// right
					else if (c == 77 && y < size - 1) {
						y++;
						break;
					}
					// down
					else if (c == 80 && x < size - 1) {
						x++;
						break;
					}
					// left
					else if (c == 75 && y > 0) {
						y--;
						break;
					}
				}
				// 1: check mine
				else if (c == 49) {
					if (board[x][y] == 0) {
						blankCheck(x, y);
					}
					else if (board[x][y] == -1) {
						checked[x][y] = 1;
						explode();
						return;
					}
					else check(x, y);
					break;
				}

				// 2. flag up
				else if (c == 50 && checked[x][y] == 0) {
					checked[x][y] = 2;
					flagCount += 1;
					break;
				}

				// 3. flag down
				else if (c == 51 && checked[x][y] == 2) {
					checked[x][y] = 0;
					flagCount -= 1;
					break;
				}
			}
		}
	}
}

void MineSweeper::saveData() {

}

void MineSweeper::help() {

}