########################################################################
# COSC1076 - Advanced Programming Techniques
# Semester 2 2014 Assignment #2
# Full Name        : Kyle Glover
# Student Number   : s3539870
# Course Code      : EDIT HERE
# Program Code     : EDIT HERE
# Start up code provided by Paul Miller
########################################################################

SOURCES=ppd_main.c ppd_menu.c ppd_options.c ppd_utility.c ppd_stock.c \
ppd_coin.c
HEADERS=ppd_main.h ppd_menu.h ppd_options.h ppd_utility.h ppd_stock.h \
ppd_coin.h bool.h
README=ppd_readme
MAKEFILE=Makefile

########################################################################
# Move this target to the end of the Makefile to zip up your code 
# when submitting. Do not submit your .dat files, or directories. 
# We only want the files that are part of your implementation.
########################################################################
compile:
	gcc -g -ansi -Wall -pedantic $(SOURCES) $(HEADERS) -o ppd
	
clean:
	rm -f -v *.o ppd

archive:
	zip $(USER)-a2 $(SOURCES) $(HEADERS) $(README) $(MAKEFILE)
