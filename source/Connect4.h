#ifndef CONNECT4_H
#define CONNECT4_H

enum { ROW = 8, COLUMN = 8, MAX = 20 }

class Connect4 {
	struct Player {
		char name[MAX];
		char color;
	};

	Player Opponent[2];
	char board[ROW][COLUMN];	

public:
	Connect4();
	void Register();
	void Print_board();
	void Place_piece(int, int);
	bool Detect();
	void Print_winner(int);
};

#endif