/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include "board.h"
#include "player.h"

void initialise_board(enum cell_contents board[][BOARDWIDTH])
{
	/* Initialise variables */
    int i, j;
	
	/* Go through whole board */
    for(i = 0; i < BOARDHEIGHT; i++) {
        for(j = 0; j < BOARDWIDTH; j++) {
			/* Empty the board */
            board[i][j] = C_EMPTY;
        }
    }
}

void display_board(enum cell_contents board[][BOARDWIDTH])
{
	/* Initialise variables */
    int i, j;
	
	/* Output greetings & board columns */
    printf("\nWelcome to Connect4!\n");
    printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
    printf("----------------------------|\n");
	
	/* Check the value of given coords and print related token */
    for(i = 0; i < BOARDHEIGHT; i++){
        for(j = 0; j < BOARDWIDTH; j++) {
			
			/* Switch between token states */
            switch(board[i][j]) {
                case C_RED:
                    printf("| %s ", RED_TOKEN);
                    break;

                case C_WHITE:
                    printf("| %s ", WHITE_TOKEN);
                    break;

                default:
                    printf("|   ");
                    break;
            }
        }
        printf("|\n----------------------------|\n");
    }
}
