/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include "con4.h"

int main(void)
{    
	char input[3];
	BOOLEAN exit;
	
    /* the scoreboard for keeping track of winners */
    scoreboard scores;
	
    /* the two players and a pointer to who won the last game */
    struct player human_player, computer_player, *winner;

    /* initialise the scoreboard */
    init_scoreboard(scores);

    /*display menu and get menu choice until the user chooses to quit */
    while(TRUE) {
		/* Declare boolean & redeclare after loop end */
		exit = FALSE;
		
		/* Output menu */
        printf("\n\nWelcome to connect 4!\n");
        printf("---------------------\n");
        printf("1. Play Game\n2. Display High Scores\n3. Quit");
        
		/* Get input from user */
		while (!exit) {
			do {
				printf("\nPlease enter your choice (1 - 3): ");
				
				/* Obtain user input */
				fgets(input, 3, stdin);
				
				if(input[strlen(input) - 1] != '\n') {
					printf("\nInput too long!");
					
					/* Flush the input buffer */
					read_rest_of_line();
	
				} else if((strlen(input) - 1) == 0) {
					printf("You must enter a value!\n");
					
				} else {
					/* Remove '\n' character */
					input[strlen(input) - 1] = '\0';
					
					/* Allow user to exit loop */
					exit = TRUE;
				}
			} while(!exit);
    
			switch(input[0]) {
				case '1':
					/* Play Game */
					winner = play_game(&human_player, &computer_player);
				
					/* If the game was not a draw, add winner to scoreboard */
					if(winner != NULL)
						add_to_scoreboard(scores, winner);
				
					break;
				
				case '2':
					/* Display High Scores */
					display_scores(scores);
					break;

				case '3': /* Quit */
					printf("Exiting the game. Thank you for playing.\n\n");
					
					/* Quit the program option */
					return EXIT_SUCCESS;

				default:
					/* Output default error message */
					printf("ERROR: Please select a number from 1-3\n\n");
					break;
			}
		}
	}
}
