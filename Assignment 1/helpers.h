/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bool.h"

/**
 * @file helpers.h contains the datastructures used for various helper 
 * functioons and their function prototypes
 **/
#ifndef HELPERS_H
#define HELPERS_H
/**
 * the possible values that can be returned from custom input handling 
 * functions
 **/
enum input_result
{
    /**
     * the input was valid
     **/
    SUCCESS,
    /**
     * the input was not valld
     **/
    FAILURE,
    /**
     * the user requested to return to the menu either by pressing enter on
     * an empty line or pressing ctrl-d on an empty line
     **/
    RTM=-1
};

/**
 * call this function whenever you detect buffer overflow but only call this
 * function when this has happened.
 **/
void read_rest_of_line(void);

#endif
