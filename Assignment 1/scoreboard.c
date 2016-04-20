/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include "scoreboard.h"

void init_scoreboard(scoreboard board)
{
	/* Initialise variable for loop */
	int i;
	
	/* Empty the board */
	for(i = 0; i < SCOREBOARDSIZE; i++) {
		/* Set an empty name */
		strcpy(board[i].name, "");
		
		/* Set counter to 0 */
		board[i].counters = 0;
		
		/* Set empty colour */
		board[i].thiscolor = 0;
		
		/* Set empty type */
		board[i].type = 0;
	}
}

void display_scores(const scoreboard board)
{
	/* Initialise variable for loop */
	int i;
	
	/* Check if there are valid scores to print */
	if(board[0].counters == 0) {
		printf("No scores to print!");
		return;
	}
	
	/* Output scoreboard */
	printf("\n\nPlayer		|Score\n");
	printf("-------------------------\n");
	for (i = 0; i < SCOREBOARDSIZE; i++) {
		/* Stop loop if current line is empty */
		if(board[i].counters == 0)
			break;
		
		/* Output player name and score */
		printf("%-16s|%d\n", 
			board[i].name,
			board[i].counters);
	}
}

BOOLEAN add_to_scoreboard(scoreboard board, const score * sc) 
{
	/* Initialise variables for loops */
	int i, j;
	
	for(i = 0; i < SCOREBOARDSIZE - 1; i++) {
		if(sc->counters >= board[i].counters) {
			
			/* Move all lower scores down */
			for(j = BOARDHEIGHT - 1; j > i; j--)
				board[j] = board[j-1];
			
			/* Set the (now empty) slot to winner */
			board[i] = *sc;
			
			/* Return function was successfull */
			return TRUE;
		}
	}
	
	/* Return default value */
	return FALSE;
}
