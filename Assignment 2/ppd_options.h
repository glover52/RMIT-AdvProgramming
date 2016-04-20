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

#include "ppd_utility.h"

/**
 * @file ppd_options.h declares all functions to implement the menu
 * options that can be called from the main menu. 
 **/
 
/**
 * This option allows the user to request a display of the items available
 * for purchase. This is the data loaded into the linked list in the 
 * requirement 2. This requirement should behave as follows - from the 
 * main menu, the user selects 1 and data should be displayed in the 
 * following format: 

 * Items Menu
 * ----------
 * ID    |Name                |Available |Price 
 * ---------------------------------------------
 * I0001 |Meat Pie            |12        |$ 3.50
 * I0002 |Apple Pie           |0         |$ 3.50
 * I0003 |Lemon Cheesecake    |439       |$ 4.00
 * I0004 |Lemon Meringue Pie  |3         |$ 3.00
 * I0005 |Lemon Tart          |5         |$ 3.75
 **/
BOOLEAN display_items(struct ppd_system *);

/** This option allows the user to purchase an item from the menu.
 * This function is called from the main menu when the user has
 * finally decided to purchase an item. This function allows the user
 * to pay for their item by collecting money from them, and adjusting
 * balances within the system as appropriate. Change is then given
 * back to the customer, if appropriate. The number of items on hand
 * should also be deducted. You should not allow an item to be
 * purchased if there are 0 or less of that item on hand.
 *
 * Purchase Item 
 * ------------- 
 * Please enter the id of the item you wish to purchase: I0001 
 * You have selected “Meat Pie - Yummy Beef in Gravy surrounded by pastry” 
 * This will cost you $3.50.  
 * Please hand * over the money – type in the value of each note/coin 
 * in cents.
 * Press enter or ctrl-d on a new line to cancel this purchase: You
 * still need to give us $3.50: 200 You still need to give us $1.50:
 * 300 Error: $3.00 is not a valid denomination of money.  You still
 * need to give us $1.50: 500 Thank you. Here is your Meat Pie, and
 * your change of $3.50: $2 $1 50c Please come again soon.
 *
 * After which the user would be returned to the main menu. 
 *
 * When refunding money, you must display each note or coin separately
 * used in the refund and you must ensure that prior to the sale that
 * there is sufficient denominations in the system so that the
 * customer is given the correct change. You must also subtract these
 * coins from the coins array if a sale can take place. Note that
 * coins entered to pay for an item can form part of the change that
 * is given to the customer if that is required to give the customer
 * the smallest amount of change possible. If pdd cannot give correct
 * change then the sale should not occur, and your program should
 * display an appropriate message explaining why. 
 *
 * If the user presses enter or ctrl-d on a new line, refund all the
 * coins/notes they have entered so far and return them to the main
 * menu.
 **/ 

BOOLEAN purchase_item(struct ppd_system *);

/** 
 * You must save all data to the data files that were provided on the
 * command line when the program loaded up. When the saving is
 * completed, you must have the program exit. The specifications 
 * mentioned for each file must be maintained and the program must be
 * able to load up your files as easily as it loaded up the files that
 * we have provided you with. Also, at this point, once you have
 * implemented dynamic memory allocation, you must free all memory
 * allocated and exit the program. A program which does everything but
 * exit the program will still lose marks, as much as a program that
 * does not implement any other requirement.  
 **/ 

BOOLEAN save_system(struct ppd_system *);

/**
 * This option adds an item to the system. When the user selects this
 * option, the system should generate the next available item id and
 * associate that with this item. The user should then be prompted for
 * the Name and Description and Price (a valid amount of money in
 * dollars and cents). The item should then be allocated the default
 * "on hand" value specified in the startup code. The new item id
 * shall have an ‘I’ prepended to it and will be 5  characters long.
 * 
 * For example:
 * 
 * This new meal item will have the Item id of I0006.
 * Enter the item name: Baklava
 * Enter the item description: rich, sweet pastry made of layers of
 * filo filled with chopped nuts and sweetened and held together with
 * syrup or honey.
 * Enter the price for this item: 8.00
 * This item “Baklava – rich, sweet pastry made of layers of filo
 * filled with chopped nuts and sweetened and held together with syrup
 * or honey.” has now been added to the menu.
 *
 **/

BOOLEAN add_item(struct ppd_system *);

/**
 * Remove an item from a category and delete it from the system,
 * including free memory that is no longer being used. 
 * Example:
 * Enter the item id of the item to remove from the menu: I0001
 * “I0001 – Meat Pie - Yummy Beef in Gravy surrounded by pastry” has
 * been removed from the system.
 **/
BOOLEAN remove_item(struct ppd_system *);

/**
 * This option will require you to iterate over every stock in the
 * list and set its 'on hand' count to the default value specified in
 * the startup code. 
 *
 * You should display a message once this is done such as “All stock
 * has been reset to the default level of X” where X is the default
 * stock level specified in the startup code.
 **/
BOOLEAN reset_stock(struct ppd_system *);

/**
 * This option will require you to iterate over every coin in the coin
 * list and set its 'count' to the default value specified in the
 * startup code. 
 *
 * You should display a message once this is done such as “All coins
 * have been reset to the default level of X” where X is the default
 * amount of coins specified in the startup code.
 **/
BOOLEAN reset_coins(struct ppd_system *);

/**
 * This option will require you to display the coins as follows. In
 * particular, the counts of coins should be correctly aligned, and
 * they should be sorted from lowest to highest value: 
 *
 *        Coins Summary
 *        ---------------------
 *        Denomination    | Count
 *        ---------------------
 *        5 cents         |    20
 *        10 cents        |    40
 *        20 cents        |    3
 *        50 cents        |    5
 *        1 dollar        |    30
 *        2 dollar        |    20
 *        5 dollar        |    4
 *        10 dollar       |    3
 **/
BOOLEAN display_coins(struct ppd_system *);

BOOLEAN abort_program(struct ppd_system * system);


