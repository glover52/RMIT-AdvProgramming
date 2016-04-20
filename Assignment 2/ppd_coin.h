/***********************************************************************
 * COSC1076 - Advanced Programming Techniques
 * Semester 2 2015 Assignment #2
 * Full Name        : EDIT HERE
 * Student Number   : EDIT HERE
 * Course Code      : EDIT HERE
 * Program Code     : EDIT HERE
 * Start up code provided by Paul Miller
 * Some codes are adopted here with permission by an anonymous author
 ***********************************************************************/

/**
 * @file ppd_coin.h defines the coin structure for managing currency in the
 * system. You should declare function prototypes for managing coins here
 * and implement them in ppd_coin.c
 **/
#include "bool.h"

#ifndef PPD_COIN
#define PPD_COIN
#define COIN_DELIM ","
#define MAX_COIN_LEN 8

#define COIN_DENOM_ID 0
#define COIN_COUNT_ID 1

#define MAX_CENT_VALUE 99
struct ppd_system;

/**
 * enumeration representing the various types of currency available in
 * the system. 
 **/
enum denomination
{
    FIVE_CENTS, 
	TEN_CENTS, 
	TWENTY_CENTS, 
	FIFTY_CENTS, 
	ONE_DOLLAR, 
    TWO_DOLLARS, 
	FIVE_DOLLARS, 
	TEN_DOLLARS
};

enum denomination_value
{
    FIVE_CENTS_VALUE=5, 
	TEN_CENTS_VALUE=10, 
	TWENTY_CENTS_VALUE=20, 
	FIFTY_CENTS_VALUE=50, 
	ONE_DOLLAR_VALUE=100, 
    TWO_DOLLARS_VALUE=200, 
	FIVE_DOLLARS_VALUE=500, 
	TEN_DOLLARS_VALUE=1000
};

/**
 * represents a coin type stored in the cash register. Each demonination
 * will have exactly one of these in the cash register.
 **/
struct coin
{
    /**
     * the denomination type
     **/
    enum denomination denom;
    /**
     * the count of how many of these are in the cash register
     **/
    unsigned count;
};

int int_to_id(int cents);

int id_to_int(int id);
#endif
