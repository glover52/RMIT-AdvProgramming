/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include "player.h"

enum input_result get_human_player(struct player* human)
{
	BOOLEAN exit = FALSE;
	
	do {
		/* Prompt user to enter a name, or return if 'Ctrl-D' entered */
		printf("Please enter username: ");
		
		if(fgets(human->name, NAMELEN+1, stdin) == NULL)
			return RTM;
	
		/* Check if user entered value */
		if((strlen(human->name) - 1) == 0)
			printf("\nYou must enter a value!\n");
	
		/* Exit loop */
		else
			exit = TRUE;
		
	} while(!exit);
	
	/* Set the name of the player */
	human->name[strlen(human->name) - 1] = '\0';
	
	/* Set the current token counter to 0 */
	human->counters = 0;
	
	/* Assign the colour of player */
	human->thiscolor = C_RED;
	
	/* Assign this player as HUMAN */
    human->type = HUMAN;
	
    return SUCCESS;
}

enum input_result get_computer_player(struct player * computer)
{
	/* Assign the name to the player */
	strcpy(computer->name, "COMPUTER"); 
	
	/* Set the counter to 0 */
	computer->counters = 0;
	
	/* Set the colour of the player */
	computer->thiscolor = C_WHITE;
	
	/* Set the type of player */
    computer->type = COMPUTER;

    return SUCCESS;
}

enum input_result take_turn(struct player * current,
        enum cell_contents board[][BOARDWIDTH])
{
    char input[3], *error;
    int column, row;
	BOOLEAN exit = FALSE;
	
    switch(current->type) {
        case HUMAN:
			/* Notify user of turn */
            printf("%s's turn!", current->name);
			
			/* Only allow player to exit if coords empty */
			do {
				printf("\nColumn number (1 - 7): ");
					
				/* Get column number */
				if(fgets(input, 3, stdin) == NULL)
					return RTM;
			
				if(input[strlen(input) - 1] != '\n') {
					printf("\nInput too long!");
					
					/* Flush input buffer */
					read_rest_of_line();
			
				} else {
					/* Remove new line character */
					input[strlen(input) - 1] = '\0';
					
					/* Change given string to an int */
					column = (int) strtol(input, &error, 10) - 1;
					
					/* Check if given column is in limit */
					if(column >= BOARDWIDTH || column < 0)
						printf("Column out of range!\n");
			
					/* Check if given column is full */
					else if(board[0][column] != C_EMPTY)
						printf("Column full!\n");
					
					/* Allow user to exit loop */
					else
						exit = TRUE;
				}
			} while(!exit);
			
			/* Find empty token in column */
            for(row = BOARDHEIGHT - 1; row >= 0; row--) {
				
				/* Check if row is empty and provide token */
                if(board[row][column] == C_EMPTY) {
					
					/* Exit loop */
                    break;
                }
            }
			
			/* Change coords token */
			board[row][column] = current->thiscolor;
			
			/* Increment counter */
			current->counters++;
			
			/* Return function was successfull */
            return SUCCESS;

        case COMPUTER:
			/* Notify user of turn */
            printf("Computer turn!\n");

			/* Go through loop until free token is found */
			do {
				/* Select a random number in given range */
				column = rand() % BOARDWIDTH;
				
				/* Check column for free token */
				for(row = BOARDHEIGHT - 1; row > 0; row--) {
					
					/* Exit loop if selected row is free */
					if(board[row][column] == C_EMPTY) {
						
						/* Output empty coords for debugging */
						printf("Computer used [%d][%d]\n", row + 1, column + 1);
					
						/* Exit loop */
						break;
					}
				}
			} while(board[row][column] != C_EMPTY);
			
			/* Change coords token */
			board[row][column] = current->thiscolor;
			
			/* Increment counter */
			current->counters++;
			
			/* Return function was successfull */
            return SUCCESS;

        default:
            printf("player.c: Could not select player!\n");
            return EXIT_SUCCESS;
    }
}
