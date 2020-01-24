//Class: CS 215
//Assignment: Caesar Shift Cipher Program
//Programmer: kevil khadka

// A program to copy a textfile one character at a time

//Header files

#include <iostream> 
#include <fstream>   // ifstream, ofstream
#include <cstdlib>   // exit()

int main (int argc, char * argv[]) 
{
   using namespace std;

   // 1. Check for correct number of arguments
   
   if (argc != 4) {
     cerr << "Usage: " << argv[0] << " inputfile outputfile number_of_shift" << endl; 
     return -1;
   }

   int shift = stoi(argv[3]);      // convert strings into intergers
   
   // 2. Open files

   
   //File descriptors
   ifstream infile;             //declare an object of type ifstream
   ofstream outfile;            //declare an object of type ofstream
   
   infile.open(argv[1]);      //open text file to read from
   outfile.open(argv[2]);     //open text file to write to
   
   // 3. Check for successful opens

   if (!infile)             //check for input file if it opens or not
     {
       cerr <<  "Unable to open input file:" << argv[1] << endl;   //Display error message
       return 1;  
     }
   
   if(!outfile)            //check for output file 
     {
       cerr << "Unable to open output file:" << argv[2] << endl;
       return 1;
     }
   
   // 4. Copy one character at a time by
   //    Reading a char until stream fails (usually EOF)

   char ch;             //declare variable for reading in each character from infile 
   
   while(infile.get(ch)){        //get the value of character as an interger while looping

     if (isalpha(ch)) {
       if(isupper(ch))               // check for uppercase character
	 ch = (((ch - 'A') +  shift) % 26) + 'A'; //compute the right circular shift of a uppercase alphabetic character ch
       else
	 ch = (((ch - 'a') +  shift) % 26) + 'a';  //case for lowercase alphabetic character ch
     }
   
   // 4.1 Write char to output file
     outfile << ch;   
   }
   
   // 5. Close files
   
   infile.close();
   outfile.close();
   
   return 0; 
} // end main
