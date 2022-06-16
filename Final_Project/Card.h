#pragma once
#include <string>

class Card {
private:
	int shape; // 0: heart, 1: club, 2: spade, 3: diamond
	int number; // 1 ~ 10, 11: J, 12: Q, 13: K
public:
	Card(int, int);
	int getShape() { return shape; }
	int getNumber() { return number; }
	void shuffle(Card*, int);
	string dataPrint();
	friend int operator+(const int&, const Card&);
};