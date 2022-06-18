#pragma once
#include "Card.h"
#include "Game.h"

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
	BlackJack(Player&);
	~BlackJack();

	int run();

	int (BlackJack::* options[4])();
};