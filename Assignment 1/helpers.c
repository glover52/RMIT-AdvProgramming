/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include "helpers.h"

/**
 * @file helpers.c contains various functions that help in the
 * implementation of the program. You should put functions you create
 * here unless they logically belong to another module (such as
 * player, board or game
 **/

void read_rest_of_line(void)
{
    int ch;
    while(ch = getc(stdin), ch!=EOF && ch != '\n')
        ; /* gobble each character */
    /* reset the error status of the stream */
    clearerr(stdin);
}


