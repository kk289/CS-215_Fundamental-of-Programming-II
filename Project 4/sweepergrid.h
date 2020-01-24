// File: sweepergrid.h
// Document
// Header file for sweepergrid.cpp
// ----------------------------------------------------------------------
// Class: CS 215                      Instructor: Dr.Deborah Hwang
// Assignment: MinesweeperProgram     Date assigned: 3/02/18 
// Programmer: kevil khadka           Date completed:/18

#ifndef SWEEPERGRID_H_   // if not define
#define SWEEPERGRID_H_
#include <stdexcept>
#include <iostream> //istream, ostream
#include "sweepercell.h"

//template <typename T>
class SweeperGrid
{
 public:
  // Constructor
  SweeperGrid();
  SweeperGrid(int initial_rows,int initial_cols,int density,
	      int user_row,int user_col);
  SweeperGrid(const SweeperGrid& original);
  
  // Deconstructor
  ~SweeperGrid();

  // Overloaded Assignment Operator Function
  SweeperGrid& operator= (const SweeperGrid& original);
  //  SweeperCell& at(int row, int col) const;

  // Accessors
  int rows() const;
  int columns() const;
  int bombs() const;
  bool game_won() const;
  
  // Mutators
  void place_bomb(int row, int col);
  void remove_bomb(int row, int col);
  bool uncover(int row, int col);
  void mark(int row, int col);
  void unmark(int row, int col);
  void write(std::ostream &out) const;
  
 private:
  // attributes declerations - any helper functions
  int num_rows;
  int num_columns;
  int num_bombs;
  SweeperCell** grid;
  
  void num_adjacent(int row, int col); // number of adjacent cells (all 8 directions)
                          // containing bombs
};
#endif
