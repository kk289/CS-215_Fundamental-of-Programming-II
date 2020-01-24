// File: sweepergrid.cpp
// ---------------------------------------------------------------------
// Class: CS 215                     Instructor: Dr.Deborah Hwang
// Assignment: Minesweeper Program   Date assigned: 03/02/18
// Programmer: kevil khadka          Date completed:/18

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <list>
#include <iomanip>   // std::setw
#include <stdexcept>
#include "sweepergrid.h"
#include "sweepercell.h"

using namespace std;

// Default Constructor
SweeperGrid::SweeperGrid()
{
  num_rows = 5;
  num_columns = 5;
  int density = 25;
  num_bombs = 0;
  int rand_num;
  
  grid = new SweeperCell*[num_rows];
  for(int i=0; i < num_rows; i++)
  {
    grid[i] = new SweeperCell[num_columns];
  }
  srand(time(0)); // to receive longer interger

  // cout << "debug";
  for(int i = 0; i < num_rows; i++)
  {
    for(int j = 0; j < num_columns; j++)
    {
      rand_num = rand() % 100 +1;
      if (rand_num < density && !grid[i][j].has_bomb() && num_bombs < num_rows * num_columns * density / 100)
      {
	place_bomb(i, j);
	grid[i][j].place_bomb();
      }
    }
  }

  cout << endl;
  cout << "There are " << this->bombs() << " bombs in the grid."
       << endl;
}

// Explicit Constructor
SweeperGrid::SweeperGrid(int initial_rows,int initial_cols,int density,
			 int user_row, int user_col)
{
  if(initial_rows < 5 || initial_cols < 5)
  {
    cout << "Rows or Columns should be greater than 5" << endl;
    exit(1);
  }
  else if(density < 25 || density > 75)
  {
    cout << "Density should be bewteen 25 and 75" << endl;
    exit(1);
  }
  else
  {
    num_rows = initial_rows;
    num_columns = initial_cols;
    num_bombs = 0;
    int rand_num = 0;

    grid = new SweeperCell*[num_rows];
    for(int i=0; i < num_rows; i++)
    {
      grid[i] = new SweeperCell[num_columns];
    }
    srand(time(0)); // to receive /longer interger
   
    //    cout << "debug" << endl;
    for(int i = 0; i < num_rows; i++)
    {
      for(int j = 0; j < num_columns; j++)
      {
	rand_num = rand() % 100 +1;
	if (rand_num < density && !grid[i][j].has_bomb() && num_bombs < num_rows * num_columns * density / 100 && (i != user_row && j != user_col))
	{
	  place_bomb(i, j);
	  grid[i][j].place_bomb();
	}
      }
    }
    cout << endl;
    cout << "There are " << this->bombs() << " bombs in the grid."
	 << endl;
  }
}

// copy constructor : new SweeperGrid same to previous one
SweeperGrid::SweeperGrid(const SweeperGrid& original)
{
  num_rows = original.num_rows;
  num_columns = original.num_columns;
  num_bombs = original.num_bombs;

  // Dyanmic allocation
  grid = new SweeperCell*[num_rows];
  for(int i=0; i < num_rows; i++)
  {
    grid[i] = new SweeperCell[num_columns];
  }
  
  // copy content 1 by 1
  for(int i = 0; i < num_rows; i++)
  {
    for(int j = 0; j < num_columns; j++)
    {
      grid[i][j] = original.grid[i][j];
    }
  }
}

// Destructor- delete the grid
SweeperGrid::~SweeperGrid()
{
  // dellocation of grid
  for(int i = 0; i < num_rows; i++)
  {
    delete [] grid[i];
    grid[i] = 0;
  }
  delete [] grid;
  grid = 0;
}

// operator= : overloaded assignment operator function
// identical to the source SweeperGrid Object
// 
// Return = *this

SweeperGrid& SweeperGrid::operator= (const SweeperGrid& original)
{
  // make a copy of original
  SweeperGrid copy(original);

  //swap the contents of this and the copy
  std::swap(num_rows, copy.num_rows);
  std::swap(num_columns, copy.num_columns);
  std::swap(num_bombs, copy.num_bombs);
  std::swap(grid, copy.grid);

  return *this;
}
/*
// at : receives row and columns and return
//    : a reference to a cell within the  grid
SweeperCell& SweeperGrid::at(int row, int col) const
{
  return grid[row][num_columns + col];
}
*/
// row: returns the number of rows in the grid
int SweeperGrid::rows() const
{
  return num_rows;
}

// columns: retruns the number of columns in the grid
int SweeperGrid::columns() const
{
  return num_columns;
}

// bombs : returns the number of bombs in the grid
int SweeperGrid::bombs() const
{  return num_bombs;
}

// game won : return true if game won otherwise false
bool SweeperGrid::game_won() const
{
  int keep_track = 0;

  for(int i = 0; i < num_rows; i++)
  {
    for(int j = 0; j < num_columns; j++)
    {
      if(grid[i][j].is_covered() == true)
      {
	keep_track++;
      }
    }
  }
  if(keep_track == num_bombs)
    return true;
  else
    return false;
}

 /*
        Count all the bombs in the 8 adjacent
        cells
 
            N.W   N   N.E
              \   |   /
               \  |  /
            W----Cell----E
                 / | \
               /   |  \
            S.W    S   S.E
 
        Cell-->Current Cell (row, col)
        N -->  North        (row-1, col)
        S -->  South        (row+1, col)
        E -->  East         (row, col+1)
        W -->  West            (row, col-1)
        N.E--> North-East   (row-1, col+1)
        N.W--> North-West   (row-1, col-1)
        S.E--> South-East   (row+1, col+1)
        S.W--> South-West   (row+1, col-1)
    */

