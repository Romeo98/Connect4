/* Connect4 game
 * Author: Romeo Barraza
 */

#include <iostream>
#include <fstream>
#define ROW 8
#define COLUMN 8

struct Players {
	std::string name;
	int win, loss;
	char color;
};

class Connect4 {
	private:
		char board[ROW][COLUMN];
		int nPlayers;
		Players Jug[2];
		Players *List;

	public:
		Connect4();
		~Connect4();
		void Load_file();
		void Register();
		void Print_board();
		void Place_piece(int, int);
		bool detect(int);
};


int main() {
	Connect4 game;
	int opcion, turno = 0;
	bool winrar = true;

	game.Register();

	do {
		system("clear");

		game.Print_board();

		std::cin >> opcion;

		game.Place_piece(opcion - 1, turno);
		winrar = game.detect(turno);
		(turno == 0) ? turno = 1 : turno = 0;

		std::cin.clear();
		std::cin.ignore();

	} while(winrar);

	game.Print_board();
}



Connect4::Connect4() {
	for(int x = 0; x < ROW; x++)
		for(int y = 0; y < COLUMN; y++)
			board[x][y] = '0';
}

Connect4::~Connect4() {
	delete [] List;
}

void Connect4::Load_file() {
	nPlayers = -1;

	std::fstream p_list("Player_list.dat", std::ios::binary | std::ios::app);

	while(!p_list.eof()) {
		nPlayers++;
		p_list.read(NULL, sizeof(Players));
	}

	List = new Players [nPlayers];
	
	int n = -1;

	while(!p_list.eof()) {
		n++;
		p_list.read(reinterpret_cast <char *> (&List[n]), sizeof(Players));
	}

	p_list.close();
}

void Connect4::Register() {
	bool check[2] = {false};

	Connect4::Load_file();
	std::cout << "Type name of player 1: ";
	std::cin >> Jug[0].name;

	std::cout << "Type name of player 2: ";
	std::cin >> Jug[1].name;

	Jug[0].color = 'r';
	Jug[1].color = 'b';

	for(int i = 0; i < 2; i++) 
		for(int j = 0; j < nPlayers; j++) 
			if(Jug[i].name == List[j].name) {
				Jug[i] = List[j];
				check[i] = true;
				break;
			}
	
	for(int i = 0; i < 2; i++) 
		if(check[i]) {
			Jug[i].win = Jug[i].loss = 0;			
			std::ofstream p_list("Player_list.dat", std::ios::binary | std::ios::app);
			p_list.write(reinterpret_cast <char *> (&Jug[i]), sizeof(Players));
			p_list.close();	
		}
}

void Connect4::Print_board() {
	std::cout << "   CONNECT4\n\n";
	for(int x = 1; x <= ROW; x++)
		std::cout << x << ' ';

	std::cout << "\n\n";

	for(int x = 0; x < ROW; x++) {
		for(int y = 0; y < COLUMN; y++)
			std::cout << board[x][y] << ' ';

		std::cout << '\n';
	}
}

void Connect4::Place_piece(int y, int n) {
	while(board[0][y] != '0') {
		std::cout << "Column: " << y + 1 << " is filled, type another one\n";
		std::cout << "Your option is: ";
		std::cin >> y;
		y--;
	}

	int x = 0;

	while(x < ROW - 1) {
		if(board[x + 1][y] != '0')
			break;
		x++;
	}

	board[x][y] = Jug[n].color;
}

bool Connect4::detect(int turno) {
	for(int x = 0; x < ROW; x++)
		for(int y = 0, c = 1; y < COLUMN - 1; y++) {
			if(board[x][y] == Jug[turno].color)
				c++;

			if(board[x][y + 1] != Jug[turno].color)
				c = 1;

			if(c == 4)
				return false;
		}


	for(int y = 0; y < COLUMN; y++)
		for(int x = 0, c = 1; x < ROW - 1; x++) {
			if(board[x][y] == Jug[turno].color)
				c++;

			if(board[x + 1][y] != Jug[turno].color)
				c = 1;

			if(c == 4)
				return false;
		}


	for(int x = 0; x < ROW; x++)
		for(int y = 0, z = x, c = 1; z >= 0; z--, y++) {

			if(board[z][y] == Jug[turno].color)
				c++;

			if(board[z - 1][y + 1] != Jug[turno].color)
				c = 1;

			if(c == 4)
				return false;
		}

	for(int x = 7; x > 0; x--)
		for(int y = 7, z = x, c = 1; z <= 7; z++, y--) {

			if(board[z][y] == Jug[turno].color)
				c++;

			if(board[z + 1][y - 1] != Jug[turno].color)
				c = 1;

			if(c == 4)
				return false;
		}
	
	for(int x = 0; x < ROW; x++)
		for(int y = 7, z = x, c = 1, n = 0; n != x; y--, z--, n++) {

			if(board[z][y] == Jug[turno].color)
				c++;

			if(board[z - 1][y - 1] != Jug[turno].color)
				c = 1;

			if(c == 4)
				return false;
		}

	for(int x = 7, i = 0; x > 0; x--, i++)
		for(int y = 0, z = x, c = 1; y != i; y++, z++) {

			if(board[z][y] == Jug[turno].color)
				c++;

			if(board[z + 1][y + 1] != Jug[turno].color)
				c = 1;

			if(c == 4)
				return false;
		}
}
