// File: document.h
// Document
// Header file for document.cpp
// ----------------------------------------------------------------------
// Class: CS 215                      Instructor: Dr.Deborah Hwang
// Assignment: LIne Editior Program   Date assigned:/18 
// Programmer: kevil khadka           Date completed:/18

#ifndef DOCUMENT_H_   // if not define
#define DOCUMENT_H_
#include <stdexcept>
#include <vector>
#include <iostream> //istream, ostream

using namespace std;

class Document
{
 public:
        // Constructor
	Document();

	//explicit value constructor
	Document(std::istream & in);

	//operators
	void load(std::istream & in);

	bool is_empty() const;

	void insert(string new_line);

	void append(string new_line);

	void replace(string new_line);

	void erase();

	bool find(string target);

	void set_current(int n);

	void move_current(int n);

	void write_line(ostream & out) const;

	void write_all(ostream & out) const;
	
 private:
	// attributes declerations - any helper functions
       	vector<string> lines;
       	int curr;
};
#endif



      