// place bomb : place a bomb in the grid cell at location(row,col)
void SweeperGrid::place_bomb(int row, int col)
{
  // if grid[row][col] exists
  if((row >= 0 && row < num_rows) &&
     (col >= 0 && col < num_columns))
  {
    // if there is no bomb in the cell yet
    if(!grid[row][col].has_bomb())
    {
      grid[row][col].place_bomb();
      num_bombs++;

      //upper left
      if(row - 1 >= 0 && col - 1 >= 0)
      {
	//cout << "test1:" << grid[row-1][col-1];
	grid[row - 1][col - 1].incr_num_adjacent();
	//	cout << "test2:" << grid[row-1][col-1];
      }

      // up
      if(row - 1 >= 0 && col >= 0)
      {
	//cout << "OK1" << endl;
	grid[row - 1][col].incr_num_adjacent();
      }

	// upper right
      if(row - 1 >= 0 && col + 1 < num_columns)
      {
	//cout << "OK2" << endl;
	grid[row - 1][col + 1].incr_num_adjacent();
      }

      // left
      if(col - 1 >= 0)
	{
	  //cout << "OK3" << endl;
	grid[row][col - 1].incr_num_adjacent();
      }

	// right
      if(col + 1 < num_columns)
      {
	//cout << "OK4" << endl;
	grid[row][col + 1].incr_num_adjacent();
      }

	// bottom left
      if(row + 1 < num_rows && col - 1 >= 0)
      {
	//cout << "OK5" << endl;
	grid[row + 1][col - 1].incr_num_adjacent();
      }

	// bottom
      if(row + 1 < num_rows)
      {
	//cout << "OK6" << endl;
	grid[row + 1][col].incr_num_adjacent();
      }

	// bottom right
      if(row + 1 < num_rows && col + 1 < num_columns)
      {
	//cout << "OK7" << endl;
	grid[row + 1][col + 1].incr_num_adjacent();
      }
    }
  }
  else
  {
    cout << "bad" << endl;
    throw std::out_of_range("Location is Out of range.");
  }
}

  /*
            Recur for all 8 adjacent cells
 
                N.W   N   N.E
                  \   |   /
                      \  |  /
                W----Cell----E
                     / | \
                   /   |  \
                S.W    S   S.E
 
            Cell-->Current Cell (row, col)
            N -->  North        (row-1, col)
            S -->  South        (row+1, col)
            E -->  East         (row, col+1)
            W -->  West            (row, col-1)
            N.E--> North-East   (row-1, col+1)
            N.W--> North-West   (row-1, col-1)
            S.E--> South-East   (row+1, col+1)
            S.W--> South-West   (row+1, col-1)
   */
 
// remove_bomb: remove a bomb in the grid cell at location(row,col)
void SweeperGrid::remove_bomb(int row, int col)
{
  if((row >= 0 && row < num_rows) &&
     (col >= 0 && col < num_columns))
  {
    if(grid[row][col].has_bomb() == true)
    {
      grid[row][col].remove_bomb();
      num_bombs--;

      // upper left
      if(row - 1 >= 0 && col - 1 >= 0)
	grid[row - 1][col - 1].decr_num_adjacent();

      // up
      if(row - 1 >= 0)
	grid[row - 1][col].decr_num_adjacent();

      // upper right
      if(row - 1 >= 0 && col + 1 < num_columns)
	grid[row - 1][col + 1].decr_num_adjacent();

      // left
      if(col - 1 >= 0)
	grid[row][col - 1].decr_num_adjacent();

      // right
      if(col + 1 < num_columns)
	grid[row][col + 1].decr_num_adjacent();

      // bottom left
      if(row + 1 < num_rows && col - 1 >= 0)
	grid[row + 1][col - 1].decr_num_adjacent();

      // bottom
      if(row + 1 < num_rows)
	grid[row + 1][col].decr_num_adjacent();

      // bottom right
      if(row + 1 < num_rows && col + 1 < num_columns)
        grid[row + 1][col + 1].decr_num_adjacent();
    }
  }
  else
  {
    throw std::out_of_range("Location is Out of range.\n");
  }
}

// uncover: uncovers the grid cell at location(row,col)
//        : returns true if a bomb is uncovered else false otherwise
bool SweeperGrid::uncover(int row, int col)
{
  if((row < 0 || row >= num_rows) ||
     (col < 0 || col >= num_columns))
  {
    throw std::out_of_range("Location is Out of range.");
  }
  else
  {
    return grid[row][col].uncover();
  } 
}

// mark - mark the grid cell at location (row, col)
void SweeperGrid::mark(int row, int col)
{
  if((row < 0 || row >= num_rows) ||
     (col < 0 || col >= num_columns))
  {
    throw std::out_of_range("Location is Out of range.");
  }
  else
  {
    return grid[row][col].mark();
  } 
} 

// unmark- unmarks the grid cell at location(row, col)
void SweeperGrid::unmark(int row, int col)
{
  if((row < 0 || row >= num_rows) ||
     (col < 0 || col >= num_columns))
  {
    throw std::out_of_range("Location is Out of range.");
  }
  else
  {
    return grid[row][col].unmark();
  } 
} 

// write - outputs the SweeperGrid in a 2D grid to an output strea,
void SweeperGrid::write(std::ostream &out) const
{
  for(int i = 0; i < num_rows; i++)
  {
    for(int j = 0; j < num_columns; j++)
    {
      out << setw(3) << grid[i][j];
    }
    out << endl;
  }
}

