#include "Card.h"
#include <random>

using namespace std;

int operator+(const int& sum, const Card& card) {
	return sum + card.number;
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

	// open addressing
	bool* check; // check array
	check = new bool[size] {false, };
	int idx;
	Card temp = deck[0]; 
	for (int i = 0; i < size; i++) {
		idx = i + (dis(gen) % (size - i));
		while (!check[idx]) {
			idx = (idx + 1) % size;
		}
		check[idx] = true;
		// swap
		temp = deck[idx];
		deck[idx] = deck[i];
		deck[i] = temp;
	}

	delete[] check;
}

string Card::dataPrint() {
	char cShape[4] = { '¢¾', '¢À', '¢¼', '¡ß' };
	string cNumber[4] = { "10", " J", " Q", " K" };
	string temp = " " + (char)number;
	if (number > 9)
		temp = cNumber[number - 10];
	return cShape[shape] + temp;
}