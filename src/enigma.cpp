// Enigma machine sigmulation and cracking
// Nicholas Norman 2025

#include <iostream>
#include <vector>
#include <fstream>
#include "utils.h"

std::vector<Rotor> currentRotors;

void displayMenu();
void setupRotors();
void setupDefaultRotors();
void setupPlugboard();
void encryptLive();
void encryptFromFile();
void turnRotors();
std::string encrypt(std::string plaintext);
char encryptLetter(char letter);
void loadFile(std::string filename);
void saveFile();
//may need a backend setup rotor for cracking

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
            if (currentRotors.size() != 3) {
                setupDefaultRotors();
            }

            encryptLive();

        } else if (input == "3") {
            //Encrypt / decrypt from a file
            if (currentRotors.size() != 3) {
                setupDefaultRotors();
            }

            encryptFromFile();
            
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

    currentRotors.clear();

    // pick 3 out of 5 rotors (I,II,III,IV,V)
    std::cout << "Select 3 rotors from I,II,III,IV,V"
    << std::endl << "Type them in the order to be placed"
    << std::endl;

    for (int i = 0; i < 3; i++) {
        std::string rotorChoice = "";
        std::cout << "Rotor " << i+1 << ": ";
        std::getline(std::cin, rotorChoice);

        //may want to add a reset instead for time sake (cracking)
        Rotor tempRotor = Rotor();

        if (rotorChoice == "I") {
            tempRotor.setRotor(RotorNumber::I);
        } else if (rotorChoice == "II") {
            tempRotor.setRotor(RotorNumber::II);
        } else if (rotorChoice == "III") {
            tempRotor.setRotor(RotorNumber::III);
        } else if (rotorChoice == "IV") {
            tempRotor.setRotor(RotorNumber::IV);
        } else if (rotorChoice == "V") {
            tempRotor.setRotor(RotorNumber::V);
        }

        currentRotors.push_back(tempRotor);
    }

    for (int i = 0; i < currentRotors.size(); i++) {
        // for each rotor
        // pick a starting letter
        std::cout << "Pick a starting letter for " << currentRotors[i].getName() <<
        std::endl;
        std::string input;
        std::getline(std::cin, input);

        currentRotors[i].setRingOffset(input[0]);
    }

    displayMenu();
}

void setupDefaultRotors() {
    std::cout << "Setting rotors at default: I, II, III" << std::endl;

    currentRotors.push_back(Rotor());
    currentRotors.push_back(Rotor());
    currentRotors.push_back(Rotor());

    currentRotors[0].setRotor(RotorNumber::I);
    currentRotors[0].setRingOffset('A');

    currentRotors[1].setRotor(RotorNumber::II);
    currentRotors[1].setRingOffset('A');

    currentRotors[2].setRotor(RotorNumber::III);
    currentRotors[2].setRingOffset('A');
}

void encryptLive() {

    std::string input;

    bool keepGoing = true;
    while (keepGoing) {
        //get input as a string
        std::cout << "Enter plaintext or ciphertext (/ to exit): ";
        std::getline(std::cin, input);

        if (input == "/") {
            keepGoing = false;
        } else {
            //encrypt
            std::string encoded;
            encoded = encrypt(input);

            //print encrypted output
            std::cout << ">>> " << encoded << std::endl;
        }
    }

    displayMenu();
}

std::string encrypt(std::string plaintext) {
    std::string output = "";
    
    for (int i = 0; i < plaintext.length(); i++) {

        // if a plaintext letter, encrypt
        if (std::isalpha(plaintext[i])) {
            output += encryptLetter(plaintext[i]);
        } else {
            output += plaintext[i];
        }
        
    }

    return output;
}

void turnRotors() {
    // checks to move previous to see if they
    // were exposed to the pawl in the last keypress
    if (currentRotors[1].isAtNotch()) {
        // if L at notch, move M and L
        currentRotors[1].turnRotor();
        currentRotors[0].turnRotor();
    
    } else if (currentRotors[2].isAtNotch()) {
        // if R at notch, move M
        currentRotors[1].turnRotor();
    }

    // always turn 2 (R)
    currentRotors[2].turnRotor();
}

char encryptLetter(char letter) {

    //turn rotors first
    turnRotors();

    // convert letter to position (0-25)
    letter = std::toupper(letter);
    int letterPos = (int)letter - 65;

    //map through initial rotors
    for (int i = 0; i < currentRotors.size(); i++) {
        //get forward mapping
        letterPos = currentRotors[2-i].getForward(letterPos);
    }

    // reflect
    letterPos = Enigma_I_UKW_B[letterPos][1];

    // for each rotor (backward)
    for (int i = 0; i < currentRotors.size(); i++) {
        // get mapping from rotor i, plug in last to current
        letterPos = currentRotors[i].getBackward(letterPos);
    }

    char newLetter = char(letterPos + 65);

    return newLetter;
}

void encryptFromFile() {
    // ask which file in /in/ to encode

    std::string inPath = "./in/";
    std::string inFileName = "grace_hopper.txt";
    std::string inFullPath = inPath + inFileName;

    // pull in file
    std::ifstream inputFile(inFullPath);

    // encrypted message
    std::string encrpytedMessage = "";

    // option to save with initial settings or not
    bool showInitialInfo;
    std::cout << "Would you like to save initial setting in file (y/n)? ";
    std::string input;
    std::getline(std::cin, input);

    if (input == "y") {
        showInitialInfo = true;

        std::string names = "";
        std::string offsets = "";

        //write intial settings of each rotor
        for (int i = 0; i < currentRotors.size(); i++) {
            names += currentRotors[i].getName();
            offsets += currentRotors[i].getRingOffset();

            if (i < currentRotors.size() - 1) {
                names += ',';
            }
        }

        encrpytedMessage += names + ": " + offsets + "\n";
    }

    // encrypt it character by character
    char c;
    while (inputFile.get(c)) {
        //while not EOF
        //encrypt
        if (std::isalpha(c)) {
            encrpytedMessage += encryptLetter(c);
        }
    }

    inputFile.close();

    // save to new file
    std::string outPath = "./out/";
    std::string outFileName = "encoded_";

    // not initial information added in file name
    if (showInitialInfo) {
        outFileName += "settings_";
    }

    outFileName += inFileName;

    std::string outFullPath = outPath + outFileName;

    std::ofstream outputFile(outFullPath);
    outputFile << encrpytedMessage;
    outputFile.close();

    std::cout << outFileName << " written to /out/" << std::endl;

    displayMenu();
}