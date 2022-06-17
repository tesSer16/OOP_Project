#include <iostream>
#include "MineSweeper.h"
#include "BlackJack.h"
#include "Player.h"
#include "Game.h"

using namespace std;

int main() {	
	//MineSweeper minesweeper;
	//minesweeper.run();
	Player temp;
	temp.coins = 12;
	temp.userID = "123123";
	BlackJack blackjack(temp);

	blackjack.run();
}