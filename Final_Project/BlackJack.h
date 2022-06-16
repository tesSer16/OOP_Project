#pragma once
#include "Card.h"
#include "Game.h"

class BlackJack : public Game{
private:
	int betting;
	Card* myCards;
	Card* dealCards;
	Card* deck;

	void hit();
	void stand();
	void doubleDown();
	void surrender();
	void checkEnd();
	void consolePrint();
public:
	BlackJack(Player);
	void run();
	void saveDate();
	void quit();
	void help();

	void (BlackJack::*options[4])() = { hit, stand, doubleDown, surrender };
};