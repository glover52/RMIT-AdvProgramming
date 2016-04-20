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

#include "ppd_options.h"

/**
 * @file ppd_options.c this is where you need to implement the main 
 * options for your program. You may however have the actual work done
 * in functions defined elsewhere. 
 * @note if there is an error you should handle it within the function
 * and not simply return FALSE unless it is a fatal error for the 
 * task at hand. You want people to use your software, afterall, and
 * badly behaving software doesn't get used.
 **/

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this particular function should never fail.
 **/
BOOLEAN display_items(struct ppd_system * system)
{
	struct ppd_node *current = system->item_list->head;
	
	/* Output menu header */
	printf("\n\nItems Menu\n==========\n");
	printf("ID    | Name                | Available | Price\n");
	printf("===============================================\n");
	
	/* Loop to output stock information */
	while(current != NULL)
	{			
		/* Output current node information */
		printf("%-6s| %-20s| %-10d|$ %d.%.2d\n",
			current->data->id,
			current->data->name,
			current->data->on_hand,
			current->data->price.dollars,
			current->data->price.cents
		);
		
		/* Assign next node in list to working node */
		current = current->next;
	}
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a purchase succeeds and false when it does not
 **/
BOOLEAN purchase_item(struct ppd_system * system)
{
	int item_price, coin_given, i;
	int coins_given[NUM_DENOMS];
	BOOLEAN exit = FALSE;
	char input[IDLEN+2], *end;
	struct ppd_node *current = system->item_list->head;
	
	/* Initialise the coins_given array */
	for(i = 0; i < NUM_DENOMS; i++)
		coins_given[i] = 0;
	
	printf("\n\n== Purchase Item ==\n");
	printf("===================\n");
	
	while(!exit) {
		printf("Please enter the ID of the item you wish to purchase: ");
	
		/* Get user input and assign to variable */
		i = get_user_input(input, IDLEN+2);
		
		/* Check if user wants to return to menu */
		if(i == RTM)
			return FALSE;
		
		/* Check returned value for failure */
		if(i == FAILURE)
		{
			printf("The provided item ID was too long!\n");
			continue;
		}
	
		/* Search for given ID */
		current = system->item_list->head;
		while(current != NULL)
		{
			if(strcmp(input, current->data->id) == 0) {
				printf("Found id: %s\n", input);
				
				if(current->data->on_hand > 0)
					exit = TRUE;
		
				else
					printf("This item has run out of stock! Please pick another.\n");
				
				break;
			}
			
			if(current->next == NULL) {
				printf("Couldn't find id: %s.\n", input);
				break;
			}
			current = current->next;
		}
	}
	
	exit = FALSE;
	printf("You have selected '%s - %s'.\n", current->data->name, current->data->desc);
	printf("This will cost you $%d.%.2d\n", current->data->price.dollars, current->data->price.cents);
	
	printf("\nTo pay, type in the value of each note/coin in cents.\n");
	printf("Press enter or ctrl-d on a new line to cancel purchase.\n");
	
	item_price = (current->data->price.dollars * 100) + current->data->price.cents;
	while(!exit) {
		printf("You still need to give us $%d.%.2d: ", 
			(int) item_price/100, 
			item_price%100
		);
		
		/* Get user input and remove new line character */
		if(get_user_input(input, IDLEN+2) == RTM)
		{
			printf("\nPurchase cancelled, refunding your money and returning to menu.\n");
			for(i = 0; i < NUM_DENOMS; i++)
			{
				while(coins_given[i] != 0)
				{
					if(FIVE_CENTS == i)
						printf("5c ");
					
					if(TEN_CENTS == i)
						printf("10c ");
					
					if(TWENTY_CENTS == i)
						printf("20c ");
					
					if(FIFTY_CENTS == i)
						printf("50c ");
					
					if(ONE_DOLLAR == i)
						printf("$1 ");
					
					if(TWO_DOLLARS == i)
						printf("$2 ");
					
					if(FIVE_DOLLARS == i)
						printf("$5 ");
					
					if(TEN_DOLLARS == i)
						printf("$10 ");
					
					--coins_given[i];
				}
			}
			printf("\n");
			return FALSE;
		}
		
		/* Convert input to number */
		coin_given = strtol(input, &end, 10);
		
		/* Check  entered coin/note */
		if(coin_given == FIVE_CENTS_VALUE)
			++coins_given[FIVE_CENTS];
		
		else if(coin_given == TEN_CENTS_VALUE)
			++coins_given[TEN_CENTS];
		
		else if(coin_given == TWENTY_CENTS_VALUE)
			++coins_given[TWENTY_CENTS];
		
		else if(coin_given == FIFTY_CENTS_VALUE)
			++coins_given[FIFTY_CENTS];
		
		else if(coin_given == ONE_DOLLAR_VALUE)
			++coins_given[ONE_DOLLAR];
		
		else if(coin_given == TWO_DOLLARS_VALUE)
			++coins_given[TWO_DOLLARS];
		
		else if(coin_given == FIVE_DOLLARS_VALUE)
			++coins_given[FIVE_DOLLARS];
		
		else if(coin_given == TEN_DOLLARS_VALUE)
			++coins_given[TEN_DOLLARS];
		
		else
		{
			printf("You must enter a valid Australian coin/note!\n");
			continue;
		}
		
		/* Continue if given coin does not exceed or equal lowered price */
		if((item_price -= coin_given) <= 0)
			exit = TRUE;
	}
	
	/* Output that price has been met and current change */
	printf("Thank you! Here is your %s", current->data->name);
	
	if(item_price < 0)
		printf(", and your change of $%d.%.2d:", 
			(int) -item_price/100, 
			-item_price%100
		);
	printf("\n");
	
	/* Input given coins into register */
	for(i = 0; i < NUM_DENOMS; i++)
	{
		while(coins_given[i] != 0)
		{
			++system->cash_register[i].count;
			--coins_given[i];
		}
	}
	
	/* Decrease purchased item quantity */
	--current->data->on_hand;

	/* Output any change */
	while(item_price < 0) {
		if(item_price <= -TEN_DOLLARS_VALUE) {
			--system->cash_register[TEN_DOLLARS].count;
			item_price += TEN_DOLLARS_VALUE;
			printf("$10 ");
			
		} else if(item_price <= -FIVE_DOLLARS_VALUE) {
			--system->cash_register[FIVE_DOLLARS].count;
			item_price += FIVE_DOLLARS_VALUE;
			printf("$5 ");
			
		} else if(item_price <= -TWO_DOLLARS_VALUE) {
			--system->cash_register[TWO_DOLLARS].count;
			item_price += TWO_DOLLARS_VALUE;
			printf("$2 ");
			
		} else if(item_price <= -ONE_DOLLAR_VALUE) {
			--system->cash_register[ONE_DOLLAR].count;
			item_price += ONE_DOLLAR_VALUE;
			printf("$1 ");
			
		} else if(item_price <= -FIFTY_CENTS_VALUE) {
			--system->cash_register[FIFTY_CENTS].count;
			item_price += FIFTY_CENTS_VALUE;
			printf("50c ");
			
		} else if(item_price <= -TWENTY_CENTS_VALUE) {
			--system->cash_register[TWENTY_CENTS].count;
			item_price += TWENTY_CENTS_VALUE;
			printf("20c ");
			
		} else if(item_price <= -TEN_CENTS_VALUE) {
			--system->cash_register[TEN_CENTS].count;
			item_price += TEN_CENTS_VALUE;
			printf("10c ");
			
		} else if(item_price <= -FIVE_CENTS_VALUE) {
			--system->cash_register[FIVE_CENTS].count;
			item_price += FIVE_CENTS_VALUE;
			printf("5c ");
		}
	}

    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when a save succeeds and false when it does not
 **/
BOOLEAN save_system(struct ppd_system * system)
{
	FILE *coins_file, *stock_file;	
	int i;
	
	/* Open files with 'write' permissions and assign to variables */
	coins_file = fopen(system->coin_file_name, "w");
	stock_file = fopen(system->stock_file_name, "w");
	
	/* Check for failure in opening files */
	if(coins_file == NULL || stock_file == NULL)
	{
		printf("One or more files failed to open!\n");
		return FALSE;
	}
	
	/* Coin File section */
	for(i = 0; i < NUM_DENOMS; i++)
	{	
		fprintf(coins_file, "%d%s%d\n", 
			id_to_int(system->cash_register[i].denom),
			COIN_DELIM,
			system->cash_register[i].count
		);
	}
	
	fclose(coins_file);
	printf("\n'%s' was saved successfully!\n", system->coin_file_name);
	
	/* Save all stock information to given file */
	printf("'%s' ", system->stock_file_name);
	
	if(!save_stock_data(system, stock_file))
		printf("failed to save!\n");
	
	else
		printf("was saved successfully!\n");
	
	/* Close opened stock file */
	fclose(stock_file);
	
	printf("Exiting program.\n\n");
	
    /* Free all allocated memory */
	system_free(system);
	
	/* Exit the system */
	exit(EXIT_SUCCESS);
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when adding an item succeeds and false when it does not
 **/
BOOLEAN add_item(struct ppd_system * system)
{
	BOOLEAN exit = FALSE;
	
	struct ppd_node *current = system->item_list->head, *new_item;
	
	char *token,
		*end,
		new_id[IDLEN],
		new_name[NAMELEN], 
		new_desc[DESCLEN],
		new_price[PRICELEN];
	
	int new_id_int = 0, stock_price;
	
	BOOLEAN price_dollar;
	
	new_item = malloc(sizeof(struct ppd_node));
	new_item->data = malloc(sizeof(struct ppd_stock));
	new_item->next = NULL;
	
	printf("\n\n== Add Item ==\n");
	printf("==============\n");
	
	/* Loop through list and find max number */
	while (current != NULL)
	{
		token = strtok(current->data->id, "I");
	
		if(((int) strtol(token, &end, 10)) > new_id_int)
			new_id_int = (int) strtol(token, &end, 10);
		
		current = current->next;
	}
	
	/* Increment max number by one */
	++new_id_int;
	
	/* Find max number in list and increment by one */
	
	if(new_id_int < MAX_STOCK)
		sprintf(new_id, "I%04d", new_id_int);
		
	else {
		printf("Maximum items reached, please first delete an item to continue.\n");
		printf("Returning to menu.\n");
		return FALSE;
	}
	
	strncpy(new_item->data->id, new_id, IDLEN);
	printf("\nNew meal item will have Item id of: %s\n", new_id);
	printf("- - - - - - - - - - - - - - - - - - -\n");
	
	/* Loop for entering new_item name */
	while(!exit) {
		printf("Enter the new item name: ");
		
		/* Checks for Ctrl-D & no character */
		if(get_user_input(new_name, NAMELEN+2) == RTM) {
			
			/* Free new_item allocated memory */
			free(new_item->data);
			free(new_item);
			
			printf("\nItem add cancelled. Returning to menu.\n");
			return FALSE;
		}
		
		strncpy(new_item->data->name, new_name, NAMELEN);
		
		exit = TRUE;
	}
	
	/* Loop for entering new_item description */
	exit = FALSE;
	while(!exit) {
		printf("\nEnter the new item description: ");
		
		/* Checks for Ctrl-D & no character */
		if(get_user_input(new_desc, DESCLEN+2) == RTM) {
			
			/* Free new_item allocated memory */
			free(new_item->data);
			free(new_item);
			
			printf("\nItem add cancelled. Returning to menu.\n");
			return FALSE;
		}
		
		strncpy(new_item->data->desc, new_desc, DESCLEN);
		exit = TRUE;
	}
	printf("\n");
	
	/* Loop for entering new_item price */
	exit = FALSE;
	while(!exit) {
		printf("Enter the new item price: ");
		
		/* Checks for Ctrl-D & no character */
		if(get_user_input(new_price, 7) == RTM) {
			
			/* Free new_item allocated memory */
			free(new_item->data);
			free(new_item);
			
			printf("\nItem add cancelled. Returning to menu.\n");
			return FALSE;
		}
		
		token = strtok(new_price, PRICE_DELIM);
		
		price_dollar = TRUE;
		while(token != NULL)
		{
			stock_price = (int) strtol(token, &end, 10);
			
			if(*end)
			{
				printf("Failed to convert '%s' into number!\n", token);
				break;
			}
			
			if(price_dollar == TRUE)
			{
				new_item->data->price.dollars = stock_price;
				price_dollar = FALSE;
			}
			else
			{
				if(stock_price != 0)
				{
					if(stock_price % FIVE_CENTS_VALUE != 0 
						|| stock_price > MAX_CENT_VALUE)
					{
						printf("Invalid cent value '%d'!\n", stock_price);
						break;
					}
				}
				new_item->data->price.cents = stock_price;
				exit = TRUE;
			}
			token = strtok(NULL, PRICE_DELIM);
		}
	}
	
	new_item->data->on_hand = DEFAULT_STOCK_LEVEL;
	
	add_list_node(system->item_list, new_item);
	
	printf("\nItem: '%s - %s' has been added to the menu!\n",  
		new_item->data->name, 
		new_item->data->desc
	);
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true when removing an item succeeds and false when it does not
 **/
BOOLEAN remove_item(struct ppd_system * system)
{
	BOOLEAN exit = FALSE;
	
	char input[IDLEN];
	
	struct ppd_node *current = system->item_list->head, *prev;
	
	printf("\n\n== Remove Item ==\n");
	printf("================\n");
	
	if(system->item_list->count == 0)
	{
		printf("Current item list is empty! Please add menu items.\n");
		return FALSE;
	}
		
	while(!exit)
	{
		printf("Enter the item id of item to remove from the menu: ");
		
		if(get_user_input(input, IDLEN+2) == RTM)
		{
			printf("\nItem removal cancelled. Returning to menu.\n");
			return FALSE;
		}
		
		
		while(current != NULL)
		{
			if(strcmp(input, current->data->id) == 0)
			{
				exit = TRUE;
				printf("Found id: %s\n", input);
				break;
			}
			
			if(current->next == NULL)
			{
				printf("Couldn't find id: %s.\n", input);
				break;
			}
			
			prev = current;
			current = current->next;
		}
	}
	
	printf("'%s - %s - %s'\nhas been removed from the system.\n",
		current->data->id,
		current->data->name,
		current->data->desc
	);
	
	/* Begin reorganising the list */
	if(strcmp(system->item_list->head->data->id, current->data->id) == 0)
		system->item_list->head = current->next;
	
	else
		prev->next = current->next;
	
	--system->item_list->count;
	
	/* Free the allocated data for the item */
	free(current->data);
	free(current);
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_stock(struct ppd_system * system)
{
	/* Assign working node to list head */
	struct ppd_node *current = system->item_list->head;
	
	/* Loop until current node is NULL */
	while(current != NULL)
	{
		/* Set on_hand stock amount to default */
		current->data->on_hand = DEFAULT_STOCK_LEVEL;
		
		/* Set the working node to the next node in the list */
		current = current->next;
	}
	
	printf("Each stock item has been reset to default amount of %d.\n", 
		DEFAULT_COIN_COUNT
	);
	
    return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail.
 **/
BOOLEAN reset_coins(struct ppd_system * system)
{
	int i;
	
	/* Iterate over every coin and set count to default */
	for(i = 0; i < NUM_DENOMS; i++)
		system->cash_register[i].count = DEFAULT_COIN_COUNT;
	
	/* Output all coins have been reset */
	printf("All coins have been reset to default level of %d.\n", 
		DEFAULT_COIN_COUNT
	);
    
	/* Return function was successfull */
	return TRUE;
}

/**
 * @param system a pointer to a  ppd_system struct that contains 
 * all the information for managing the system.
 * @return true as this function cannot fail
 **/
BOOLEAN display_coins(struct ppd_system * system)
{
	int i;
	char * denom_array[] = {
		"5 cents",
		"10 cents",
		"20 cents",
		"50 cents",
		"1 dollar",
		"2 dollars",
		"5 dollars",
		"10 dollars"
	};
	
	printf("\n\nCoins Summary\n");
	printf("==============\n");
	printf("Denomination | Count\n");
	printf("=====================\n");
	
	for(i = 0; i < NUM_DENOMS; i++)
		printf(" %-11s | %d\n", 
			denom_array[i], 
			system->cash_register[i].count
		);
	
	return TRUE;
}

BOOLEAN abort_program(struct ppd_system * system)
{
	/* Free all allocated memory */
	system_free(system);
	
	/* Exit the system */
	exit(EXIT_SUCCESS);
}
