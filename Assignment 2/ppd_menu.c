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

#include "ppd_menu.h"
/**
 * @file ppd_menu.c handles the initialised and management of the menu 
 * array
 **/

/**
 * @param menu the menu item array to initialise
 **/
void init_menu( struct menu_item* menu)
{
	/* Strings names of menu items */
	char * menu_items[] = {
		"Display Items",
		"Purchase Items",
		"Save and Exit",
		"Add Item",
		"Remove Item",
		"Display Coins",
		"Reset Stock",
		"Reset Coins",
		"Abort Program"
	};
	
	/* Function pointer for the menu items */
	BOOLEAN (*menu_functions[])(struct ppd_system *) = {
		display_items,
		purchase_item,
		save_system,
		add_item,
		remove_item,
		display_coins,
		reset_stock,
		reset_coins,
		abort_program
	};
	
	int i;
	for(i = 0; i < NUM_MENU_ITEMS; i++)
	{
		/* Assign function from the function pointer */
		menu[i].function = menu_functions[i];
		
		/* Copy name of item to selected menu item */
		strncpy(menu[i].name, menu_items[i], MENU_NAME_LEN);
	}
}
