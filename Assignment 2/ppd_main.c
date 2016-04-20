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

#include "ppd_main.h"

/**
 * @file ppd_main.c contains the main function implementation and any 
 * helper functions for main such as a display_usage() function.
 **/

/**
 * manages the running of the program, initialises data structures, loads
 * data and handles the processing of options. The bulk of this function
 * should simply be calling other functions to get the job done.
 **/
int main(int argc, char **argv)
{	
	/* Represents the data structures to manage the system */
    struct ppd_system system;
	struct menu_item menu[NUM_MENU_ITEMS];
	char input[NUM_MENU_INPUT], *error;
	int option,	i;
	BOOLEAN exit = FALSE;
	
    /* Validate command line arguments */
	if ( argc != NUM_ARGS)
	{
		printf("Usage: ./playme <stock> <coins>\n\n");
		return EXIT_FAILURE;
	}
	
	else
	{
		if(argv[ITEM_FILE_INDEX] == 0)
		{
			printf("stock_file failed!\n");
			printf("Please make sure to input file name correctly.\n\n");
			return EXIT_FAILURE;
		}
		
		if(argv[COIN_FILE_INDEX] == 0)
		{
			printf("coins_file failed!\n");
			printf("Please make sure to input file name correctly.\n\n");
			return EXIT_FAILURE;
		}
	}
	
    /* Init the system */
	if(system_init(&system) != TRUE)
	{
		printf("System failed to initialise!\n");
		system_free(&system);
		return EXIT_FAILURE;	
	}

    /* Load data */
	if(load_data(&system, argv[COIN_FILE_INDEX], argv[ITEM_FILE_INDEX]) != TRUE)
	{
		printf("Failed to load data!\n");
		system_free(&system);
		return EXIT_FAILURE;
	}

    /* Test if everything has been initialised correctly */
	#if 0
	if(!display_items(&system) || !display_coins(&system))
		abort_program(&system);
	#endif
	
    /* Initialise the menu system */
	init_menu(menu);
	
	while(!exit)
	{
		/* Loop, asking for options from the menu */
		for(i = 0; i < NUM_MENU_ITEMS; i++)
		{
			if(i == SELECT_DEFAULT)
				printf("\n\n== Default Selections ==\n========================\n");
		
			else if(i == SELECT_ADMIN)
				printf("\n== Admin Selections ==\n========================\n");
		
			printf("%d. %s\n", i + 1, menu[i].name);
		}
		
		while(!exit) {
			printf("\nPlease select what you would like to do: ");
			
			/* Get user input and assign to variable */
			i = get_user_input(input, NUM_MENU_INPUT);
			
			/* Check for return to menu */
			if(i == RTM)
			{
				printf("You have no where to return to!\n");
				continue;
			}
			
			/* Check for invalid input */
			if(i == FAILURE)
			{
				printf("Your text was too long!\n");
				continue;
			}
			
			/* Convert given input to int and assign to option */
			option = (int) strtol(input, &error, 0) - 1;
			
			/* Check if converted string inside menu range */
			if(option >= 0 && option <= NUM_MENU_ITEMS)
				exit = TRUE;
			
			/* For all other values, echo output outside of range */
			else
				printf("Input outside of range!\n");
		}
		
		/* Reset exit BOOLEAN for part 2 */
		exit = FALSE;
		
		/* Run each option selected */
		if(menu[option].function(&system) != TRUE)
			printf("Option '%s' failed to complete!\n", menu[option].name);
	}
    return EXIT_SUCCESS;
}


