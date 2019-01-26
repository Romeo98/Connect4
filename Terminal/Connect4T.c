// Connect4, c terminal version

#include <stdio.h>
#define false 0
#define true 1
#define ROW 8
#define COLUMN 8
#define MAX 20

struct Players {
    char name[MAX];
    char color;
};

char board[ROW][COLUMN];
struct Players Opponent[2];

void Create_board();
void Register();
void Print_board();
void Place_piece(int, int);
_Bool Detect(int);

int main() {

    Create_board();
    Register();

    int option, turn = 0;

    do {
        system("clear");

        Print_board();
        scanf("\n%d", &option);

        Place_piece(option -1, turn);

        if(!Detect(turn)) {
            system("clear");
            Print_board();
            break;
        }

        (turn == 0) ? (turn = 1) : (turn = 0);
        
        fflush(stdin);

    } while(true);
}


void Create_board() {
    for(int x = 0; x < ROW; x++)
        for(int y = 0; y < COLUMN; y++)
            board[x][y] = '0';
}

void Register() {
    printf("Type name of player 1: ");
    scanf("%19s", &Opponent[0].name);

    fflush(stdin);
    while((getchar()) != '\n');

    printf("Type name of player 2: ");
    scanf("%19s", &Opponent[1].name);
    
    fflush(stdin);
    while((getchar()) != '\n');

    Opponent[0].color = 'r';
    Opponent[1].color = 'b';
}

void Print_board() {
    printf("   Connect4\n\n");

    for(int x = 1; x <= 8; x++)
        printf("%d ", x);

    printf("\n\n");

    for(int x = 0; x < ROW; x++) {
        for(int y = 0; y < COLUMN; y++)
            printf("%c ", board[x][y]);
        
        printf("\n");
    }
}

void Place_piece(int Yselect, int player) {
    while(board[0][Yselect] != '0') {
        printf("Column: %d is filled, select another one\n", Yselect);
        printf("Your new option is: ");
        scanf("%d", Yselect);
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


_Bool Detect(int turn) {
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
