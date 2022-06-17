#include "BlackJack.h"
#include <iostream>
#include <conio.h>

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
		cin.get();
		return 0;
	}		

	user.coins -= 10;
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
		cout << "Press <Enter> to Continue..." << endl;
		cin.get();
		cin.get();
	}
	consolePrint(1);

	if (mySum > 21) {
		cout << "Bust!" << endl;
		cout << "You lose " << betting << " coins!" << endl;
	}
	else if (mySum == dealSum) {
		val = betting;
		cout << "Push!" << endl;
		cout << "You get back your betting: " << val << endl;
	}
	else if (mySum == 21 && myCards.size() == 2) {
		val = betting * 5 / 2;
		cout << "BlackJack!!!" << endl;
		cout << "You get " << val << " coins!(x2.5)" << endl;
	}
	else if (dealSum > 21 || mySum > dealSum) {
		val = betting * 2;
		cout << "You Win!!" << endl;
		cout << "You get " << betting << " coins!(x2)" << endl;
	}
	else {
		cout << "You lose!" << endl;
		cout << "You lose " << betting << " coins!" << endl;
	}
	
	cin.get();
	cin.get();

	return val;
}

void BlackJack::consolePrint(int r = 0) {
	system("cls");
	cout << "[Your coins: " << user.coins << ", Your betting: " << betting << "]" << endl;
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
	int input;
	while (1) {
		if (myCards.size() < 3)
			cout << "1: hit, 2: stand, 3: doubleDown" << endl;
		else
			cout << "1: hit, 2: stand" << endl;
		cout << ">>> ";
		cin >> input;
		if (input > 0 && input < 4) break;
	}
	return input - 1;
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

BlackJack::BlackJack(Player u) : Game(u) {
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

void BlackJack::run() {
	// input betting
	while (1) {
		system("cls");
		cout << "[Your coins: " << user.coins << "]" << endl;
		cout << "Please input your betting" << endl;
		cout << ">>> ";
		cin >> betting;
		if (betting <= user.coins) {
			user.coins -= betting;
			break;
		}
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
}

void BlackJack::saveData() {

}

void BlackJack::help() {

}