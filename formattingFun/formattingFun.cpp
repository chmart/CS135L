/*
 * Christian Martinez
 * CS 135L - 1006
 * Assignment #0?
 *
 * This program is intended to be a model for your programming assignments
 * Your program should be documented like this one, so try to mimic how this program is commented
 * This is also an example of an easy to understand strategy for formatting output with setw()
 *
 * Problem:
 * (This comment isn't necessary for your assignments, it's just so you know what this program does)
 ** At the XYZ Store, the regular price of an item is determined by doubling the wholesale price.
 ** Then when items are put on sale, the regular price is reduced by the sale rate.
 ** For example, if the wholesale price of an item is $10.00, the regular price will be $20.00.
 ** If the item is then put on sale for 20% off, the sale price will be $16.00,
 ** yielding a profit of $6.00.
 **
 **	Write a complete C++ program that will interactively prompt for and read
 ** the wholesale price of an item (floating point) and the percentage off sales rate (integer).
 ** The program should then determine the regular price of the item, the sale price of the item,
 ** and the profit from selling the item.
 *
 * Input: As input, this program expects the wholesale price of an item
 *        as well as the percentage off that item should be marked down
 * Output: This program will output the wholesale price given by the user,
 *         the retail price the item will be sold for, the sale rate the item
 *         will be marked down at, the price of the item after the markdown,
 *         and the profit made from the item.
 */
#include <iostream>
#include <iomanip>

using namespace std;

const int LABEL = 29;    // Constant for setting the width of labels

const int VALUE = 7;     // Constant for setting the width of values

int main(){

    double wholesalePrice;    // Wholesale price of an item entered by the user
    double profit;            // Profit made from selling the itemt
    double retailPrice;       // Price the item will be sold for retail
    double salePrice;         // Price the item will be sold for on sale
    int percentOff;           // Percent of the item will be on sale for

    // Dollar values always use 2 places after the decimal point
    // Set the precision of floating point values to 2 places after the decimal point
    cout << fixed << setprecision(2);

    // Say hello and prompt the user for the wholesale price
    cout << "Greetings, fellow seeker of truth." << endl
         << "Please enter the wholesale price of an item" << endl;   cin >> wholesalePrice;

    // Prompt for and recieve the sale rate
    cout << "What is the sale rate of the item?" << endl;     cin >> percentOff;

    // Sell the item for double the whole sale price
    retailPrice = 2 * wholesalePrice;

    // Calculate the sale price of the item
    salePrice = retailPrice - retailPrice * (double(percentOff)/100);

    // Calculate the profit
    profit = salePrice - wholesalePrice;

    // Print pretty stuff
    // Kawaii desu ne?
    cout << ".*.*.*.*.*.*:.\\(*'ᴗ'*)/.:*.*.*.*.*.*." << endl
         << "Profit Calculator Thing" << endl
         << "Christian Martinez" << endl
         << "Lab Sec #1006 Assignment #0?" << endl;

    /* Employ setw() strategy
     * Split up output into two parts: label and value
     * Have one line decdicated to label formatting
     * Have one line dedicated to value formatting
     * Separate label formatting and value formatting with a $ or space
     * Repeat the process over and over again 
     * Copy Pasta
     *
     * Allocate space for the width of the label + value + 1 (for divider character)
     * Fill that space with = 
     * Print an = to apply the setw()
     * This gives you a bar of = the width of your output  */
    cout << setw(LABEL + VALUE + 1) << setfill('=') << "=" << endl

         /* LABEL PART:
          * left - Left justify label text 
          * setw(LABEL) - Allocate space for the label
          * setfill('.') - Fill space with dots
          * "Label" - Print out Label */
         << left << setw(LABEL) << setfill('.') << "Wholesale Price" 

         // Separate label part from value part with $
         << "$"

         /* VALUE:
          * right - Right justify value text
          * setw(VALUE) - Allocate space for the value 
          * setfill(' ') - Fill space with blanks
          * var - Print out value 
          * endl - go to next line*/
         << right <<  setw(VALUE) << setfill(' ') << wholesalePrice << endl

         // Rinse and repeat that same process for all output
         // Print out retail price 
         << left << setw(LABEL) << setfill('.') << "Retail Price" 
         << "$"
         << right << setw(VALUE) << setfill(' ') << retailPrice << endl << endl

         // Print out sale rate
         << left << setw(LABEL) << "Sale Rate:" 
         << " "
         << right << setw(VALUE-1) << percentOff << "%" << endl

         // Print out sale price
         << left << setw(LABEL) << setfill('.') << "Sale Price" 
         << "$"
         << right << setw(VALUE) << setfill(' ') << salePrice << endl << endl

         // Print out profit
         << left << setw(LABEL) << setfill('.') << "Profit" 
         << "$"
         << right << setw(VALUE) << setfill(' ') << profit << endl

         // Hai, hontou ni kawaii desu!
         << ".*.*.*.*.*.*:.\\(*'ᴗ'*)/.:*.*.*.*.*.*." << endl;

   return 0;
}