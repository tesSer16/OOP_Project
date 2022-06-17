#pragma once
#include "Card.h"
#include "Game.h"
#include <iostream>
#include <vector>

using namespace std;

class BlackJack : public Game{
private:
	int betting;
	int mySum;
	int dealSum;
	int deckIndex;
	Card dealFirstCard;
	vector<Card> myCards;
	vector<Card> dealCards;
	Card* deck; // 52 cards, 1 set

	int hit();
	int stand();
	int doubleDown();
	int split();
	int result();
	void consolePrint(int);
	int askOptions();
	int calSum(vector<Card>);
public:
	BlackJack(Player u);
	~BlackJack();

	void run();
	void saveData();
	void help();

	int (BlackJack::* options[4])();
};