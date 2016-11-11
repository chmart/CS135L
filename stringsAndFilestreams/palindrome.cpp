/* This is an example program that demonstrates how to use strings and file streams
 * Problem:
 * -- Write a program that uses file streams to read in words from a file
 * -- It should also use file streams to write output to a diffrent file
 * -- The program should:
 *       o Display the current, unmodified string
 *       o Format the current string so the first letter is capital and rest are lower case and display it
 *       o Determine if the string a palidrome and say yes or no if it is or isn't 
 *       o l33t!fy d4 s7r!ng 
 * -- After all the data in the file is read, the program should:
 *       o Output the average number of letters per word
 *       o Output the number of palindromes found 
 * A Quick Lesson On Strings:
 * -- string is a data type just like int, double, char, etc. 
 * -- Strings are nothing more than an ordered list of char type variables
 * -- Each char variable in the row is indexed, starting from 0
 * -- The first char is 0, the second is 1, ... , the last one is n-1, where n is the length of the string
 * -- The length of a string can also be obtained easily because it is built in to the data structure
 * -- If we have a string called a, a.length() returns the number of chars in that string
 * -- Individual chars in a string can be accessed by using square brackets[]
 * -- In order to get the first char of the string a: a[0]
 * -- In order to get the last char of the string a: a[a.length()-1]
 * -- Strings can be used like any other variable, or they can be broken down into invididual chars */

#include <iostream>     // Provides general I/O
#include <iomanip>      // Provides setw() and setfill()
#include <fstream>      // Provides file stream operations
#include <cctype>       // Provides toipper() and tolower()
#include <string>       // Provides string data structure 

using namespace std;

// Prints the header row of the table
void printHeader(ofstream&);

// Prints a data row of the table
void printRow(ofstream&, string, int&);

// Prints the end data
void printEnd(ofstream&, int, double);

// Returns a nicely formatted version of the passed string
string makePretty(string);

// Returns true if the passed string is palindrome, false otherwise
bool isPalindrome(string);

// Returns a reversed version of the passed string
string reverseString(string);

// l33t!f!3z 4 s7r!ng n00b
string l33t1fy(string);

const int COL = 15;    // Defines the width of each column in the table 

// Main function
int main(){
  
  ifstream fin;       // Declare a new input stream
  ofstream fout;      // Declare a new output stream
  
  string filename;    // A string to hold file names
  string input;       // A string to hold the current string coming from the input stream

  int palCount = 0;   // Total number of palindromes so far
  int wordCount = 0;  // Total number of words being read
  int letterSum = 0;  // Sum of all the letters 

  // Prompt the user for a file name
  // Then read in whatever string they input
  cout << "Please enter the name of the file containing the input data: "; cin >> filename;

  // Open the file with that name given by the user
  // Note: file name must be casted to a C-style string using .c_str()
  // This is because the fstream library was carried over from C
  // In C, valid strings must be explicitly null terminated 
  fin.open(filename.c_str());

  // Error check the filename given by the user
  // If the file could not be opened sucessfully, fin will return false
  // Ask for a file name in a loop until a file with that name can be opened for input
  while(!fin){
    cout << "File with that name could not be opened for input." << endl
         << "Try another file name: "; cin >> filename;
    
    fin.open(filename.c_str());
  }

  // Prompt the user for the name of the output file 
  cout << "Please enter the name of file where the output should go: "; cin >> filename;

  // Open the output file (create it if it doesn't exist) for writing
  // NOTE: fout is a NEW output stream that writes to a file instead of the screen
  // fout can repleace cout for anywhere you want to write to the file
  fout.open(filename.c_str());
  
  // Left justify everything going into the output file 
  fout << left;

  // Print out the labels of the column
  printHeader(fout);

  // Read the first string from the input stream
  fin >> input;

  // Loop until there is no more input
  while(fin){

    // Print out a row for each word read from input
    printRow(fout, input, palCount);

    wordCount++;
    letterSum = letterSum + input.length();

    // Get the next word from input 
    fin >> input;
  }

  
  // When done with all the words, print out the final results
  printEnd(fout, palCount, double(letterSum)/wordCount);

  // Thank the kind human for his hard work 
  cout << "Thank you, kind human!" << endl
       << "The results of this program have been saved in a file called "
       << filename << endl;

  return 0;
}

