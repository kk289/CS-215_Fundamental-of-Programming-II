// File: document.cpp
// Implementation file for document class
// ---------------------------------------------------------------------
// Class: CS 215                     Instructor: Dr.Deborah Hwang
// Assignment: Line Editor Program   Date assigned: 02/12/18
// Programmer: kevil khadka          Date completed:03/02/18

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <stdlib.h>
#include <vector> // STL vector class template
#include <string>
#include "document.h"

using namespace std;

// Default Constructor
Document::Document()                 // initiialized the current line index to -1
{
  curr = -1;
}

// Explicit Constructor
Document::Document(std::istream & in) // REC'D & PB   // input stream 
{
  string line;
  while (getline(in, line))      // read in the data 
  {
    lines.push_back(line);      // add value to end of lines
  }
  curr = 0;     // current line is set to the first line:: index = 0
}

//template <typename T> 
void Document::load(std::istream & in)  // REC'D & PB
{
  // Assume that we want to get rid of anything that was already in line
  lines.clear();  // reset line to empty
  curr = 0;  
  
  string line;     
  while (getline(in, line))
  {
    lines.push_back(line); // add value to end of lines
  }
}

bool Document::is_empty() const   // operator returns true if the document is empty
{                                 // otherwise false
  return curr < 0;
}

//template <typename T>
void Document::insert(string new_line)  // insert a line infront of the current line 
{
  // int i=0;
  //temp_lines = this->lines;
  if(this->is_empty())     
  {
    lines.push_back(new_line);
    curr = 0;
  }
  else
  {
    lines.push_back("");
    for(int i = lines.size()-1; i > curr; i--) 
    {
      lines[i] = lines[i-1]; 
    }
    lines[curr] = new_line;
  }
}

void Document::append(string new_line) // operator inserts a line at the end of document
{
  lines.push_back(new_line);
  curr = lines.size()-1;
}

//template <typename T>
void Document::replace(string new_line) // operator replaces the content of the current 
{                                       // line.
  
  if(this->is_empty())
    throw std::out_of_range("Illegal Operation!\n");
  else
    lines[curr] = new_line;    
}

void Document::erase()  // operator removes current line from the document
{
  if(this->is_empty())
    throw std::out_of_range("Illegal Operation!\n");
  else
  {  
    for (int i = curr; i < lines.size() - 1; i++) 
    {
      lines[i] = lines[i+1];   // last line becomes current line
    }
    lines.pop_back();    // removes the last line

    if (curr == lines.size())
      curr--;
  }
}

bool Document::find(string target) // operator returns true or false when it
{                                  // finds the first line in tthe document 
  for(int i = 0; i < lines.size(); i++) // search index is set 0
    {                                   
    if(lines[i].find(target) != std::string::npos)
    {
      curr = i;       // set current line to same
      return true;  
    }
  }
  return false;
}

void Document::set_current(int n)  // operator sets the current line
{
  if(n < 0 || this->lines.size() <= n)  
    throw std::out_of_range("Illegal operation!\n");
  else
    curr = n;   // set current line to same
}

void Document::move_current(int n)  // operator moves the current line n places
{
  if(n > 0 && ( curr + n < lines.size()))
    curr = curr + n;   // current line moves forward direction (towards the end)
  else if(n < 0 && (curr + n) >= 0)
    curr = curr + n;  
  else
    throw std::out_of_range("Illegal operation!\n");
}

void Document::write_line(std::ostream & out) const // operator helps to write the current
{                                                   // lines, newline, to output stream
  if(!is_empty())
    out << lines[curr] << endl;
}

void Document::write_all(std::ostream & out) const // operator writes all the lines, with
{                                               // ending newlines, starting with first line
                                                // to an output stream    
  for(int i = 0; i < lines.size(); i++) 
  {
    out << lines[i] << endl;
  }
}


