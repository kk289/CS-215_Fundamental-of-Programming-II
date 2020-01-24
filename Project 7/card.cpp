// File: card.cpp
// Implementation file for card  class
// ----------------------------------------------------------------------
// Class: CS 215
// Project: card.cpp
// February 5, 2018

#include <iostream>
#include <cstdlib>
#include <sstream>
#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <stdlib.h>
#include "card.h"

using namespace std;

// Default Constructor
Card::Card ()
{
  value_char = 'A';
  suit_char = 'S';
}

// Explicit Constructor
Card::Card(char initial_value, char initial_suit)
{
  if(initial_value != 'A' && initial_value != '2' &&
     initial_value != '3' && initial_value != '4' &&
     initial_value != '5' && initial_value != '6' &&
     initial_value != '7' && initial_value != '8' &&
     initial_value != '9' && initial_value != 'T' &&
     initial_value != 'J' && initial_value != 'Q' &&
     initial_value != 'K')
    throw out_of_range("Invalid value.");
  
  value_char = initial_value;

  if (initial_suit != 'C' && initial_suit != 'D' &&
      initial_suit != 'H' && initial_suit != 'S')
    throw out_of_range("Suit must be C, D, H, or S.");

  suit_char = initial_suit;
}

// return the value character of this card
char Card::value() const
{
  return value_char;
}

// return the suit character of this card
char Card::suit() const
{
  return suit_char;
}

// return the numeric value of this card
int Card::numeric_value() const
{
  if(value_char == 'A')
    return 1;
  if(value_char == 'T')
    return 10;
  if(value_char == 'J')
    return 11;
  if(value_char == 'Q')
    return 12;
  if(value_char == 'K')
    return 13;
  else
    return value_char - '0';
}

// return the output equivalent of this card as a string
std::string Card::to_string() const
{
  string name;
  name.push_back(value_char);
  name.push_back(suit_char);

  return name;
}

// return the full name of this card as a string
std::string Card::full_name() const
{
  string eqv = "";

  if(value_char == 'A')
    eqv += "Ace";  
  if(value_char == '1')
    eqv += "One";
  if(value_char == '2')
    eqv += "Two";
  if(value_char == '3')
    eqv += "Three";
  if(value_char == '4')
    eqv += "Four";
  if(value_char == '5')
    eqv += "Five";
  if(value_char == '6')
    eqv += "Six";
  if(value_char == '7')
    eqv += "Seven";
  if(value_char == '8')
    eqv += "Eight";
  if(value_char == '9')
    eqv += "Nine";
  if(value_char == 'T')
    eqv += "Ten";
  if(value_char == 'J')
    eqv += "Jack";
  if(value_char == 'Q')
    eqv += "Queen";
  if(value_char == 'K')
    eqv += "King";

  eqv += " of ";
  
  if(suit_char == 'C')
    eqv += "Clubs";
  if(suit_char == 'D')
    eqv += "Diamonds";
  if(suit_char == 'H')
    eqv += "Hearts";
  if(suit_char == 'S')
    eqv += "Spades";
  
  return eqv;
}

// friend functions following
// == operator
bool operator == (const Card& lhs, const Card& rhs)
{
	if (lhs.value_char == rhs.value_char)
	{
	  return (lhs.suit_char == rhs.suit_char);
	}
	return false;
}

// < operator
bool operator < (const Card& lhs, const Card& rhs)
{
  if (lhs.numeric_value() < rhs.numeric_value())
  {
    return true;
  }
  else if (lhs.value_char == rhs.value_char)
  {
    if (lhs.suit() == 'C' && (rhs.suit() == 'D' || rhs.suit() == 'H' || rhs.suit() == 'S'))
      return true;
    else if (lhs.suit() == 'D' && (rhs.suit() == 'H' || rhs.suit() == 'S'))
      return true;
    else if (lhs.suit() == 'H' && rhs.suit() == 'S')
      return true;
  }
  return false;
}

// >= operator
bool operator >= (const Card& lhs, const Card& rhs)
{
  if (rhs < lhs || lhs == rhs)
    return true;
  else
    return false;
}

// > operator
bool operator > (const Card& lhs, const Card& rhs)
{
  return rhs < lhs;
}

// <= operator
bool operator <= (const Card& lhs, const Card& rhs)
{
  return rhs >= lhs;
 
}

// != operator
bool operator != (const Card& lhs, const Card& rhs)
{
  if (lhs.value_char != rhs.value_char)
  {
    return true;
  }
  else if (lhs.value_char == rhs.value_char &&
	     lhs.suit_char != rhs.suit_char)
  {
    return true;
  }
  return false;
}

// instream operator
std::istream & operator >> (std::istream & in,
			   Card & a_card)
{
  char val, suit;

  if (!in)
    return in;

  in >> val;
  if (in.peek() != 'C' && in.peek() != 'D' && in.peek() != 'H' && in.peek() != 'S')
  {
    in.setstate(ios_base::failbit);
    cout << "BAD INPUT(S)!" << endl;
    return in;
  }
  
  in >> suit;

  a_card.value_char = val;
  a_card.suit_char = suit;

  return in;
}

// outstream operator
std::ostream & operator << (std::ostream & out,
			   const Card & a_card)
{
  out << a_card.value() << a_card.suit();
  return out;
}

