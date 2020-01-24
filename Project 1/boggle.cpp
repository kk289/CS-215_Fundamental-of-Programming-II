// File: boggle.cpp
// Descripition: It contains Header files, Function Prototypes, Main function and Function
// definitions.In this program, it makes table grid of letter to make
// words of more than 3 length letter. 
// ----------------------------------------------------------------------
// Class: CS 215                Instructor: Dr.Deborah Hwang
// Assignment: Boggle Program   Date assigned: 1/27/18
// Programmer: kevil khadka     Date completed: 2/2/18

//Header files

#include <iostream> // cin, cout, endl
#include <fstream>  // ifstream, ofstream
#include <string>   // c++ string type
#include <cstdlib>  // exit()
#include <unistd.h> // Unix standard library: system, usleep

//Identifier
const int SIZE = 7;   // 7 rows and 7 columns of data for borders
                      // one row on start and end on each side

const int MAXROW = 5; // 5 Row 
const int MAXCOL = 5; // 5 Colums 

//structure to make tile grid
struct Tile {
  char letter; 
  bool used;
};

//Function Prototypes


void createGrid(std::ifstream &infile,     // REC'D/P'BACK: input file
		Tile gird[SIZE][SIZE]);    // REC'D: 2D grid of letter

void printGrid(std::ofstream &outfile,     // REC'D/P'BACK: outfile file
	       Tile grid[SIZE][SIZE]);     // REC'D: 2D grid of letter to print

void reset_grid(Tile grid[SIZE][SIZE]);    // REC'D: 2D grid of letter


bool word_position(Tile grid[SIZE][SIZE],  // REC'D: 2D grid of letter
		std::string initial_word,  // REC'D:basic_string templates thatstores
	                                   //  and manipulates sequences of <char>
		   int &row, int &col);    // P'BACK: #rows/columns filled

void search(Tile grid[SIZE][SIZE],         // REC'D: 2D grid of letter
	    int row, int col,              // REC'D: #rows/columns
	    bool &found,                   // P'BACK: Flag for word finding 
	    std::string initial_word,      // REC'D:basic_string templates thatstores
	                                   //  and manipulates sequences of <char>
	    int word_index);               // REC'D: word position

//main program
int main(int argc, char * argv[])
{
   using namespace std;

   // 1. Check for correct number of arguments
   if (argc != 3) {
     cerr << "Usage: " << argv[0] << " infile outfile " << endl; 
     exit(1);  //quits program with return value
   }
   
   // 2. Open files
   ifstream infile(argv[1]); //explicit -value construction of input file
   if (!infile)
     {
       cerr <<  "Unable to open input file" << argv[1] << endl;
       exit(1); //quits program with return value
     }
   
   ofstream outfile(argv[2]); //explicit - value construction of output file
   if(!outfile)
     {
       cerr << "Unable to open output file" << argv[2] << endl;
       exit(1);  //quits program with return value
     }
   
   Tile grid[SIZE][SIZE];   //tile gird

   createGrid(infile, grid);  // make a tile grid

   printGrid(outfile, grid);  //print out the tile grid
 
   string a_string;   
   int row, col;
   
   while (infile >> a_string)
     {
   
       if(word_position(grid,a_string,row,col))
	 {
	   outfile << a_string << " found" << endl;  // print out found after each word 
	  }
       else
	 {
	   outfile << a_string << " not found" << endl; // print out not found after each word 
	 }
     }

   // close files
   infile.close();
   outfile.close();
   
   return 0;
}

//Function Definitions

