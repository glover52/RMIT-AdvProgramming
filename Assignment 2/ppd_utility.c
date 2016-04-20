/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2015 Assignment #2
 * Full Name        : Kyle Glover
 * Student Number   : s3539870
 * Course Code      : COSC1076
 * Program Code     : BP094
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/

#include "ppd_utility.h"
/**
 * @file ppd_utility.c contains implementations of important functions for
 * the system. If you are not sure where to implement a new function, 
 * here is probably a good spot.
 **/

void read_rest_of_line(void)
{
    int ch;
    /* keep retrieving characters from stdin until we
     * are at the end of the buffer
     */
    while(ch = getc(stdin), ch!='\n' && ch != EOF)
        ;
    /* reset error flags on stdin */
    clearerr(stdin);
}

/**
 * @param system a pointer to a @ref ppd_system struct that contains
 * all the data in the system we are manipulating
 * @param coins_name the name of the coins file
 * @param stock name the name of the stock file
 **/
BOOLEAN load_data(struct ppd_system * system , const char * coins_name, 
const char * stock_name)
{
    FILE *coins_file, *stock_file;
	char line[256], *token, *token2, *end, *save1, *save2;
	int tok_id, denom_id, number;
	
	struct ppd_node *current;
	
	/* Assign file names to pointers */
	system->coin_file_name = coins_name;
	system->stock_file_name = stock_name;
	
	/* Open files with 'reading' permissions */
	coins_file = fopen(coins_name, "r");
	stock_file = fopen(stock_name, "r");
	
	/* Check for failure in opening files */
	if(coins_file == NULL || stock_file == NULL)
		return FALSE;
	
	/** COIN FILE **/
	denom_id = 0;
	
	/* Loop to load data from the coin file */
	while(fgets(line, MAX_COIN_LEN + 1, coins_file) != NULL) {
		
		/* Prevent a lone '\n' from causing trouble */
		if(line[0] == '\n')
			continue;
		
		/* Set/Reset token_id to 0 */
		tok_id = 0;
		
		/* Remove the new line character */
		if(line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		
		/* Tokenises the given line */
		token = strtok(line, COIN_DELIM);
		
		while(token != NULL) {
			number = (int) strtol(token, &end, 10);
			
			/* Check if given token is an int */
			if(*end)
			{
				printf("Failed to convert '%s' into integer.\n", token);
				return FALSE;
			}
			
			if(tok_id == COIN_DENOM_ID)
				system->cash_register[denom_id].denom = int_to_id(number);

			else if(tok_id == COIN_COUNT_ID)
				system->cash_register[denom_id].count = number;
				
			token = strtok(NULL, COIN_DELIM);
		
			tok_id++;
		}
		denom_id++;
	}
	
	/** STOCK FILE **/
	/* Loop to load data from the stock file */
	while(fgets(line, sizeof(line), stock_file) != NULL) {	
	
		/* Prevent a lone '\n' from causing trouble */
		if(line[0] == '\n')
			continue;
		
		/* Set/Reset token_id to 0 */
		tok_id = 0;
		
		/* Remove the new line character */
		if(line[strlen(line) - 1] == '\n')
			line[strlen(line) - 1] = '\0';
		
		/* Tokenises the given line */
		token = strtok_r(line, STOCK_DELIM, &save1);
		
		/* Allocate spot on heap for the working node */
		current = malloc(sizeof(struct ppd_node));
		current->data = malloc(sizeof(struct ppd_stock));
		
		while(token != NULL) {
			switch(tok_id) {
				case STOCK_ID:
					strncpy(current->data->id, token, IDLEN+1);
					break;
					
				case STOCK_NAME:
					strncpy(current->data->name, token, NAMELEN+1);
					break;
					
				case STOCK_DESC:
					strncpy(current->data->desc, token, DESCLEN+1);
					break;
					
				case STOCK_PRICE:
					token2 = strtok_r(token, PRICE_DELIM, &save2);
					number = (int) strtol(token2, &end, 10);
					
					if(*end)
					{
						printf("Failed to convert '%s' into number\n", token2);
						return FALSE;
					}
					current->data->price.dollars = number;
					
					
					token2 = strtok_r(NULL, PRICE_DELIM, &save2);
					
					number = (int) strtol(token2, &end, 10);
					if(*end)
					{
						printf("Failed to convert '%s' into number\n", token2);
						return FALSE;
					}
					current->data->price.cents = number;
					break;
					
				case STOCK_AMOUNT:
					current->data->on_hand = strtol(token, &end, 10);
					break;
			}
			token = strtok_r(NULL, STOCK_DELIM, &save1);
			tok_id++;
		}
		
		add_list_node(system->item_list, current);
	}
	
	fclose(coins_file);
	fclose(stock_file);
    return TRUE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/
BOOLEAN system_init(struct ppd_system * system)
{
	memset(system->cash_register, 0, sizeof(int) * NUM_DENOMS);
	system->item_list = malloc(sizeof(struct ppd_list));
	system->item_list->count = 0;
	system->coin_file_name = NULL;
	system->stock_file_name = NULL;
	return TRUE;
}

/**
 * @param system a pointer to a @ref ppd_system struct that holds all 
 * the data for the system we are creating
 **/
void system_free(struct ppd_system * system)
{
	struct ppd_node *current, *next;
	current = system->item_list->head;
	
	while(current != NULL)
	{
		next = current->next;
		free(current->data);
		free(current);
		current = next;
	}
	
	free(system->item_list);
}

int get_user_input(char * input, int input_size) 
{
		/* Checks for Ctrl-D & no character */
		if(fgets(input, input_size, stdin) == NULL || strlen(input) == 1)
			return RTM;
		
		/* Remove the new line character */
		if(input[strlen(input) - 1] == '\n')
			input[strlen(input) - 1] = '\0';
		
		else
		{
			read_rest_of_line();
			return FAILURE;
		}
		
		return SUCCESS;
}

