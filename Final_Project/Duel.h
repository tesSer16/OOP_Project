#pragma once
#include "Card.h"
#include "Game.h"

class Duel : public Game {
private:
	Card card1;
	Card card2;
public:
	Duel(Player);
	int run();
	void help();
};