#pragma once
#include <string>

using namespace std;

class Card {
private:
	int shape; // 0: heart, 1: club, 2: spade, 3: diamond
	int number; // 1: A, 2 ~ 10, 11: J, 12: Q, 13: K
public:
	Card();
	Card(int, int);
	int getShape() const { return shape; }
	int getNumber() const { return number; }
	static void shuffle(Card*, int);
	string dataPrint();
	friend int operator+(const int&, const Card&);
};