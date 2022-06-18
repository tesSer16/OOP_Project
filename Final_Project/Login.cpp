#include "Login.h"

Login::Login() {
	options[0] = &Login::login;
	options[1] = &Login::registration;
}

int Login::askOptions() {
	static const char* GameWorld[9] = {
	"  ______                                        __       __                      __         __       __ ",
	" /      W                                      /  |  _  /  |                    /  |       /  |     /  |",
	"/$$0$$$$  | ______   _____  ____    ______     $$ | / W $$ |  ______    ______  $$ |       $$ |     $$ |",
	"$$ | _$$/ /      W /     W/    W  /      W     $$ |/$  W$$ | /      W  /      W $$ |  _____$$ |     $$ |",
	"$$ |/    |$$$$$$  |$$$$$$ $$$$  |/$$$$$$  |    $$ /$$$  $$ |/$$$$$$  |/$$$$$$  |$$ | /     $$ |     $$ |",
	"$$ |$$$$ |/    $$ |$$ | $$ | $$ |$$    $$ |    $$ $$/$$ $$ |$$ |  $$ |$$ |  $$/ $$ | $$$$$$$$ |     $$/ ",
	"$$ W__$$ /$$$$$$$ |$$ | $$ | $$ |$$$$$$$$/     $$$$/  $$$$ |$$ W__$$ |$$ |      $$ |$$     $$ |      __ ",
	"$$    $$/$$    $$ |$$ | $$ | $$ |$$       |    $$$/    $$$ |$$    $$/ $$ |      $$ |$$     $$ |     /  |",
	" $$$$$$/  $$$$$$$/ $$/  $$/  $$/  $$$$$$$/     $$/      $$/  $$$$$$/  $$/       $$/  $$$$$$$$/      $$/ "
	};

	int userInput = 0;
	string optionStrings[2] = { ". Login", ". Register" };
	char c;
	while (1) {
		system("cls");
		cout << "----------------------------------------------------------------------------------------------------------" << endl;
		for (int i = 0; i < 9; i++) {
			cout << GameWorld[i] << endl;
		}
		cout << "----------------------------------------------------------------------------------------------------------" << endl;

		printSystem();
		cout << "Select login or register" << endl;
		for (int i = 0; i < 2; i++) {
			if (i == userInput) {
				setColor(0 | (15 << 4));
				cout << ">";
			}
			cout << i + 1 << optionStrings[i];
			setColor(15);
			cout << "      ";
		}
		cout << endl;

		while (1) {
			if (_kbhit()) {
				c = _getch();
				if (c == -32) {
					c = _getch();
					// left
					if (c == 75 && userInput == 1) {
						userInput--;
						break;
					}
					// right
					else if (c == 77 && userInput == 0) {
						userInput++;
						break;
					}
				}
				else if (c == 13) {
					return userInput;
				}
			}
		}
	}
}

vector<string> split(string str, char Delimeter) {
	istringstream iss(str);
	string buffer;

	vector<string> result;

	while (getline(iss, buffer, Delimeter)) {
		result.push_back(buffer);
	}

	return result;
}

