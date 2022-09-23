
#include <iostream>
using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[3][3], char);


void isValidInput(int, int); //check for valid input
void validCell(char[][3], int, int); //check if cell is empty and can accept new entry
bool wonRow(char[][3], char); //three in a row of same type
bool wonColumn(char[][3], char); //three in a column of same type
bool wonDiagonal(char[][3], char); //three in a diagonal of same type

bool valid = false; // valid if user input meets program assumptions --> empty cell && valid input (i.e. 0-2)
int playerInputCount = 0; //count player inputs 


int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {
		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);
		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}
	return 0;
}

//displays tic tac toe board
void displayBoard(char board[][3]) {						//	 TIC-TAC-TOE BOARD
	cout << " " << endl;							//	-------------------
	//rows									//	| 0,0 | 0,1 | 0,2 |
	for (int i = 0; i < 3; i++) {						//	-------------------
		cout << "-------------" << endl;				//	| 1,0 | 1,1 | 1,2 |
		//columns							//	-------------------
		for (int j = 0; j < 3; j++) {					//	| 2,0 | 2,1 | 2,2 |
			cout << "| " << board[i][j] << " ";			//	-------------------
		}
		cout << "|" << endl;
	}
	cout << "-------------" << endl;
}

//inserts players char into board if valid input is given
void makeAMove(char board[][3], char player) {
	int row = 0;
	int col = 0;

	while (valid != true) {
		//rows
		cout << "Enter a row(0, 1, 2) for player " << player << " : ";
		cin >> row;
		//columns
		cout << "Enter a column(0, 1, 2) for player " << player << " : ";
		cin >> col;

		isValidInput(row, col);
		validCell(board, row, col);
	}
	board[row][col] = player;
	valid = false;
}

//three of the same type in either row | column | diagonal
bool isWon(char player, char board[][3]) {
	return wonRow(board, player) || wonColumn(board, player) || wonDiagonal(board, player);
}

//counts valid user input till max=8 is reached resulting in draw (no winner)
bool isDraw(char board[][3]) {
	playerInputCount++;
	return playerInputCount > 8;
}

//check for invalid input
void isValidInput(int row, int col) {
	if (row > 2) {
		valid = false;
		cout << "invalid input" << endl;
	} else if (col > 2) {
		valid = false;
		cout << "invalid Input" << endl;
	} else {
		valid = true;
	}
}

//checks if cell is not empty
void validCell(char board[][3], int row, int col) {
	if (board[row][col] != ' ') {
		valid = false;
		cout << "This cell is occupied. Try a different cell." << endl;
	}
}

//check for three of same type in a row
bool wonRow(char board[][3], char player) {
	int count = 0;

	//iterate rows and increment count when input == player
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[i][j] == player) count++;
			if (count == 3) return true;
		}
		count = 0;
	}
	return false;
}

//check for three of same type in a column
bool wonColumn(char board[][3], char player) {
	int count = 0;
	
	//iterate columns and increment count when input == player
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (board[j][i] == player) count++;
			if (count == 3) return true;
		}
		count = 0;
	}
	return false;
}

//check for three of same type in a diagonal
bool wonDiagonal(char board[][3], char player) {
	return (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
		(board[0][2] == player && board[1][1] == player && board[2][0] == player);
}
