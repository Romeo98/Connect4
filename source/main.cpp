#include <iostream>
#include <iomanip>
#include <limits>
#include "Connect4.h"


int main() {
Connect4 game;
    
    int option, turn = 0;
	bool win = true;

	game.Register();

	do {
		system("clear");

		game.Print_board();

		std::cin >> option;

		game.Place_piece(option - 1, turn);
		win = game.Detect(turn);

        if(!win) {
            system("clear");
	        game.Print_board();
            game.Print_winner(turn);
            break;
        }

		(turn == 0) ? turn = 1 : turn = 0;

		std::cin.clear();
		std::cin.ignore();

	} while(true);
}