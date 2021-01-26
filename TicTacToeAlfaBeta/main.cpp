// Tic-Tac-Toe - Iterative implementation of alpha beta tree search.

// Built with Microsoft Visual Studio Professional 2013.

#include <iostream>
#include <algorithm>




#define INFINITY 9999 // Arbitrary value to indicate worst position.
#define NO_MOVE 9     // Flag to indicate no moves available.
#define X 1           // Computer Player
#define O -1          // Human Player
#define EMPTY 0       // Empty board square


struct values {
	int nodeMove;
	int nodeEval;
	int alpha;
	int beta;
	int player;
	int board[9];
	int moveList[10];
};


// Define the board positions.
struct values moves[9];


// Tracks the current best move for the computer.
static int bestMove;


// Used to indicate the tree depth.
static int depth;


static int board_eval(const int* board) {
	int sum;

	// Rows and columns.
	for(int colStart = 0, rowStart = 0; colStart < 3; colStart++, rowStart += 3) {
		sum = board[rowStart] + board[rowStart + 1] + board[rowStart + 2];
		if(sum == 3 || sum == -3)
			return sum;
		sum = board[colStart] + board[colStart + 3] + board[colStart + 6];
		if(sum == 3 || sum == -3)
			return sum;
	}

	// Diagonals.
	sum = board[0] + board[4] + board[8];
	if(sum == 3 || sum == -3)
		return sum;
	sum = board[2] + board[4] + board[6];
	if(sum == 3 || sum == -3)
		return sum;

	return 0;
}


void displayboard(int depth) {
	const char* t = "O X";

	std::cout << "\n\t " << t[moves[depth].board[0] + 1] << " | " << t[moves[depth].board[1] + 1] << " | " << t[moves[depth].board[2] + 1] << "\t\t 0 | 1 | 2\n";
	std::cout << "\n\t " << t[moves[depth].board[3] + 1] << " | " << t[moves[depth].board[4] + 1] << " | " << t[moves[depth].board[5] + 1] << "\t\t 3 | 4 | 5\n";
	std::cout << "\n\t " << t[moves[depth].board[6] + 1] << " | " << t[moves[depth].board[7] + 1] << " | " << t[moves[depth].board[8] + 1] << "\t\t 6 | 7 | 8\n\n";
}


// Generate a list of valid moves from the current board position...

void find_moves(values* moves) {
	int moveIndex = 0;

	for(int i = 0; i < 9; i++) {
		if(moves->board[i] == EMPTY) {
			moves->moveList[moveIndex++] = i;
		}
	}

	// To indicate the end of the move list, mark it with NO_MOVE.
	moves->moveList[moveIndex] = NO_MOVE;
}


void move_up_tree() {
	 // Decrement the tree depth (a.k.a ply level)
	depth--;

	// If this is a root node (depth=0) (the last computer's move) and there is a better move found, then update "bestMove".
	if(depth == 0 && (moves[depth + 1].nodeEval > moves[depth].nodeEval)) {
		bestMove = moves[depth].moveList[moves[depth].nodeMove];
	}

	// Player X is trying to maximize the board evaluation.
	if(moves[depth].player == X) {
		moves[depth].nodeEval = std::max(moves[depth].nodeEval, moves[depth + 1].nodeEval);
		moves[depth].alpha = std::max(moves[depth].alpha, moves[depth].nodeEval);
	}
	// Player O is trying to minimize the board evaluation.
	else {
		moves[depth].nodeEval = std::min(moves[depth].nodeEval, moves[depth + 1].nodeEval);
		moves[depth].beta = std::min(moves[depth].beta, moves[depth].nodeEval);
	}

	// Explore the next move...
	moves[depth].nodeMove++;
}


 void move_down_tree() {
	static int eval;

	// Increment the tree depth (a.k.a ply level)
	depth++;

	// Copy the parent node values to the child.
	moves[depth] = moves[depth - 1];

	if(moves[depth].player == X) {
		 // Make the X move on the child board.
		moves[depth].board[moves[depth].moveList[moves[depth].nodeMove]] = X;

		// Players O turn to move.
		moves[depth].player = O;

		// Set initial evaluation to the worst possible value (INFINITY),
		// since player O is trying to minimize the board evaluation,
		// its score can only get better.
		moves[depth].nodeEval = INFINITY;
	} else {
		 // Make the O move on the child board.
		moves[depth].board[moves[depth].moveList[moves[depth].nodeMove]] = O;

		// Players X turn to move.
		moves[depth].player = X;

		// Set initial evaluation to the worst possible value (-INFINITY),
		// since player X is trying to maximize the board evaluation,
		// its score can only get better.
		moves[depth].nodeEval = -INFINITY;
	}

	// Calculate board evaluation...
	eval = board_eval(moves[depth].board);

	// Start at initial move.
	moves[depth].nodeMove = 0;

	//  Check leaf node win.
	if(eval) {
		moves[depth].nodeEval = eval;
		moves[depth].moveList[0] = NO_MOVE;
	} else {
		find_moves(&moves[depth]);

		//  Check leaf node draw.
		if(moves[depth].moveList[0] == NO_MOVE) {
			moves[depth].nodeEval = eval;
		}
	}
}


void computer_move() {

	depth = 0;

	find_moves(&moves[0]);

	moves[0].nodeMove = 0;
	moves[0].nodeEval = -INFINITY;
	moves[0].alpha = -INFINITY;
	moves[0].beta = INFINITY;
	moves[0].player = X;

	if(moves[0].moveList[moves[0].nodeMove] != NO_MOVE) {

		while(true) {
			if(moves[depth].moveList[moves[depth].nodeMove] == NO_MOVE) {
				displayboard(depth); //uncomment to see AI' analizes
				if(depth == 0) break;

				move_up_tree();
			} else if(moves[depth].alpha >= moves[depth].beta) {
				 // AlphaBeta pruning. No further move exploration needed from this tree node.  
				moves[depth].nodeMove = 0;
				moves[depth].moveList[moves[depth].nodeMove] = NO_MOVE;
			} else {
				move_down_tree();
			}
		}

		// Make the best move the computer has found.
		moves[0].board[bestMove] = X;

		printf("Computer : %d\n", bestMove);
	}
}


void init_board() {
	moves[0].board[0] = EMPTY;
	moves[0].board[1] = EMPTY;
	moves[0].board[2] = EMPTY;
	moves[0].board[3] = EMPTY;
	moves[0].board[4] = EMPTY;
	moves[0].board[5] = EMPTY;
	moves[0].board[6] = EMPTY;
	moves[0].board[7] = EMPTY;
	moves[0].board[8] = EMPTY;
}


void human_move() {
	int move{};
	char* p, s[100];

	printf("Your move: ");
	while(fgets(s, sizeof(s), stdin)) {
		move = strtol(s, &p, 10);
		if(p == s || *p != '\n') {
			printf("Your move: ");
		} else break;
	}

	// Make human board move.
	moves[0].board[move] = O;
}


int main(int argc, char** argv) {
	init_board();
	displayboard(0);

	while(1) {
		human_move();
		computer_move();
		displayboard(0);

		find_moves(&moves[0]);

		if(board_eval(moves[0].board)) {
			printf("Computer Wins! (-_-)\n");
			init_board();
			displayboard(0);
		} else if(moves[0].moveList[0] == NO_MOVE) {
			printf("A draw! (*_*)\n");
			init_board();
			displayboard(0);
		}
	}

	return 0;
}