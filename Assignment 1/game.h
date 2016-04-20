/***********************************************************************
* COSC1076 - Advanced Programming Techniques
* Semester 2 2015 Assignment #1 
* Full Name        : Kyle Glover
* Student Number   : s3539870
* Course Code      : COSC1076
* Program Code     : BP094
* Start up code provided by Paul Miller
***********************************************************************/
#include <stdlib.h>
#include "player.h"
#include "time.h"
#include "board.h"
#include "helpers.h"
/**
 * the various possibilities when we check for a winner
 **/
enum game_state
{
    /**
     * there was no winner (the game is still in progress
     * - set to -1 so the other values increment from 0
     **/
    G_NO_WINNER=-1,
    /**
     * the game was a draw - there are no valid moves that can be made
     **/
    G_DRAW,
    /**
     * the red token won the game
     **/
    G_RED,
    /**
     * the white token won the game
     **/
    G_WHITE
};

/**
 * Manages the game loop. See the documentation in the .c file for full
 * details. 
  **/
struct player * play_game(struct player *, struct player*);

/**
 * tests to see if the game has been won. A win is defined as four 
 * tokens in a row in any direction, however you should not wrap 
 * around the board.
 **/
enum game_state test_for_winner(
        enum cell_contents board[][BOARDWIDTH]);

