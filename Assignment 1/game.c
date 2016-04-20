/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include "game.h"

static void swap_players(struct player ** current, struct player ** other)
{	
    /* Implement a classic swap using a temporary pointer */
	struct player temp = **current;
	**current = **other;
	**other = temp;
}

struct player * play_game(struct player * human , 
        struct player* computer)
{
    /* Declaration that allocates the board for the game */
    enum cell_contents board[BOARDHEIGHT][BOARDWIDTH];
	
	/* Declare current and other players */
    struct player *current = computer, *other = human;
	
	/* Initialise variable for checking winner */
	enum game_state winner;
    
	
	/* Seed for random value using the current time */
    srand(time(NULL));

	/* Get info about the human player */
    if(get_human_player(human) != SUCCESS)
		return NULL;
	
	/* Get info about the computer player */
    get_computer_player(computer);
	
	/* Initialise board, setting tokens to EMPTY */
    initialise_board(board);
	

	/* Continue playing game until winner is chosen */
    while((winner = test_for_winner(board)) == G_NO_WINNER) {
		/* Swap the current player with the other */
        swap_players(&current, &other);
		
		/* Display the board */
        display_board(board);

		/* Let current player take a turn */
        if(take_turn(current, board) == RTM)
			return NULL;
    }
	
	/* Revert player information back to original */
    swap_players(&current, &other);
    
	/* Check if winner is the PLAYER */
	if(winner == human->thiscolor) {
		printf("%s WINS!!", human->name);
		return human;
	}
	
	/* Check if winner is COMPUTER */
	else if(winner == computer->thiscolor) {
		printf("COMPUTER WINS!!");
		return computer;
	}
	
	/* Return that game ended in draw */
	else
		return NULL;
}

enum game_state test_for_winner(
        enum cell_contents board[][BOARDWIDTH])
{
	int i, j, k;
	
	/* DIAGONAL CHECKS */
	/* Bottom Right -> Top Left */
	for(i = BOARDHEIGHT - 1; i > 2; i--) {
		for(j = BOARDWIDTH - 1; j > 2; j--) {
			if(board[i][j] == C_EMPTY)
				continue;
			
			for(k = 0; k < 4; k++) {
				/* printf("1: Checking [%d][%d][%d]\n", i+1-k, j+1-k, k); */
				if(board[i][j] != board[i - k][j - k])
					break;
				
				else if(k >= 3)
					return board[i][j];
			}
			
		}
	}
	
	/* Bottom Left - Top Right */
	for(i = BOARDHEIGHT - 1; i > 2; i--) {
		for(j = 0; j < BOARDWIDTH - 3; j++) {
			if(board[i][j] == C_EMPTY)
				continue;
			
			for(k = 0; k < 4; k++) {
				/* printf("2: Checking [%d][%d][%d]\n", i+1-k, j+1+k, k); */
				if(board[i][j] != board[i - k][j + k])
					break;
				
				else if(k >= 3)
					return board[i][j];
			}
			
		}
	}
	
	/* HORIZONTAL CHECKS */
	for(i = BOARDHEIGHT - 1; i >= 0; i--) {
		for(j = BOARDWIDTH - 1; j > 2; j--) {
			if(board[i][j] == C_EMPTY)
				continue;
			
			for(k = 0; k < 4; k++) {
				/* printf("HRZ: Checking [%d][%d][%d]\n", i+1, j+1-k, k); */
				if(board[i][j] != board[i][j - k])
					break;
				
				else if(k >= 3)
					return board[i][j];
			}
		}
	}
	
	/* VERTICAL CHECKS */
	for(i = BOARDHEIGHT - 1; i > 2; i--) {
		for(j = BOARDWIDTH - 1; j >= 0; j--) {
			if(board[i][j] == C_EMPTY)
				continue;
			
			for(k = 0; k < 4; k++) {
				/* printf("VERT: Checking [%d][%d][%d]\n", i+1-k, j+1, k); */
				if(board[i][j] != board[i - k][j])
					break;
				
				else if(k >= 3)
					return board[i][j];
			}
		}
	}
	
	/* Check board for default value of no winner */
	for(i = 0; i < BOARDWIDTH; i++) {
		if(board[0][i] == C_EMPTY)
			return G_NO_WINNER;
	}

	/* Return that game ended in a draw */
	printf("Game has ended in a draw!\n\n");
	return G_DRAW;
}

