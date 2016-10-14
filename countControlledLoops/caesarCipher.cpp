/* Christian Martinez
 * CS 135L
 * Caesar Cipher Decrypter
 * This is a program that decrypts messages encoded using a Caesar Cipher
 * If you are unfamiliar with a Caesar Cipher, look here:
 * http://practicalcryptography.com/ciphers/caesar-cipher/
 * This program is to be given a file via Linux redirection
 * The file will contain the following:
 * - One integer saying how many lines need to be decoded
 * - One integer number saying how much the cipher shifted the message
 * - Multiple lines of text encoded using a Caesar Cipher
 * Assumptions:
 * - The data file will ALWAYS contain those two integers at the beginning
 * - The two integers will always be valid (no error checking needed)
 * - All the letters in the message will be lower case (no need to convert/check)
 * This program will output the decoded message to the screen */

#include <iostream>          // Provides cout/cin/end/etc
#include <cctype>            // Provides isalpha()

using namespace std;

int main(){

    int totalLines;       // Total lines of text that need to be decrypted
    int shiftAmount;      // Amount of shifting in the encrypted messaged

    char currentChar;     // Current char coming from the input stream
    char shiftedChar;     // Decrypted char after shifting

    cin >> totalLines;    // Read in the total number of lines to be decrypted

    cin >> shiftAmount;   // Reading in the amount of shifting going on

    cin >> currentChar;   // Read in the first char to be decrypted
                          // cin >> x will skip any whitespace after the two numbers
                          // and go right to the first char

    // Loop once for each line you of text you are decrypted
    for(int i = 0; i < totalLines;){

        // If the char coming from input is a letter, decrypt it
        if(isalpha(currentChar)){
            // First shift the car char by the amount given
            shiftedChar = currentChar - shiftAmount;

            // Subtract the ASCII value of 'a' from the shifted char
            shiftedChar -= 97;

            // Add 26 to the char in case the shifted result is negative
            shiftedChar += 26;

            // There are 26 possible letters, so mod by 26 to say in the alphabet
            shiftedChar %= 26;
            
            // Add the ASCII value of 'a' back to make it a value letter again
            shiftedChar += 97;

            // Output the decrypted character
            cout << shiftedChar;
        }
        // If the char coming from input is a line feed
        // Increment i to go to the next loop, print out a line feed
        else if(currentChar == 10){
            i++;
            cout << endl;
        }
        // Otherwise print out whatever non letter character is coming from input
        else
            cout << currentChar;

        /* Get the next character from input
         * NOTE: I am using cin.get(x) because it does NOT skip whitespace
         *       cin >> x would skip any whitespace including line feeds and spaces
         *       But we need to use the line feeds to know when to increment the loop counter
         *       And we need to print any spaces from the original message
         *       So cin.get() is necessary inside the loop */
        cin.get(currentChar);
    }
    return 0;
}