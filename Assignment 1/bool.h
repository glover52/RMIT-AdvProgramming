/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#ifndef BOOL_H
#define BOOL_H
/**
 * @file bool.h defines the BOOLEAN type which contains @ref FALSE as 0 and 
 * @ref TRUE as 1
 **/

/**
 * enumeration to represent the boolean type as this is not defined in ansi
 * C.
 **/
typedef enum falsetrue
{
    /**
     * false value - set to 0
     **/
    FALSE=0,
    /**
     * true value - defined in the standard as non-zero. In this case we define
     * it as 1
     **/
    TRUE
} BOOLEAN;
#endif
