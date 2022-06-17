#include "Card.h"
#include <random>
#include <iostream>

int operator+(const int& sum, const Card& card) {
	return sum + card.number;
}

Card::Card() {
	shape = -1;
	number = -1;
}

Card::Card(int s, int num) {
	shape = s;
	number = num;
}

void Card::shuffle(Card* deck, int size) {
	// initializing random module
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, size - 1);

	// shuffling
	int idx;
	Card temp = deck[0]; 
	for (int i = 0; i < size - 1; i++) {
		idx = i + (dis(gen) % (size - i));

		// swap
		temp = deck[idx];
		deck[idx] = deck[i];
		deck[i] = temp;
	}
}

string Card::dataPrint() {
	string cShape[4] = { "¢¾", "¢À", "¢¼", "¡ß" };
	string cNumber[4] = { "10", " J", " Q", " K" };
	string temp = " " + to_string(number);
	if (number > 9)
		temp = cNumber[number - 10];
	else if (number == 1)
		temp = " A";
	return cShape[shape] + temp;
}