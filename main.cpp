#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Define chess pieces
const char PAWN = 'P';
const char ROOK = 'R';
const char KNIGHT = 'N';
const char BISHOP = 'B';
const char QUEEN = 'Q';
const char KING = 'K';
const char EMPTY = ' ';

// Define player colors
const char WHITE = 'W';
const char BLACK = 'B';

// Define board size
const int BOARD_SIZE = 8;

// Define board array
char board[BOARD_SIZE][BOARD_SIZE];

// Define current player
char currentPlayer = WHITE;

// Function to initialize the board with starting positions
void initializeBoard() {
	// Place white pieces
	board[0][0] = ROOK;
	board[0][1] = KNIGHT;
	board[0][2] = BISHOP;
	board[0][3] = QUEEN;
	board[0][4] = KING;
	board[0][5] = BISHOP;
	board[0][6] = KNIGHT;
	board[0][7] = ROOK;
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[1][i] = PAWN;
	}

	// Place black pieces
	board[7][0] = ROOK;
	board[7][1] = KNIGHT;
	board[7][2] = BISHOP;
	board[7][3] = QUEEN;
	board[7][4] = KING;
	board[7][5] = BISHOP;
	board[7][6] = KNIGHT;
	board[7][7] = ROOK;
	for (int i = 0; i < BOARD_SIZE; i++) {
		board[6][i] = PAWN;
	}

	// Place empty squares
	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			board[i][j] = EMPTY;
		}
	}
}

// Function to print the current board state
void printBoard() {
	cout << " A B C D E F G H" << endl;
	for (int i = 0; i < BOARD_SIZE; i++) {
		cout << i + 1 << " ";
		for (int j = 0; j < BOARD_SIZE; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
}

// Function to check if a move is valid for the current player
bool isValidMove(int startRow, int startCol, int endRow, int endCol) {
	// Check if start and end positions are within the bounds of the board
	if (startRow < 0 || startRow >= BOARD_SIZE || startCol < 0 || startCol >= BOARD_SIZE ||
		endRow < 0 || endRow >= BOARD_SIZE || endCol < 0 || endCol >= BOARD_SIZE) {
		return false;
	}

	// Check if start position contains a piece belonging to the current player
		if (board[startRow][startCol] == EMPTY ||
			(currentPlayer == WHITE && islower(board[startRow][startCol])) ||
			(currentPlayer == BLACK && isupper(board[startRow][startCol]))) {
			return false;
		}

	// Check if end position is empty or contains an opponent's piece
	if (board[endRow][endCol] != EMPTY &&
		(currentPlayer == WHITE && isupper(board[endRow][endCol])) ||
		(currentPlayer == BLACK && islower(board[endRow][endCol]))) {
		return false;
	}

	// Check piece-specific move rules
	switch (board[startRow][startCol]) {
	case PAWN:
		// White pawns can only move forward one square or two squares on the first move
		// They can only capture diagonally
		if (currentPlayer == WHITE) {
			if (endRow != startRow - 1 || endCol != startCol) {
				if (startRow != 1 || endRow != startRow - 2 || endCol != startCol) {
					if (endRow != startRow - 1 || abs(endCol - startCol) != 1) {
						return false;
					}
				}
			}
		}
		// Black pawns can only move forward one square or two squares on the first move
		// They can only capture diagonally
		else {
			if (endRow != startRow + 1 || endCol != startCol) {
				if (startRow != 6 || endRow != startRow + 2 || endCol != startCol) {
					if (endRow != startRow + 1 || abs(endCol - startCol) != 1) {
						return false;
					}
				}
			}
		}
		break;
	case ROOK:
		// Rooks can only move horizontally or vertically
		if (endRow != startRow && endCol != startCol) {
			return false;
		}
		break;
	case KNIGHT:
		// Knights can only move in an "L" shape (two squares in one direction and one square in the other)
		if (abs(endRow - startRow) != 2 || abs(endCol - startCol) != 1) {
			if (abs(endRow - startRow) != 1 || abs(endCol - startCol) != 2) {
				return false;
			}
		}
		break;
	case BISHOP:
		// Bishops can only move diagonally
		if (abs(endRow - startRow) != abs(endCol - startCol)) {
			return false;
		}
		break;
	case QUEEN:
		// Queens can move horizontally, vertically, or diagonally
		if (endRow != startRow && endCol != startCol && abs(endRow - startRow) != abs(endCol - startCol)) {
			return false;
		}
		break;
	case KING:
		// Kings can only move one square horizontally, vertically, or diagonally
		if (abs(endRow - startRow) > 1 || abs(endCol - startCol) > 1) {
			return false;
		}
		break;
	}

	// If all checks pass, the move is valid
		return true;
}

// Function to execute a move
void makeMove(int startRow, int startCol, int endRow, int endCol) {
	// Update the board array with the new position of the piece
	board[endRow][endCol] = board[startRow][startCol];
	board[startRow][startCol] = EMPTY;

	// Switch to the other player
	if (currentPlayer == WHITE) {
		currentPlayer = BLACK;
	}
	else {
		currentPlayer = WHITE;
	}
}

int main() {
	// Initialize the board
	initializeBoard();

	// Loop until the game is over
	while (true) {
		// Print the board
		printBoard();
		// Prompt the current player for their move
		cout << currentPlayer << "'s turn. Enter move (ex. A1 B2): ";

		// Read the player's move
		string move;
		cin >> move;

		// Convert the move to coordinates
		int startRow = move[1] - '1';
		int startCol = move[0] - 'A';
		int endRow = move[3] - '1';
		int endCol = move[2] - 'A';

		// Check if the move is valid
		if (isValidMove(startRow, startCol, endRow, endCol)) {
			// Execute the move
			makeMove(startRow, startCol, endRow, endCol);
		}
		else {
			cout << "Invalid move. Try again." << endl;
		}

	}

	return 0;
}
