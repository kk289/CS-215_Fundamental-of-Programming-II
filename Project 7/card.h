// File: card.h
// Header file for card class that models a card number
// ----------------------------------------------------------------------
// Class: CS 215                Instructor: Dr.Deborah Hwang
// Assignment: Card Program   Date assigned: 1/27/18
// Programmer: kevil khadka     Date completed: 2/2/18

#ifndef CARD_H_   // if not define
#define CARD_H_

#include <iostream> //istream, ostream

class Card
{
 public://prototypes of operations for "programming users" of the type
    	// Constructor -same name as type
    	//   example of function overloading, ie >1 function of same name
    	//   with different numbers or type of argument
	
	Card();	// Default constructor

	Card(char initial_value,char initial_suit);//explicit value constructor
	
	//accessor

       	char value() const;
	char suit() const;
	int numeric_value() const;
	std::string to_string() const;
	std::string full_name() const;
	

	// attributes declerations - any helper functions
       	char value_char;
       	char suit_char;
	
  	//operators
     	// "friend" keyword "blessess" this function to allow it is access
      	//     the private data for this class]
      	// all obejcts are passed by reference by covention for efficency
      	//      received-only object are passed const
	
       	friend bool operator == (const Card & lhs, const Card & rhs);
	friend bool operator < (const Card & lhs, const Card & rhs);
 	friend bool operator > (const Card & lhs, const Card & rhs);
       	friend bool operator <= (const Card & lhs, const Card & rhs);		        
	friend bool operator != (const Card & lhs, const Card & rhs);
  	friend bool operator >= (const Card & lhs, const Card & rhs);
  
  

  	// I/O operators
	friend std::istream & operator >> (std::istream & in,  // P'BACK
					  Card & a_Card);  
  	friend std::ostream & operator << (std::ostream & out,
			 		  const Card & a_Card); // REC'D
 private:
	
	//	int v, s;   // card value and suit
};
#endif



      
