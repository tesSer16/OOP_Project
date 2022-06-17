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
	// cout << endl;
}

void MineSweeper::consolePrint() {
	// clear console screen and print each blocks if it is checked
	system("cls");

	// horizontal coordinate number print
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
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


	for (int i = 0; i < size; i++) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
		if (i > 9)
			cout << i << " ";
		else
			cout << " " << i << " ";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		for (int j = 0; j < size; j++) {
			if (!checked[i][j]) {
				cout << "¡á ";
			}
			else if (checked[i][j] == 2) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "¢Ò ";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			}
			else {
				if (board[i][j] >= 0) {
					cout << board[i][j] << " ";
				}
				else {
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
					cout << "¡Ø ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				}
			}
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "[System]";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " MINE EXPLODED!!!..." << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "[System]";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "[System]";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " Game Clear!" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	cout << "[System]";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	cout << " During time : ";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	cout << time;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
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
	while (1) {
		if (checkCount == goal) {
			clear();
			break;
		}

		consolePrint();
		// mode input
		cout << "-------------------------------------------" << endl;
		int x, y;
		int usertype;

		cout << "Please input type (1 = check mine / 2 = flag up / 3 = cancel flag) -> ";
		cin >> usertype;

		if (usertype == 1) {
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
		else if (usertype == 2) {
			cout << "Please input x, y coordinate (ex: 3 4) -> ";
			cin >> x >> y;
			if (checked[x][y] == 0) {
				checked[x][y] = 2;
				flagCount += 1;
			}
		}
		if (usertype == 3) {
			cout << "Please input x, y coordinate (ex: 3 4) -> ";
			cin >> x >> y;
			if (checked[x][y] == 2) {
				checked[x][y] = 0;
				flagCount -= 1;
			}
		}
	}
}

void MineSweeper::saveData() {

}

void MineSweeper::help() {

}