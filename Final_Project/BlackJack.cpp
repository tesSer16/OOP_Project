#include "BlackJack.h"

int BlackJack::hit() {
	myCards.push_back(deck[deckIndex++]);
	mySum = calSum(myCards);
	return 0;
}

int BlackJack::stand() {
	return 1;
}

int BlackJack::doubleDown() {
	if (user.coins < betting) {
		cout << "You don't have enough coins!" << endl;
		cin.get();
		return 0;
	}		

	user.coins -= betting;
	betting *= 2;
	myCards.push_back(deck[deckIndex++]);
	mySum = calSum(myCards);
	return 1;
}

// implement later
int BlackJack::split() { 
	return 1;
}

int BlackJack::result() {
	int val = 0;
	dealCards.insert(dealCards.begin(), dealFirstCard);
	dealSum = calSum(dealCards);
	while (mySum < 22 && dealSum <= 17) {
		dealCards.push_back(deck[deckIndex++]);
		dealSum = calSum(dealCards);

		consolePrint(1);
		printSystem();
		cout << "Press <Enter> to Continue..." << endl;

		cin.get();
		cin.get();
	}
	consolePrint(1);

	if (mySum > 21) {
		printSystem();
		cout << "Bust!" << endl;
		printSystem();
		cout << "You lose ";
		printNum(betting);
		cout << " coins!" << endl;
	}
	else if (mySum == dealSum) {
		val = betting;
		printSystem();
		cout << "Push!" << endl;
		printSystem();
		cout << "You get back your betting: ";
		printNum(val);
		cout << endl;
	}
	else if (mySum == 21 && myCards.size() == 2) {
		val = betting * 5 / 2;
		printSystem();
		cout << "BlackJack!!!" << endl;
		printSystem();
		cout << "You get ";
		printNum(val); 
		cout << " coins!(x2.5)" << endl;
	}
	else if (dealSum > 21 || mySum > dealSum) {
		val = betting * 2;
		printSystem();
		cout << "You Win!!" << endl;
		printSystem();
		cout << "You get ";
		printNum(val);
		cout << " coins!(x2)" << endl;
	}
	else {
		printSystem();
		cout << "You lose!" << endl;
		printSystem();
		cout << "You lose ";
		printNum(betting);
		cout << " coins!" << endl;
	}
	
	cin.get();
	cin.get();

	return val;
}

void BlackJack::consolePrint(int r = 0) {
	system("cls");
	cout << "[Your coins: ";
	printNum(user.coins);
	cout << ", Your betting: ";
	printNum(betting);
	cout << "]" << endl;

	cout << "Dealer's sum: " << dealSum << endl;
	cout << endl;

	for (unsigned i = 0; i <= dealCards.size() - r; i++)
		cout << "忙式式式忖 ";
	cout << endl;
	for (unsigned i = 0; i <= dealCards.size() - r; i++)
		cout << "弛" << ((!i && !r) ? "≦≦≦" : dealCards.at(i - 1 + r).dataPrint()) << "弛 ";
	cout << endl;
	for (unsigned i = 0; i <= dealCards.size() - r; i++)
		cout << "戌式式式戎 ";
	cout << endl;
	cout << endl;

	cout << "<" << user.userID << ">'s sum: " << mySum << endl;
	for (unsigned i = 0; i < myCards.size(); i++)
		cout << "忙式式式忖 ";
	cout << endl;
	for (unsigned i = 0; i < myCards.size(); i++)
		cout << "弛" << myCards.at(i).dataPrint() << "弛 ";
	cout << endl;
	for (unsigned i = 0; i < myCards.size(); i++)
		cout << "戌式式式戎 ";
	cout << endl;
	cout << endl;
}

int BlackJack::askOptions() {
	int inputIndex = 0;
	string optionStrings[3] = { ". hit", ". stand", ". doubleDown" };
	int optionCount = myCards.size() < 3 ? 3 : 2;
	char c;
	while (1) {
		consolePrint();
		for (int i = 0; i < optionCount; i++) {
			if (i == inputIndex) {
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
					// left arrow
					if (c == 75 && inputIndex > 0) { 
						inputIndex--;
						break;
					}
					// right arrow
					else if (c == 77 && inputIndex < optionCount - 1) {
						inputIndex++;
						break;
					}						
				}
				else if (c == 13) {
					return inputIndex;
				}
			}			
		}
	}
}

int BlackJack::calSum(vector<Card> v) {
	int cnt1 = 0;
	int sum = 0;
	for (unsigned i = 0; i < v.size(); i++) {
		int val = v[i].getNumber();
		if (val == 1) cnt1++;
		else if (val > 9) sum += 10;
		else sum += val;
	}

	if (cnt1) {
		if (sum < 11)
			sum += 11;
		sum += cnt1 - 1;
	}

	return sum;
}

BlackJack::BlackJack(Player& u) : Game(u) {
	betting = 0;
	mySum = 0;
	dealSum = 0;
	deckIndex = 0;
	deck = new Card[52]; // 52 cards, 1 set

	options[0] = &BlackJack::hit;
	options[1] = &BlackJack::stand;
	options[2] = &BlackJack::doubleDown;
	options[3] = &BlackJack::split;
}

BlackJack::~BlackJack() {
	delete[] deck;
}

int BlackJack::run() {
	// input betting
	while (1) {
		system("cls");
		cout << "[Your coins: ";
		printNum(user.coins);
		cout << "]" << endl;

		printSystem();
		cout << "Please input your betting" << endl;
		cout << ">>> ";
		cin >> betting;

		if (betting <= user.coins) {
			user.coins -= betting;
			break;
		}

		printSystem();
		cout << "You don't have enough coins!" << endl;
		cin.get();
		cin.get();
	}
	

	// initialize and shuffle deck
	for (int s = 0; s < 4; s++) {
		for (int n = 0; n < 13; n++) {
			deck[13 * s + n] = Card(s, n + 1);
		}
	}

	Card::shuffle(deck, 52); 
	
	// initial 2 cards
	myCards.push_back(deck[deckIndex++]);
	myCards.push_back(deck[deckIndex++]);
	dealFirstCard = deck[deckIndex++];
	dealCards.push_back(deck[deckIndex]);
	mySum = calSum(myCards);
	dealSum = calSum(dealCards);

	int flag;
	while (1) {
		consolePrint();
		flag = (this->*options[askOptions()])();
		if (flag || mySum >= 21) {
			user.coins += result();
			break;
		}
	}

	return user.coins;
}