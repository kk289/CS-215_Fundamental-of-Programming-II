# This is a comment starting with #
# Makefile for card class and test program

# target: dependencies
# <TAB> command

# Link together object files into the executable 
carddriver: carddriver.o card.o
	clang++ carddriver.o card.o -o carddriver

# compile the .cpp file into .o files using -c option
carddriver.o: carddriver.cpp card.h
	clang++ -Wall -std=c++11 -c carddriver.cpp

card.o: card.cpp card.h
	clang++ -Wall -std=c++11 -c card.cpp

submit.tar: Makefile card.h card.cpp carddriver.cpp
	tar -cvf submit.tar Makefile card.h card.cpp carddriver.cpp

# Dummy targets- the targets are not actually created
# *~ are the emacs backup files
clean: 
	rm -f carddriver *.o *~ *.tar