//function to create a tile grid of 2 dimension 
void createGrid(std:: ifstream& infile,
		Tile grid[SIZE][SIZE])
{

   int row_index, col_index;    //word position in row and column
   
   std::string row;
   
   // Read each row from the file

   for (row_index = 1; row_index <= MAXROW; row_index++) {
     
     infile >> row;   //get word of row side from input file                     

     // Set left border character
     grid[row_index][0].letter = '+';

     // Copy row to tile grid
     for(col_index = 1; col_index <= MAXCOL; col_index++) {
	
	grid[row_index][col_index].letter = row[col_index-1];

	// mark letter unused in the beginning
        grid[row_index][col_index].used = false;
      }
      
      // Set right border character
      grid[row_index][MAXCOL+1].letter = '+';
   }

   // Set top and bottom border characters
   for(col_index = 0; col_index <= MAXCOL+1; col_index++)
   {
      grid[0][col_index].letter = '+';
      grid[MAXROW+1][col_index].letter = '+';
   }
}

//function to print out grid 
void printGrid(std:: ofstream &outfile,
	       Tile grid[SIZE][SIZE])
{
   using namespace std;
   
   int row_index, col_index;
   
   cout << "Grid" << endl;

   // For each row
   for (row_index = 1; row_index <= MAXROW; row_index++)
     {
      // Print each character in a row and column
      for (col_index = 1; col_index <= MAXCOL; col_index++)
	{
	  if(col_index != 1){
	    cout << " ";
	  }
	  cout << " " << grid[row_index][col_index].letter;
	}
      cout << endl;
     }
}

// function to reset the flag value
void reset_grid(Tile grid[SIZE][SIZE])
{
  for(int i = 1; i <= MAXROW; i++)
    {
      for(int j = 1; j <= MAXCOL; j++)
	{
	  grid[i][j].used = false;	
	}
    }
}

//function to look the word position and passes back to main function 
bool word_position(Tile grid[SIZE][SIZE], std::string initial_word,
	     int &row, int &col)
{
  bool found;
  
  for(int i= 1; i <= MAXROW; i++)
    {
    for(int j = 1; j <= MAXCOL; j++)
      {
	reset_grid(grid);

	search(grid,i,j,found,initial_word, 0);

	if(found)
	  return true;
      }
    }
  return false;
}

//function to search word if they are already used:if yes, return ture or vice versa
void search(Tile grid[SIZE][SIZE],
	    int row, int col, bool &found,
	    std::string initial_word, int word_index){

  using namespace std;

  //  - word is found
  if(word_index == initial_word.length()){

    grid[row][col].used = true;
    found = true;

    return;
  }
  
  // words is not found
  // path is blocked if border character is a '+'(Wall) 

  if(grid[row][col].letter == '+' || grid[row][col].used == true ||
     grid[row][col].letter != initial_word[word_index]){
    
    found = false;

    return;
  }
  
  //recursive steps
  // mark the grid as used and go to a neighbor
   grid[row][col].used = true;

   //Try to search right neighbor
   search(grid, row, col+1, found, initial_word, word_index+1);

   if (!found)  // right neighbor is not on the path
     // Try the lower right  neighbor
     search(grid, row+1, col+1, found, initial_word, word_index+1);
    
     if (!found)  // lower right neighbor is not on the path
       // Try the lower neighbor
       search(grid, row+1, col, found, initial_word, word_index+1);
    
     if (!found)  // lower neighbor is not on the path
       // Try the lower left  neighbor,
       search(grid, row+1, col-1, found, initial_word, word_index+1);

     if (!found)  // lower left neighbor is not on the path
       // Try the left neighbor
       search(grid, row, col-1, found, initial_word, word_index+1);

     if (!found)  // left neighbor is not on the path
       // Try the upper left neighbor
       search(grid, row-1,col-1,found, initial_word, word_index+1);

     if (!found)  // Upper left neighbor is not on the path
       // Try the upper neighbor
       search(grid, row-1, col, found, initial_word, word_index+1);

     if (!found)  // upper neighbor is not on the path
       // Try the upper right neighbor
       search(grid, row-1, col+1,found, initial_word, word_index+1);
   
        // if none of the option works out, BACKTRACK and return false
     if (!found)
       {
	 
       grid[row][col].used = false;
       found = false;
       return;

       }
}
