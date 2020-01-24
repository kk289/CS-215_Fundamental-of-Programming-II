// File: sweeper.cpp
// Descripition: Test program for sweepergrid class
// ---------------------------------------------------------------------
// Class: CS 215                     Instructor: Dr.Deborah Hwang
// Assignment: Minesweeper Program   Date assigned: 03/02/18
// Programmer: kevil khadka          Date completed:/18

#include <iostream>
#include <sstream>
#include <cstdlib>
#include "sweepergrid.h"
#include "sweepercell.h"

using namespace std;

//template <typename T>
// Main Function

int main(int argc, char *argv[])      
{
  // Local variables
  int num_rows = stoi(argv[1]);
  int num_columns = stoi(argv[2]);
  int density = stoi(argv[3]);
  int row;
  int col;
  char ch;
  bool game_won = false;
  bool first = false;
  
  // 1. Check for correct number of arguments
  if(argc != 4)
  {
    cout << "Invalid arguments" <<  endl;
    exit(1);
  }
  
  while (1)
  {
    // write the output
    SweeperGrid1.write(cout);
    cout << endl;
    
    cout << "Enter u to uncover, m to mark, k to unmark, q to quit: ";
    cin >> ch;
    ch = tolower(ch);
    try
    {
      if(ch == 'u')
      {
	cout << "Enter a location (row col) to uncover: ";
	cin >> row >> col;
	if(!first)
	{
	  first = true;
	  SweeperGrid SweeperGrid1 (num_rows, num_columns,density,
				    row, col);
	  cout << endl;
	}
	bool move = SweeperGrid1.uncover(row, col);
	cout << endl;
	
	if(move)  // if bomb is found 
	{
	  cout << "You've uncovered a mine! Game Over!!" << endl
	       << endl;
	
	  // set flags below
	  for (int i=0; i<num_rows; i++)
	  {
	    for (int j=0; j<num_columns; j++)
	    {
	      SweeperGrid1.uncover(i, j);
	    }
	  }
	  SweeperGrid1.write(cout);
	  exit(1);
	}
      }
      else if(SweeperGrid1.game_won())
      {
	cout << "Game won!" << endl << endl;
	// set flags below
	for (int i=0; i<num_rows; i++)
	{
	  for (int j=0; j<num_columns; j++)
	  {
	    SweeperGrid1.uncover(i, j);
	  }
	}
	SweeperGrid1.write(cout);
	exit(1);
      }
      
      else if(ch == 'm')
      {
	cout << "Enter a location (row col) to mark: ";
	cin >> row >> col;
	SweeperGrid1.mark(row,col);
	game_won = SweeperGrid1.game_won();
      }
      else if(ch == 'k')
      {
	cout << "Enter a location (row col) to unmark: ";
	cin >> row >> col;
	SweeperGrid1.unmark(row,col);
	game_won = SweeperGrid1.game_won();
      }
      else if (ch == 'q')
      {
	exit(1);
      }
      else
      {
	cout << "Bad input. Try again!" << endl;
	cout << endl;
      }
      cout << endl;
    }
    
    catch(const out_of_range &error)
    {
      cout << error.what() << "Try again!" << endl;
      //  SweeperGrid1.write(cout);
      cout << endl;
    }
  }
  return 0;
} 
