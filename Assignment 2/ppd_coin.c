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
#include "ppd_coin.h"

 /**
  * @file ppd_coin.c implement functions here for managing coins in the
  * "cash register" contained in the @ref ppd_system struct.
  **/

int int_to_id(int cents)
{
	if(cents == FIVE_CENTS_VALUE)
		return FIVE_CENTS;
	
	if(cents == TEN_CENTS_VALUE)
		return TEN_CENTS;
	
	if(cents == TWENTY_CENTS_VALUE)
		return TWENTY_CENTS;
	
	if(cents == FIFTY_CENTS_VALUE)
		return FIFTY_CENTS;
	
	if(cents == ONE_DOLLAR_VALUE)
		return ONE_DOLLAR;
	
	if(cents == TWO_DOLLARS_VALUE)
		return TWO_DOLLARS;
	
	if(cents == FIVE_DOLLARS_VALUE)
		return FIVE_DOLLARS;
	
	if(cents == TEN_DOLLARS_VALUE)
		return TEN_DOLLARS;
	
	/* Function failed */
	return -1;
}

int id_to_int(int id)
{
	if(id == FIVE_CENTS)
		return FIVE_CENTS_VALUE;
	
	if(id == TEN_CENTS)
		return TEN_CENTS_VALUE;
	
	if(id == TWENTY_CENTS)
		return TWENTY_CENTS_VALUE;
	
	if(id == FIFTY_CENTS)
		return FIFTY_CENTS_VALUE;
	
	if(id == ONE_DOLLAR)
		return ONE_DOLLAR_VALUE;
	
	if(id == TWO_DOLLARS)
		return TWO_DOLLARS_VALUE;
	
	if(id == FIVE_DOLLARS)
		return FIVE_DOLLARS_VALUE;
	
	if(id == TEN_DOLLARS)
		return TEN_DOLLARS_VALUE;
	
	/* Function failed */
	return -1;
}