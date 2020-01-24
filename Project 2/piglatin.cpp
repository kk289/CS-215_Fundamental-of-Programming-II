// File: piglatin.cpp
// Descripition: It contains Header files, Function Prototypes, Main function and Function
// definitions.In this program, it translates English words in lowercase to a very simple
// form of Piglatin. There are three functions mention in function prototypes.
// It takes a word from input file and print its result in output file.
// ----------------------------------------------------------------------
// Class     : CS 215            Instructor    : Dr.Deborah Hwang
// Assignment: Piglatin Program  Date assigned : 1/31/18
// Programmer: kevil khadka      Date completed: 2/05/18

//Header files

#include <iostream> // cin, cout, endl
#include <fstream>  // ifstream, ofstream
#include <string>   // c++ string type
#include <cstdlib>  // exit()

using namespace std;

// Function Prototypes
void translate_sentence(string english_sentence, string & piglatin_sentence);
void translate_word (string english_word, string & piglatin_word);
bool isVowel(char letter); 

// main function
int main(int argc, char * argv[])
{ 
  string initial_word;     // initial variable to hold letter of input file
  string final_word;       // piglatin words after translation 
  
  // 1. Check for correct number of arguments
  if (argc != 3)
    {
     cerr << "Usage: " << argv[0] << " infile outfile " << endl; 
     exit(1);  // quits program with return value
   }
  
   // 2. Open files
  ifstream infile(argv[1]); // explicit -value construction of input file

  if (!infile)
     {
       cerr <<  "Unable to open input file:" << argv[1] << endl;
       exit(1);
     }
   
  ofstream outfile(argv[2]); // explicit - value construction of output file
  if(!outfile)
     {
       cerr << "Unable to open output file:" << argv[2] << endl;
       exit(1);
     }

  
  while(getline(infile, initial_word)) // get characters from the input stream and appends                                             // it to the string object until the delimiting character                                             // is found.
    {
      translate_sentence(initial_word, final_word); // calling function for translate sentence
      outfile << final_word << endl; // print out the piglatin words in outtputetext file    
    }
  
     // 5. Close files
  infile.close();
  outfile.close();
   
  return 0; 
}// end main


// function definitions

// function to receieve a line of words in all lowercase letters and passes back a string
// that is the pig latin translation of the word
void translate_sentence(string english_sentence, string & piglatin_sentence)
{
  piglatin_sentence = "";

  string final_word;
  string word;

  // to find first word
  size_t position = 0;                
  size_t space_position = english_sentence.find(' ', position);

  while(space_position != string::npos)
    {
      word = english_sentence.substr(position, space_position - position); 
      
      translate_word(word, final_word);     // calling translate_word function
      
      piglatin_sentence += final_word + " "; // each word followed by space too

      // find next word
      position = space_position + 1;
      space_position = english_sentence.find (' ', position);  // to find out the space
    }

  // it convert last word of each line without extra space
  word = english_sentence.substr(position);
  translate_word(word, final_word);
  
  piglatin_sentence += final_word;//it doesnt keep extra space at the end
}

// function to receiece a word in all lowercase letters and passes back a string that is
// the pig latin translation of the word
void translate_word(string english_word, string &piglatin_word)
{
  char lastLetter = english_word.length()-1;   // variable to get last letter
  piglatin_word = english_word;    // assign to piglatin_word as passing variable
  
  if(isVowel(english_word[0]))      // check first letter of each word
    {
      piglatin_word +=  "ay";      // if word is vowel, it add 'ay' 
    }
  else
    {
      string otherLetters = english_word.substr(1, lastLetter); // else it just print out the word taking
                                                                // first letter to last and add "ay"
      piglatin_word = otherLetters + english_word[0] + "ay";  // add ay to last letter of a word
    }

}

// function to check for vowel letter in each word
bool isVowel(char letter)
{
  return (letter == 'a' || letter == 'e' || letter == 'i' ||
	 letter == 'o' || letter == 'u');
}
