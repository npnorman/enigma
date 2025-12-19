// Enigma machine sigmulation and cracking
// Nicholas Norman 2025

#include <iostream>
#include "utils.h"

void displayMenu();
void setupRotors();
void setupPlugboard();
std::string encrypt(std::string plaintext);
char encryptLetter(char letter);
void loadFile(std::string filename);
void saveFile();

int main() {

    //display menu
    // display menu, get choice, then return back to the menu
    std::string input;

    displayMenu();

    //while loop to have menu
    bool keepGoing = true;
    while(keepGoing) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input == "1") {
            //Set up machine
            setupRotors();

        } else if (input == "2") {
            //Encrypt / decrypt live

        } else if (input == "3") {
            //Encrypt / decrypt from a file
            
        } else if (input == "4") {
            //Crack

        } else if (input == "5") {
            //Display menu again
            displayMenu();
              
        } else if (input == "6") {
            //Exit
            std::cout << "Thank you for using the Enigma Machine. Schönen Tag noch!" << std::endl;
            keepGoing = false;
            
        } else {
            std::cout << "Please pick a new input" << std::endl;
        }
    }

    return 0;
}

void displayMenu() {
    // prompt the user to what mode they would like to enter
    // set up machine
    // encrypt / decrypt text
    // encrypt / decrypt from a file
    // break enigma
    // ... (more here for cracking)
    // exit

    std::cout << "--- ENIGMA SIMULATOR ---"
    << std::endl << "Nicholas Norman 2025"
    << std::endl
    << std::endl << "1) Setup Machine Rotors & Plugboard"
    << std::endl << "2) Encrypt live"
    << std::endl << "3) Encrypt from a file"
    << std::endl << "4) Break enigma (NOT IMPLEMENTED YET)"
    << std::endl << "5) Display Menu"
    << std::endl << "6) Exit Program"
    << std::endl;
}

void setupRotors() {
    // pick 3 out of 5 rotors (I,II,III,IV,V)
    
    // for each rotor
        // pick a starting letter
        
        // create a new rotor object
        // set it using ring number constant
        // find the mapping of the letter chosen to the ring offset
}