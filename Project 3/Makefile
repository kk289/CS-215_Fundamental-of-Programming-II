# This is a comment starting with #
# Makefile for document class and test program

# target: dependencies
# <TAB> command

# Link together object files into the executable 
editor: editor.o document.o
	clang++ editor.o document.o -o editor

# compile the .cpp file into .o files using -c option
editor.o: editor.cpp document.h
	clang++ -Wall -std=c++11 -c editor.cpp

document.o: document.cpp document.h
	clang++ -Wall -std=c++11 -c document.cpp

submit.tar: Makefile document.h document.cpp editor.cpp
	tar -cvf submit.tar Makefile document.h document.cpp editor.cpp

# Dummy targets- the targets are not actually created
# *~ are the emacs backup files
clean: 
	rm -f editor *.o *~ *.tar

