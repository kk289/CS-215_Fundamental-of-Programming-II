// File: sweepercell.h
// Minesweeper game cells, can contain a bomb or not,
// can be covered or not, can be marked or not
// -----------------------------------------------------------
// Assignment: Project 4
// Date Assigned: October 11, 2016

#ifndef CELL_H_
#define CELL_H_

#include <iostream>

class SweeperCell
{
   public:
      // Constructor: cell always starts out empty, covered, unmarked,
      // and with 0 adjacent bombs
      SweeperCell ();

      // Accessors
      bool has_bomb () const;       // returns true if cell contains a bomb
      bool is_covered () const;     // returns true if cell is covered
      bool is_marked () const;      // returns true if cell is marked
      int get_num_adjacent() const; // returns number of adjacent bombs

      // Mutators
      void incr_num_adjacent();     // increment number of adjacent bombs by 1
      void decr_num_adjacent();     // decrement number of adjacent bombs by 1
      void place_bomb();            // places a bomb in the cell
      void remove_bomb();           // removes a bomb from the cell
      bool uncover ();              // uncovers cell; returns true if cell
                                    // contains a bomb, false otherwise
      void mark ();                 // marks cell
      void unmark ();               // unmarks cell
	 
      // Friends
      // output the character rep of the cell, see below
      // returns the output stream
      friend std::ostream& operator<<
	 (std::ostream & out,        // rec'd & pb: output stream
	  const SweeperCell & a_cell); // rec'd: cell to output
	 
   private:
      bool bomb,          // true if contains a bomb
	   covered,       // true if covered
	   marked;        // true if marked
      char rep;           // character representation of cell state
                          //   # - when covered and unmarked
                          //   f - when covered and marked
                          //   * - when uncovered containing a bomb
                          //   n - when uncovered and no bomb, where n is 
                          //       number of adjacent cells (all 8 directions) 
                          //       containing bombs
      int num_adjacent;   // number of adjacent cells (all 8 directions)
                          // containing bombs

}; // end class SweeperCell

#endif // CELL_H_
