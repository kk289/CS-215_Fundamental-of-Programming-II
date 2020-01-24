// File: sweepercell.cpp
// Implementation of minesweeper cells
// -----------------------------------------------------------
// Assignment: Project 4
// Date Assigned: October 11, 2016
// Name: Kevil khadka

#include <iostream>
#include "sweepercell.h"
using namespace std;

// Constructor
// Cell always starts out empty, covered, unmarked, and with 0
// adjacent bombs
SweeperCell::SweeperCell ()
{
   bomb = false;
   covered = true;
   marked = false;
   rep = '#';          // covered and unmarked
   num_adjacent = 0;
}  // end default constructor

// Accessors
bool SweeperCell::has_bomb () const
{
   return bomb;
}  // end has_bomb

bool SweeperCell::is_covered () const
{
   return covered;
}  // end is_covered

bool SweeperCell::is_marked () const
{
   return marked;
}  // end is_marked

int SweeperCell::get_num_adjacent() const
{
   return num_adjacent;
}  // end get_num_adjacent

// Mutators
void SweeperCell::incr_num_adjacent()
{
   num_adjacent++;
   if (!bomb && !covered) // no bomb and not covered, so show num_adjacent
      rep = '0' + num_adjacent;
}  // end incr_num_adjacent

void SweeperCell::decr_num_adjacent()
{
   num_adjacent--;
   if (!bomb && !covered)  // no bomb and not covered, so show num_adjacent
      rep = '0' + num_adjacent;
}  // end decr_num_adjacent

void SweeperCell::place_bomb ()
{
   bomb = true;
   if (!covered)  // not covered, so show bomb
      rep = '*';
}  // end place_bomb

void SweeperCell::remove_bomb ()
{
   bomb = false;
   if (!covered)  // not covered, so show num_adjacent
      rep = '0' + num_adjacent;
}  // end remove_bomb

bool SweeperCell::uncover ()
{
   covered = false;
   if (bomb)  // has a bomb, so show it
      rep = '*';
   else       // no bomb, so show num_adjacent
      rep = '0' + num_adjacent;
   return (bomb);
}  // end uncover

void SweeperCell::mark ()
{
   marked = true;
   if (covered)  // covered, so show the mark
      rep = 'f';
}  // end mark

void SweeperCell::unmark ()
{
   marked = false;
   if (covered)  // covered, so remove the mark
      rep = '#';
}  // end Unmark

// Function: operator<<
// Outputs the character representation of the cell:
//   # - when covered and unmarked
//   f - when covered and marked
//   * - when uncovered containing a bomb
//   n - when uncovered and no bomb, where n is 
//       number of adjacent cells (all 8 directions) 
//       containing bombs
ostream& operator<< (ostream & out, const SweeperCell & a_cell)
{
   out << a_cell.rep;
   return out;
}  // end operator<<
