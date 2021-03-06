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

public:
    Connect4();
    void Register();
    void Print_board();
    void Place_piece(int);
    bool Detect();

    Players Opponent[2];
    bool turn;
};


int main() {
    Connect4 game;
    int option;

	game.Register();

	do {
		system("clear");

		game.Print_board();

		std::cin >> option;

		game.Place_piece(option - 1);

        if(game.Detect()) {
            system("clear");
	        game.Print_board();
            std::cout << game.Opponent[game.turn].name << " wins\n";
            break;
        }

		std::cin.clear();
		std::cin.ignore();

	} while(true);
}


Connect4::Connect4() {
    for(int x = 0; x < ROW; x++)
        for(int y = 0; y < COLUMN; y++)
            board[x][y] = '0';

    Opponent[0].color = 'r';
    Opponent[1].color = 'b';
    turn = true;
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
}

void Connect4::Print_board() {
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

void Connect4::Place_piece(int Yselect) {
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

    turn ? turn = false : turn = true;

    board[Xselect][Yselect] = Opponent[turn].color;
}

bool Connect4::Detect() {
    for(int x = 0; x < ROW; x++)
		for(int y = 0, c = 1; y < COLUMN - 1; y++) {
			if(board[x][y] == Opponent[turn].color)
				c++;

			if(board[x][y + 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return true;
		}


	for(int y = 0; y < COLUMN; y++)
		for(int x = 0, c = 1; x < ROW - 1; x++) {
			if(board[x][y] == Opponent[turn].color)
				c++;

			if(board[x + 1][y] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return true;
		}


	for(int x = 0; x < ROW; x++)
		for(int y = 0, z = x, c = 1; z >= 0; z--, y++) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z - 1][y + 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return true;
		}

	for(int x = 7; x > 0; x--)
		for(int y = 7, z = x, c = 1; z <= 7; z++, y--) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z + 1][y - 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return true;
		}
	
	for(int x = 0; x < ROW; x++)
		for(int y = 7, z = x, c = 1, n = 0; n != x; y--, z--, n++) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z - 1][y - 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return true;
		}

	for(int x = 7, i = 0; x > 0; x--, i++)
		for(int y = 0, z = x, c = 1; y != i; y++, z++) {

			if(board[z][y] == Opponent[turn].color)
				c++;

			if(board[z + 1][y + 1] != Opponent[turn].color)
				c = 1;

			if(c == 4)
				return true;
		}

    return false;
}
