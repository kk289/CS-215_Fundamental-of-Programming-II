// File: carddriver.cpp
// Descripition: Test program for card class
// ----------------------------------------------------------------------
// Class: CS 215              Instructor: Dr.Deborah Hwang
// Assignment: Card Program   Date assigned: 2/04/18
// Programmer: kevil khadka   Date completed:/18

//Header files
#include <iostream>
#include <string>
#include <stdexcept>

#include "card.h"

using namespace std;

// function prototypes
void CardCheck(Card c, char val, char s);
void Check(string result, string expect);

int main ()  // no command-line arguments
{
 
   Card ex1;               // Default value
   Card ex2('7','D');
   Card ex3('7','C'); // Explicit-value construction
   
   cout << "This is test for constructors" << endl;
   CardCheck(ex1, 'A', 'S');
   CardCheck(ex2, '7', 'D');
   CardCheck(ex3, '7', 'C');

   cout << "This is test for numeric_value" << endl;
   Check(to_string(ex1.numeric_value()), "1");
   Check(to_string(ex2.numeric_value()), "7");
   
   cout << "This is test for to_string" << endl;
   Check(ex1.to_string(), "AS");
   Check(ex2.to_string(), "7D");
   Check(ex3.to_string(), "7C");
 
   cout << "This is test for full_name" << endl;
   Check(ex1.full_name(), "Ace of Spades");
   Check(ex2.full_name(), "Seven of Diamonds");
   Check(ex3.full_name(), "Seven of Clubs");
   
   cout << "This is test for friend operators" << endl;
   if(ex2 == ex2)
     cout << "Test operator (==): " << "PASS" << endl;
   if(ex1 < ex2)
     cout << "Test operator (<) : " << "PASS" << endl;
   if(ex2 >= ex3)
     cout << "Test operator (>=): " << "PASS" << endl;
   if(ex1 <= ex2)
     cout << "Test operator (<=): " << "PASS" << endl;
   if(ex1 != ex2)
     cout << "Test operator (!=): " << "PASS" << endl;
   if(ex2 > ex3)
     cout << "Test operator (>) : " << "PASS" << endl;

   cout << "Enter to cards: ";
   cin >> ex1 >> ex2;
   cout << "ex1 is: " << ex1 << endl;
   cout << "ex2 is: " << ex2 << endl;
   
   
   return 0;
     
}

void CardCheck(Card c, char val, char s)
{
  if(c.value() == val && c.suit() == s)  
    cerr << "PASS" << endl;
  else
    cerr << "FAIL!" << endl; 
}

void Check(string result, string expect)
{
  if(result == expect)
    cerr << "PASS" << endl;
  else
    cerr << "FAIL!" << endl;
}