Player Login::login() {
	char inputID[20]{};
	char inputPW[20]{};
	char tempID[20]{};
	char tempPW[20]{};

	int cnt1 = 0, cnt2 = 0;
	char c;
	while (1) {
		cout << "ID : ";
		while (cnt1 <= 20 && (c = getchar()) != '\n') tempID[cnt1++] = c;

		if (4 <= cnt1 && cnt1 <= 20) {
			strncpy(inputID, tempID, cnt1);
			break;
		}
		else if (cnt1 < 4) {
			cout << "ID must exceed 3 characters!" << endl;
			cnt1 = 0;
			cin.get();
			cin.get();
		}
		else {
			cout << "ID must not exceed 20 characters!" << endl;
			cnt1 = 0;
			cin.get();
			cin.get();
		}
	}

	while (1) {
		cout << "PW : ";
		while (cnt2 <= 20 && (c = getchar()) != '\n') tempPW[cnt2++] = c;

		if (4 <= cnt2 && cnt2 <= 20) {
			strncpy(inputPW, tempPW, cnt2);
			break;
		}
		else if (cnt2 < 4) {
			cout << "PW must exceed 3 characters!" << endl;
			cnt2 = 0;
			cin.get();
			cin.get();
		}
		else {
			cout << "PW must not exceed 20 characters!" << endl;
			cnt2 = 0;
			cin.get();
			cin.get();
		}
	}
	
	
	fstream file;
	file.open("userList.dat", ios::in, ios::binary);
	if (file.is_open()) {
		char ch[256];
		vector<string> sp;
		vector<Player> userVector;

		while (!file.eof()) {
			file.getline(ch, 256);
			string work(ch);
			sp = split(work, ' ');

			Player player;
			stringstream ssInt(sp[0]);
			ssInt >> player.coins;
			strcpy(player.userID, sp[1].c_str());
			strcpy(player.userPW, sp[2].c_str());

			if (!strcmp(inputID, player.userID) && !strcmp(inputPW, player.userPW)) {
				user = player;
				return user;
			}

			userVector.push_back(player);
		}
		file.close();
	}
	cout << "Can not find such user..." << endl;
	cin.get();

	Player temp;
	temp.coins = -1;
	return temp;
}

Player Login::registration() {
	char inputID[20];
	char inputPW[20];
	char tempID[20];
	char tempPW[20];

	int cnt1 = 0, cnt2 = 0;
	char c;
	while (1) {
		cout << "ID : ";
		while (cnt1 <= 20 && (c = getchar()) != '\n') tempID[cnt1++] = c;

		if (4 <= cnt1 && cnt1 <= 20) {
		strncpy(inputID, tempID, cnt1);
		break;
		}
		else if (cnt1 < 4) {
			cout << "ID must exceed 3 characters!" << endl;
			cnt1 = 0;
			cin.get();
			cin.get();
		}		
		else {
			cout << "ID must not exceed 20 characters!" << endl;
			cnt1 = 0;
			cin.get();
			cin.get();
		}
	}
	
	while (1) {
		cout << "PW : ";
		while (cnt2 <= 20 && (c = getchar()) != '\n') tempPW[cnt2++] = c;

		if (4 <= cnt2 && cnt2 <= 20) {
		strncpy(inputPW, tempPW, cnt2);
		break;
		}
		else if (cnt2 < 4) {
			cout << "PW must exceed 3 characters!" << endl;
			cnt2 = 0;
			cin.get();
			cin.get();
		}		
		else {
			cout << "PW must not exceed 20 characters!" << endl;
			cnt2 = 0;
			cin.get();
			cin.get();
		}
	}

	user.coins = 10;
	strncpy(user.userID, inputID, cnt1);
	strncpy(user.userPW, inputPW, cnt2);

	fstream file;
	file.open("userList.dat", ios::app | ios::binary);
	if (file.is_open()) {
		file << endl << user.coins << " " << user.userID << " " << user.userPW;
		file.close();
	}

	return user;
}

void Login::run() {
	user = (this->*options[askOptions()])();
	if (user.coins == -1) run();
}

void Login::save() {
	int cnt = 1;
	fstream file;
	file.open("userList.dat", ios::in, ios::binary);
	vector<Player> userVector;
	if (file.is_open()) {
		char ch[256];
		vector<string> sp;

		while (!file.eof()) {
			file.getline(ch, 256);
			string work(ch);
			sp = split(work, ' ');

			Player player;
			stringstream ssInt(sp[0]);
			ssInt >> player.coins;
			strcpy(player.userID, sp[1].c_str());
			strcpy(player.userPW, sp[2].c_str());

			if (!strcmp(user.userID, player.userID) && !strcmp(user.userID, player.userPW)) {
				userVector[cnt - 1].coins = user.coins;
			}

			userVector.push_back(player);
			cnt++;
		}
		file.close();
	}

	file.open("userList.dat", ios::out, ios::binary);
	for (int i = 0; i < cnt; i++) {
		file << userVector[i].coins << " " << userVector[i].userID << " " << userVector[i].userPW;
		if (i != cnt - 1)
			cout << endl;
	}
}