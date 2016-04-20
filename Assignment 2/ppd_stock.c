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
#include "ppd_stock.h"

 /**
  * @file ppd_stock.c this is the file where you will implement the 
  * interface functions for managing the stock list.
  **/

BOOLEAN load_stock_data(struct ppd_system * system)
{
	return FALSE;
}

BOOLEAN add_list_node(struct ppd_list * list, struct ppd_node * node)
{
	int result;
	struct ppd_node * current, * prev = NULL;
	
	/* Check if there is nothing in the list */
	if(list->count == 0)
	{
		node->next = NULL;
		list->head = node;
		list->count++;
		
		return TRUE;
	}
	
	/* Check current list for alphabetical order */
	current = list->head;
	while(current != NULL)
	{
		result = strcmp(current->data->name, node->data->name);
		
		if(result >= 0)
			break;
		
		prev = current;
		current = current->next;
	}

	/* Return if names are the same */
	if(result == 0)
		return FALSE;
	
	/* First node in list is greater than entered node */
	if(prev == NULL)
	{
		/* Swap nodes */
		node->next = current;
		list->head = node;
	}
	
	/* Reached the end of the list (standard) */
	else if(current == NULL)
	{
		prev->next = node;
		node->next = NULL;
	}
	
	/* Curent node is greater than entered node */
	else
	{
		node->next = current;
		prev->next = node;
	}
	
	/* Increment list count for new item */
	++list->count;
	
	return TRUE;
}

BOOLEAN save_stock_data(struct ppd_system * system, FILE* stock_file)
{
	struct ppd_node *current = system->item_list->head;
	
	/* Check if node is NULL (is error)*/
	if(current == NULL)
		return FALSE;
	
	/* Loop for writing lines to file */
	while(current != NULL)
	{
		/* Output given line to file */
		fprintf(stock_file, "%s%s%s%s%s%s%.0d%s%.2d%s%d\n",
			current->data->id,
			STOCK_DELIM,
			current->data->name,
			STOCK_DELIM,
			current->data->desc,
			STOCK_DELIM,
			current->data->price.dollars,
			PRICE_DELIM,
			current->data->price.cents,
			STOCK_DELIM,
			current->data->on_hand
		);
		
		/* Assign next node in list to current */
		current = current->next;
	}
	
	return TRUE;
}