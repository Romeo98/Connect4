// Connect4, c++ terminal version

#include <iostream>
#include <iomanip>
#include <limits>

enum { ROW = 8, COLUMN = 8, MAX = 20 };

struct Players {
    char name[MAX];
    char color;
};

class Connect4 {

    char board[ROW][COLUMN];
    Players Opponent[2];

public:
    Connect4();
    void Register();
    void Print_board();
    void Place_piece(int, int);
    bool Detect(int);
};


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
		(turn == 0) ? turn = 1 : turn = 0;

		std::cin.clear();
		std::cin.ignore();

	} while(win);

	game.Print_board();
}


Connect4::Connect4() {
    for(int x = 0; x < ROW; x++)
        for(int y = 0; y < COLUMN; y++)
            board[x][y] = '0';
}

void Connect4::Register() {
    std::cout << "Type name of player 1: ";
    std::cin >> std::setw(MAX) >> Opponent[0].name;
    
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Type name of player 2: ";
    std::cin >> std::setw(MAX) >> Opponent[1].name;

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    Opponent[0].color = 'r';
    Opponent[1].color = 'b';
}

void Connect4::Print_board() {
    
    std::cout << Opponent[0].name << '\n' << Opponent[1].name << '\n';

    std::cout << "   Connect4\n\n";

    for(int x = 1; x <= 8; x++)
        std::cout << x << ' ';

    std::cout << "\n\n";

    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COLUMN; y++)
            std::cout << board[x][y] << ' ';

        std::cout << '\n';
    }
}

void Connect4::Place_piece(int Yselect, int player) {
    while(board[0][Yselect] != '0') {
        std::cout << "Column: " << Yselect + 1 << " is filled, select another one\n";
        std::cout << "Your new option is: ";
        std::cin >> Yselect;
        Yselect--;
    }

    int Xselect = 0;

    while(Xselect < ROW - 1) {
        if(board[Xselect + 1][Yselect] != '0')
                break;
        Xselect++;
    }

    board[Xselect][Yselect] = Opponent[player].color;
}

bool Connect4::Detect(int turn) {
    for(int x = 0; x < ROW; x++)
		for(int y = 0, c = 1; y < COLUMN - 1; y++) {
			if(board[x][y] == Opponent[turn].color)
				c++;

			if(board[x][y + 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return false;
		}


	for(int y = 0; y < COLUMN; y++)
		for(int x = 0, c = 1; x < ROW - 1; x++) {
			if(board[x][y] == Opponent[turn].color)
				c++;

			if(board[x + 1][y] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return false;
		}


	for(int x = 0; x < ROW; x++)
		for(int y = 0, z = x, c = 1; z >= 0; z--, y++) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z - 1][y + 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return false;
		}

	for(int x = 7; x > 0; x--)
		for(int y = 7, z = x, c = 1; z <= 7; z++, y--) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z + 1][y - 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return false;
		}
	
	for(int x = 0; x < ROW; x++)
		for(int y = 7, z = x, c = 1, n = 0; n != x; y--, z--, n++) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z - 1][y - 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return false;
		}

	for(int x = 7, i = 0; x > 0; x--, i++)
		for(int y = 0, z = x, c = 1; y != i; y++, z++) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z + 1][y + 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return false;
		}

    return true;
}
