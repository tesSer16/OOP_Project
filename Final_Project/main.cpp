#include <iostream>
#include "MineSweeper.h"
#include "BlackJack.h"
#include "Game.h"

using namespace std;

int main() {
	Player temp;
	temp.coins = 20;
	temp.userID = "1231";

	MineSweeper minesweeper(temp);
	minesweeper.run();
	
	/*BlackJack blackjack(temp);
	blackjack.run();*/
}