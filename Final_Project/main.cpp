#include <iostream>
#include "MineSweeper.h"
#include "BlackJack.h"
#include "Duel.h"

using namespace std;

int selectGame(int);

int main() {
	Login log1;
	log1.run();

	MineSweeper minesweeper(log1.user);
	BlackJack blackjack(log1.user);

	Game* games[3] = { &minesweeper, &blackjack };
	while (1) {
		int val = selectGame(log1.user.coins);
		if (val == 3)
			break;
		log1.user.coins = games[val]->run();
		// log1.save();
		cin.get();
	}
}

int selectGame(int coin) {
	system("cls");
	static const char* GameSelect[18] = {
	"������������������������������������������������������������������������������������������������������������������������������������",
	"��                 $$                        $$$$$$               ��",
	"��                 $$                            $$               ��",
	"��                 $$                        $$$$$$               ��",
	"��                 $$                        $$                   ��",
	"��                 $$                        $$$$$$               ��",
	"��                                                                ��",
	"��            <MineSweeper>               <BlackJack>             ��",
	"��                                                                ��",
	"��                 $$                     ____________            ��",
	"��                 $$                    |           4|           ��",
	"��             $$$$  $$$$                |            |           ��",
	"��           $$          $$              |     ����     |           ��",
	"��           $$    �ڡ�    $$              |     ����     |           ��",
	"��           $$          $$              |            |           ��",
	"��             $$$$$$$$$$                |4___________|           ��",
	"��                                                                ��",
	"������������������������������������������������������������������������������������������������������������������������������������"
	};
	cout << "[Your coins: ";
	printNum(coin);
	cout << "]" << endl;
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	setColor(11);
	for (int i = 0; i < 6; i++) {
		cout << GameSelect[i] << endl;
	}
	setColor(15);
	for (int i = 6; i < 18; i++) {
		cout << GameSelect[i] << endl;
	}
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	
	int user_type;
	while (1) {
		printSystem();
		cout << " Please type Game number (1 = Minesweeper / 2 = BlackJack / 4 = Quit)" << endl;
		cout << ">>> ";
		cin >> user_type;
		if (1 <= user_type && user_type <= 4) {
			if (user_type == 4)
				return 3;
			if (user_type == 3)
				continue;

			char c;
			while (1) {
				printSystem();
				cout << "Do you need guide of this game? (Y / N)" << endl;
				cout << ">>> ";
				cin >> c;
				if (c == 'Y') {
					fstream file;
					string s;
					if (user_type == 1)
						file.open("help1.txt", ios::in);
					else if (user_type == 2)
						file.open("help2.txt", ios::in);
					else
						file.open("help3.txt", ios::in);
					if (file.is_open()) {
						file.seekg(0, ios::end);
						int size = file.tellg();
						s.resize(size);
						file.seekg(0, ios::beg);
						file.read(&s[0], size);
						cout << s << endl;
					}
					
					cin.get();
					cin.get();
					break;
				}
				else if (c == 'N') break;
				else {
					cout << "Invalid Input!" << endl;
					cin.get();
				}
			}
			
			return user_type - 1;
		}
		cout << "Invalid Input" << endl;
		cin.get();
	}
}