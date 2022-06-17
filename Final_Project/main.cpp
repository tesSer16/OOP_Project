#include <iostream>
#include "MineSweeper.h"
#include "BlackJack.h"
#include "Player.h"
#include "Game.h"

using namespace std;

int main() {
	Player temp;

	MineSweeper minesweeper(temp);
	minesweeper.run();
	
	/*BlackJack blackjack(temp);
	blackjack.run();*/
}