// Print out the header row of the table
// Includes squiggly bars and labels for each column
void printHeader(ofstream& fout)
{
  // Send the header row to the output file
  fout << endl << setw(COL * 4) << setfill('~') << "~" << setfill(' ') << endl
       << setw(COL) << "Original Word"
       << setw(COL) << "Pretty Word"
       << setw(COL) << "Palindrome?"
       << setw(COL) << "l33tif13d" << endl
       << setw(COL * 4) << setfill('~') << "~" << setfill(' ') << endl;
}

/* Prints out a row of the table to the output file
 * Prints the unmodified string read from input
 * Prints the pretty version of the input string
 * Determines if the input string is a palindrome
 * If it is, say so and increment palindrome count
 * Otherwise, say no
 * l33t!fy th3 !npu7 s7r!ng */
void printRow(ofstream& fout, string input, int& palCount)
{
  // Send first part of row to the file
  fout << setw(COL) << input
       << setw(COL) << makePretty(input)
       << setw(COL);

  // If the word is a palindrome
  // Say yes and increment count
  if(isPalindrome(input)){
    fout << "Yes :^)";
    palCount++;            // palCount is passed by reference, so changes persist between function calls
  }
  // Otherwise, say no
  else
    fout << "No";

  // l33t!fy n00b
  fout << setw(COL) << l33t1fy(input) << endl;

}

// Prints the last part of the output to the file
// Count of palindromes is passed and displayed
// As well as average letters per word 
void printEnd(ofstream& fout, int count, double avg)
{
  fout << setw(COL * 4) << setfill('~') << "~" << setfill(' ') << endl;

  fout << "Avg # of letters per word: " << avg << endl
       << "# of palindromes: " << count << endl << endl;
}

// Returns a prettier looking version of the passed string
string makePretty(string input)
{
  char currentLetter;            // Holds the current letter in the string
 
  string prettyVersion = input;  // Make a copy of the passed input string 

  // Make the first letter of the string upper case
  prettyVersion[0] = toupper(input[0]);

  // Loop for the rest of the chars in the input string, skipping the first char
  for(int i = 1; i < input.length(); i++){
    
    currentLetter = input[i];               // Get the current letter from the string
    
    currentLetter = tolower(currentLetter); // Make the current letter lowercase
    
    prettyVersion[i] = currentLetter;       // Store the new lower case version in the pretty string
  }

  // Return the prettified version of the string 
  return prettyVersion;
}

/* Returns true if the passed string is a palindrome
 * Returns false otherwise
 * In order to determine if a string is a palindrome
 * We must compare the string to it's reversed version
 * If the string is the same when revered, it's a palindrome */
bool isPalindrome(string input)
{
  // First, we must format the string to one case
  // I have chosen to make the string all lower case letters
  input = makePretty(input);

  // makePretty() makes the first letter uppercase and the rest lower case
  // Make the first letter lowercase after calling makePretty() to make them all lowercase
  input[0] = tolower(input[0]);

  // Return true if input is equal to the reversed version
  // Returns false if the equality check fails 
  return (input == reverseString(input));
}

// Returns a reversed version of the passed input string
string reverseString(string input)
{
  string result = input;         // Make a copy of the given input string
  
  int len = result.length();     // Get the length of that string
  
  int j = len - 1;              // j is the index at the very end of the string

  // Loop for the length of the string
  // i is the index at the very beginning of the string
  // Set the first letter in the result string to be the last letter in the input stream
  // Then make the second letter in result, the second to last letter in input
  // Repeat this process for the whole string
  for(int i = 0; i < len; i++){
    result[i] = input[j-i];
  }

  // At the end of the loop, result will contain the reveresed version of input
  // Return the reversed version
  return result;
}

/* Returns a l337!f!3d version of the given input string
 * Basic l33t conversion is done according the following legend:
 * -- a = 4
 * -- e = 3
 * -- i = !
 * -- o = 0
 * -- t = 7
 * -- s = $
 * Conversion is done by checking each character in the string
 * If any character can be replaced by a l33t equivalent, then replace it
 */
string l33t1fy(string input)
{
  // Get the length of the input string
  int n = input.length();

  // Loop for the whole input string
  for(int i = 0; i < n; i++){

    // For the sake of simplicity, make the string all lower case
    input[i] = tolower(input[i]);

    // Switch on the current char in the string
    // Apply the l33t replacement if any cases are met
    switch(input[i]){
      
    case 'a': input[i] = '4'; break;
              
    case 'e': input[i] = '3'; break;
              
    case 'i': input[i] = '!'; break;
              
    case 'o': input[i] = '0'; break;

    case 't': input[i] = '7'; break;

    case 's': input[i] = '$'; break;
    }
  }

  // Return the l33t!f!3d string
  return input;
}
