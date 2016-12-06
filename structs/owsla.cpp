// Structs demonstration program
// This program demonstrates using an array of structs to store data
// It expects two input files:
// - The first contains albums to be stored (called albums in github repo)
// - The second contains data on changes to make to those albums (called changes in github repo)
// Run the program yourself to see what happens!
#include <iostream>     // Provides cin/cout
#include <iomanip>      // Provides setw
#include <fstream>      // Provides filestreams
#include <string>       // Provides strings
#include <cctype>       // Provides toupper/tolower

using namespace std;

// Constant variables
const int MAX = 30;
const int NAME = 25;
const int ID = 3;
const int YEAR = 8;
const int PRICE = 6;

// Album data structure
// Each album is defined by artist and album names, id, release year, and price
struct album{
    string artist, album;
    int id, year;
    double price;
};

// Function Prototypes:
string prettify(string);
int match(album[], int, int);
void openInput(ifstream&);
void readAlbums(ifstream& , album[], int&);
void processChanges(ifstream&, album[], int);
void print(album[], int);
void bubblesort(album[], int);

int main(){

    // Create a file stream to read input from
    ifstream fin;

    // Keep a count of the number of albums that will be rad
    int count = 0;

    // Create an array of albums to hold the data from the file
    album collection[MAX];

    // Set precision for dollar values and ask for the first input file
    cout << fixed << setprecision(2) << "Enter name of first data file" << endl;

    // Attempt to copy the contents of the file into the filestream fin
    openInput(fin);

    // Read in all the data into the array of albums
    readAlbums(fin, collection, count);

    // Close the file stream after you are done reading
    // This is so you can reopen it later with a different filename 
    fin.close();

    // Sort the array in alphabetical order
    bubblesort(collection, count);

    // Print the sorted albums 
    print(collection, count);

    // Ask for the name of the second input file and try to open it
    cout << "Enter name of second data file" << endl;
    openInput(fin);

    // Process the changes to the albums
    processChanges(fin, collection, count);

    // Print out the final result
    print(collection, count);

    // Close the filestream for completeness
    fin.close();

    return 0;
}

// prettify
// Expects: A string type variable
// Returns: A copy of the string with first letter uppercase and the rest lowercase
string prettify(string s)
{
    // Make the first letter uppercase
    s[0] = toupper(s[0]);

    // Loop to make the rest of the letters lowercase. 
    for(int i = 1; i < s.length(); i++)
        s[i] = tolower(s[i]);

    // Return the modified string 
    return s;
}

// match
// Expects: An array of album data structures
//          An ID that might be in the array
//          Size of the array 
// Returns: The position in the array where the album with the given ID is found
//          -1 if the given ID was not found in the array
int match(album collection[], int id, int count)
{
    // Loop through the entire array of structs
    for(int i = 0; i < count; i++){

        // If a matching ID was found
        if(id == collection[i].id)
            return i;             // Return the index that you found it at
    }
    
    // Otherwise return -1 to indicate no such ID was found
    return -1;
}

// openInput
// Expects: A filestream variable that will be opened
// Takes in a file name entered by the user and attempts to open that file for input
// If the file could not be opened, repeatedly ask until a valid file is entered
void openInput(ifstream& fin)
{

    // Declare a string and read into it
    string filename;
    cin >> filename;

    // Attempt to open the file
    fin.open(filename.c_str());

    // Error check the filename given by the user
    // If the file could not be opened sucessfully, fin will return false
    // Ask for a file name in a loop until a file with that name can be opened for input
    while(!fin){
        cout << "File with that name could not be opened for input." << endl
             << "Try another file name: "; cin >> filename;
    
        fin.open(filename.c_str());
    }
}

// readAlbums
// Expects: An opened file stream to read from
//          A collection of album data structures
//          An integer counter starting at 0 (very important)
// Populates the array of albums with the data from the file stream
// Increments the count of albums being read for bookkeeping purposes
void readAlbums(ifstream& fin , album collection[], int& count)
{
    // Read the first artist into the first album struct
    // NOTE: count should be 0 at this point, since that is what the function expects 
    fin >> collection[count].artist;

    // Loop until there is no more input to read
    while(fin){

        // Read the album pertaining to the previous artist
        fin >> collection[count].album;

        // Prettify the string since it isn't guarnteed to be pretty
        collection[count].album = prettify(collection[count].album);

        // Read in the rest of the data (id, year, price)
        fin >> collection[count].id 
            >> collection[count].year
            >> collection[count].price;

        // Increment the count to put the following data into the next struct
        // Also to keep track of how many times you've done this...
        count++;

        // Attempt to read in the next artist name
        fin >> collection[count].artist;
    }
}

// processChanges
// Expects: An open file stream to read changes from
//          An array of album structs to apply changes to
// Reads data from the input stream containing codes to change the structs
// Applies changes to the structs, and outputs what changes were made
// If an invalid ID is found, the rest of the line is skipped 
void processChanges(ifstream& fin, album collection[], int count)
{   
    int id;      // ID of the album to which the changes need to be applied
    int index;   // Index of where the album with that ID is in the array
    char cmd;    // Command that says which change will be made

    // Read in the first change ID
    fin >> id;

    // Loop while there is still input to be read
    while(fin){

        // Match the given ID to an index in the array
        index = match(collection, id, count);

        // If the index is valid
        if(index >= 0){

            // Take in the command of the change to be made
            fin >> cmd;

            // If the command is P, it's a price change
            if(cmd == 'P'){

                // Read the new price into the album struct
                fin >> collection[index].price;

                // State the change that was made
                cout << "ID# " << id << " price changed to "
                     << collection[index].price << endl;
            }

            // Otherwise the command is a year change (there's only two options)
            else{

                // Read in the updated release year              
                fin >> collection[index].year;

                // State the chnages that were made
                cout << "ID# " << id << " release year changed to "
                     << collection[index].year << endl; 
            }
        }

        // If the ID could not be matched to an index, throw an error   
        else{
            cout << "ID# " << id << " is invalid" << endl;

            // When the ID given is invalid, skip anything left on that line
            // This can be done with the ignore() function in fstream
            // For more info: http://www.cplusplus.com/reference/istream/istream/ignore/
            fin.ignore(80, '\n');
        }
        
        // Attempt to read the next ID
        fin >> id;
    }
}

// print
// Expects: A populated array of album structs
//          How many albums are in the collection
// Prints out the collection in a nice table format
void print(album collection[], int count)
{
    cout << left << endl
         << setw(NAME) << "NAME"
         << right << setw(ID) << "ID#"
         << setw(YEAR) << "YEAR" << "   "
         << setw(PRICE) << "PRICE" << endl;

    // Create a string to concatenate the album and arist name for easy printing
    string name;

    // Loop through all the structs
    for(int i = 0; i < count; i++){

        // Concatenate the album and artist names so they can be used easily with setw()
        name = collection[i].album + " - " +collection[i].artist;

        cout << left << setw(NAME) << name
             << right << setw(ID) << collection[i].id
             << setw(YEAR) << collection[i].year
             << "  $"
             << setw(PRICE) << collection[i].price << endl;
    }
    cout << endl;
}

void bubblesort(album list[ ],int count)
// Sort an array of integers into descending order.
// Parameters:
// list – array of albums to be sorted
// count – (integer) number of values in the array
// Value passed back: sorted list
{
    album temp;                           //place holder when values are interchanged
    for (int i=0; i < count-1; i++)
        for (int j=0; j < count-(i+1); j++)
            if (list[j].album > list[j+1].album)     // Sort based on the album name
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
}