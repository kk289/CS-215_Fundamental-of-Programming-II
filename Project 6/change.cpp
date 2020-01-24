//Class: CS 215
//Assignment:Change.cpp
//Programmer: kevil khadka

#include <iostream>  // cout, endl
#include <cmath>     // change_compute()
#include <fstream>  //ifstream, ofstream
#include <iomanip>  // setw(), left, right

//Function Prototypes
void compute_change( int no_of_cents, int & dollar, int & quarters,
		       int & dimes, int & pennies);

int main(int argc, char * argv[])
{
   using namespace std;

   // 1. Check for correct number of arguments
   
   if (argc != 3)
   {
     cerr << "Usage: " << argv[0] << " infile outfile " << endl; 
     exit(1);  //quits program with return value
   }
   
   // 2. Open files
   
   ifstream infile(argv[1]); //explicit -value construction of input file
   if (!infile)
   {
      cerr <<  "Unable to open input file" << argv[1] << endl;
      exit(1);
   }
   
   ofstream outfile(argv[2]); //explicit - value construction of output file
   if(!outfile)
   { 
      cerr << "Unable to open output file" << argv[2] << endl;
      exit(1);
   }
   //Declaring variables
   int money;         //a positive integer representing a number of cents
   int dollar_no;     
   int quarters_no;
   int dimes_no;
   int pennies_no;

   //Make a table in output file 
   outfile << setw(10) << "Amount" << setw(10) << "Dollars"
        << setw(10) << "Quarters" << setw(10) << "Dimes"
        << setw(10) << "Pennies" << endl;

   //put space
   outfile << endl;
   
   while(infile >> money)
     {
      //function call
       compute_change(money, dollar_no, quarters_no, dimes_no, pennies_no);
       
      //Write results to output file
       outfile << setw(10) << money << setw(10) << dollar_no
	       << setw(10) << quarters_no << setw(10) << dimes_no
	       << setw(10) << pennies_no << endl;

      cout << right; // make output right justified in field width
     }

   // close files

   infile.close();
   outfile.close();

   return 0;
   
} //end main

//Function Definition
void compute_change( int no_of_cents, int & dollar, int & quarters,
		       int & dimes, int & pennies)
 {
   
   int remainder; //temporary variable 

   //calculation
   dollar = no_of_cents / 100;

   remainder = no_of_cents % 100;
   
   quarters = remainder / 25;

   remainder = remainder % 25;
   
   dimes = remainder / 10;

   remainder = remainder % 10;

   pennies = remainder;
   
 }

