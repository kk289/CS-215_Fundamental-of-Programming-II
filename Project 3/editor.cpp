// File: editor.cpp
// Descripition: Test program for document class
// ----------------------------------------------------------------------
// Class     : CS 215               Instructor    : Dr.Deborah Hwang
// Assignment: Line Editor Program  Date assigned : 2/12/18
// Programmer: kevil khadka         Date completed: 3/02/18

//Header files
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <stdexcept>
#include "document.h"

using namespace std;

// Function prototype
void show_commands();  // displays all command lines 

/*
 * Main Function
 */
int main(int argc, char *argv[])      
{
  // Local variables
  Document editorFile;  // Document name
  string filename;      // file name holder
  string line;          // user input holder
  string target;        // used for find operators
  char command_line;    // holds command line
  int n;                // holds number
  
  // 1. Check for correct number of arguments
  if(argc != 2)
  {
    cerr << "Usage: " << argv[0] << " Inputfile Outfile " <<  endl;
    exit(1);
  }

  // open files
  ifstream infile(argv[1]);  // explicit- value construction of input file
  if(!infile)
  {
    cerr << "Unable to open input file" << argv[1] << endl;
    exit(1); // quits program with return value
  }

  // load the input file
  editorFile.load(infile);

  // keep asking user
  while(1)
  {
    cout << "> ";
    cin >> command_line; // ask to enter command line from commmand menu
    command_line = toupper(command_line);  // change to upper case letter
    cin.ignore();   // skip a line

    if(command_line == 'I') // insert line in front of current line
    {
      getline(cin, line);
      editorFile.insert(line);   // call insert operator
    }
    else if(command_line == 'A') // append line to end of document
    {
      getline(cin, line);
      editorFile.append(line);  // call append operator
    }
    else if(command_line == 'R') // replace current line
    {
      try  // put code that can throw into a try -block
      {
	getline(cin, line); 
	editorFile.replace(line);  // call replace operator
      }
      catch (const invalid_argument & ex) // this is the hander for
	                                   // invalid_argument exceptions
      {
	cout << ex.what() << endl;
	cout << "Too Bad!" << endl;
      }
    }
    else if(command_line == 'D') // delete the current line
    {
      try  // put code that can throw into a try -block
      {
	editorFile.erase();  // call erase operator
      }
      catch (const invalid_argument & ex) // this is the hander for
	                                   // invalid_argument exceptions
      {
	cout << ex.what() << endl;
	cout << "Too Bad!" << endl;
      }
    }
    else if(command_line == 'F') // makes line containing target current line
    {
      getline(cin, target);
      editorFile.find(target);   // call find operator
    }
    else if(command_line == 'S') // set current line to nth line
    {
      try  // put code that can throw into a try -block
      {
	cin >> n;
	editorFile.set_current(n); // call set_current operator
      }
      catch (const invalid_argument & ex) // this is the hander for
	                                   // invalid_argument exceptions
      {
	cout << ex.what() << endl;
	cout << "Too Bad!" << endl;
      }
    }
    else if(command_line == 'M') // move current line n places
    {
      try  // put code that can throw into a try -block
      {
	cin >> n;
	editorFile.move_current(n);  // call move_current operator
      }
      catch (const invalid_argument & ex) // this is the hander for
	                                   // invalid_argument exceptions
      {
	cout << ex.what() << endl;
	cout << "Too Bad!" << endl;
      }
    }
    else if(command_line == 'C')  // display current line to screen
    {
      editorFile.write_line(cout);  // call write_line operator
    }
    else if(command_line == 'P') // display entire document to screen
    {
      editorFile.write_all(cout); // call write_all operator
    }
    else if(command_line == 'W') // write document to file
    {
      cin >> filename;  // ask user to enter file name
      ofstream outfile(filename);  // open outfile 
      editorFile.write_all(outfile); // call write_all operator
      outfile.close();
    }
    else if(command_line == 'L') // load file into this editor
    {
      cin >> filename;
      ifstream infile(filename);   // new input file for load operator
      if(!infile)
	cout << "Error!" << endl;
      else
	editorFile.load(infile); // call load operator
    }
    else if(command_line == 'H') //  display this list of commands 
    {
      show_commands();  // call show commands function
    }
    else if (command_line == 'Q') // quit the editor (does not save changes)
    {
      // Close files
      infile.close();
      return 0;
    }
    else
      cerr << "Error! Look at 'show commands' Instructions" << endl;
  }
}

/*
 *  Function displays all the commands
 */
void show_commands()
{
   cout << endl << "This line editor can do the following commands:"<< endl;
   cout << endl ;
   cout << "  I line   - insert line in front of current line" << endl;
   cout << "  A line   - append line to end of document" << endl;
   cout << "  R line   - replace current line"<< endl;
   cout << "  D        - delete the current line" << endl;
   cout << "  F target - makes line containing target current line" << endl;
   cout << "  S n      - set current line to nth line" << endl;
   cout << "  M n      - move current line n places" << endl;
   cout << "  C        - display current line to screen" << endl;
   cout << "  P        - display entire document to screen" << endl;
   cout << "  W file   - write document to file" << endl;
   cout << "  L file   - load file into this editor" << endl;
   cout << "  H        - display this list of commands" << endl;
   cout << "  Q        - quit the editor (does not save changes)" << endl;
   cout<< endl;
}
