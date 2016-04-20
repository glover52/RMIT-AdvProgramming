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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include "ppd_coin.h"

#ifndef PPD_STOCK
#define PPD_STOCK
#define STOCK_DELIM "|"
#define PRICE_DELIM "."

#define STOCK_ID 0
#define STOCK_NAME 1
#define STOCK_DESC 2
#define STOCK_PRICE 3
#define STOCK_AMOUNT 4

/**
 * @file ppd_stock.h this file defines the data structures required to 
 * manage the stock list. You should add here the function prototypes for
 * managing the list here and implement them in ppd_stock.c
 **/

/**
 * The length of the id string not counting the nul terminator
 **/
#define IDLEN 5

/**
 * The maximum length of a product name not counting the nul terminator
 **/
#define NAMELEN 40

/**
 * The maximum length of a product description not counting the nul
 * terminator.
 **/
#define DESCLEN 255

#define PRICELEN 5
/**
 * The default coin level to reset the coins to on request
 **/
#define DEFAULT_COIN_COUNT 20

/**
 * The default stock level that all new stock should start at and that 
 * we should reset to on restock
 **/
#define DEFAULT_STOCK_LEVEL 20

/**
 * The number of denominations of currency available in the system 
 **/
#define NUM_DENOMS 8

#define MAX_STOCK 10000

/**
 * a structure to represent a price. One of the problems with the floating
 * point formats in C like float and double is that they have minor issues
 * of inaccuracy due to rounding. In the case of currency this really is
 * not acceptable so we introduce our own type to keep track of currency.
 **/
struct price
{
    /**
     * the dollar value for some price
     **/
    unsigned dollars, 
             /**
              * the cents value for some price
              **/
             cents;
};

/**
 * data structure to represent a stock item within the system
 **/
struct ppd_stock
{
    /**
     * the unique id for this item
     **/
    char id[IDLEN + 1];
    /**
     * the name of this item
     **/
    char name[NAMELEN + 1];
    /**
     * the description of this item
     **/
    char desc[DESCLEN + 1];
    /**
     * the price of this item
     **/
    struct price price;
    /**
     * how many of this item do we have on hand? 
     **/
    unsigned on_hand;
    /**
     * a pointer to the next node in the list
     **/
};

/**
 * the node that holds the data about an item stored in memory
 **/
struct ppd_node
{
    /* pointer to the data held for the node */
    struct ppd_stock * data;
    /* pointer to the next node in the list */
    struct ppd_node * next;
};

/**
 * the list of products - each link is the list is a @ref ppd_node
 **/
struct ppd_list
{
    /**
     * the beginning of the list
     **/
    struct ppd_node * head;
    /**
     * how many nodes are there in the list?
     **/
    unsigned count;
};

/**
 * this is the header structure for all the datatypes that is 
 * passed around and manipulated
 **/
struct ppd_system
{
    /**
     * the container for all the money manipulated by the system
     **/
    struct coin cash_register[NUM_DENOMS];

    /**
     * the linked list - note that this is a pointer - how does that
     * change what we need to do for initialization of the list?
     **/
    struct ppd_list * item_list;

    /**
     * the name of the coin file - we need this for saving as all menu
     * items only take the one parameter of the ppd_system
     **/
    const char * coin_file_name;
    /**
     * the name of the stock file
     **/
    const char * stock_file_name;
};

/**
 * loads all data from the given stock file and assigns information
 * to related stock pointers
 **/
BOOLEAN load_stock_data(struct ppd_system * system);

BOOLEAN add_list_node(struct ppd_list * list, struct ppd_node * node);

/**
 * saves all data related to stock with the formatted string:
 * ID|NAME|DESCRIPTION|PRICE|ON_HAND
 * to the given file
 **/
BOOLEAN save_stock_data(struct ppd_system * system, FILE*);

#endif


