// Enigma machine sigmulation and cracking
// Nicholas Norman 2025

#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "utils.h"
#include "cryptography.h"

std::vector<Rotor> currentRotors;
bool isTracing = false;

void displayMenu();
void setupRotors();
void setupDefaultRotors();
void setupPlugboard();
void encryptLive();
void encryptFromFile();
void turnRotors();
std::string encrypt(std::string plaintext, bool traceOveride = false);
char encryptLetter(char letter);
char encryptLetterWithoutTrace(char letter);
void loadFile();
void saveFile();
std::string getFileName();
std::string getTextFromFile(std::string inFileName);

//cracking
void testIndexOfCoincidence();
void breakCiphertext();

//may need a backend setup rotor for cracking

int main() {

    //display menu
    // display menu, get choice, then return back to the menu
    std::string input;

    displayMenu();

    //while loop to have menu
    bool keepGoing = true;
    while(keepGoing) {

        //reset
        isTracing = false;

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
            testIndexOfCoincidence();

        } else if (input == "5") {
            //Crack
            breakCiphertext();

        } else if (input == "a") {
            //Display menu again
            displayMenu();
              
        } else if (input == "b") {
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
    << std::endl << "4) Calculate Index of Coincidence of file"
    << std::endl << "5) Break encrypted file"
    << std::endl << "a) Display Menu"
    << std::endl << "b) Exit Program"
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
    
    //ask to enable tracing
    std::cout << "Enable tracing (y/n)? ";
    std::getline(std::cin, input);

    if (input == "y") {
        isTracing = true;
    }

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

std::string encrypt(std::string plaintext, bool traceOveride) {
    std::string output = "";
    
    for (int i = 0; i < plaintext.length(); i++) {

        // if a plaintext letter, encrypt
        if (std::isalpha(plaintext[i])) {

            if (traceOveride) {
                output += encryptLetterWithoutTrace(plaintext[i]);
            } else {
                output += encryptLetter(plaintext[i]);
            }
            
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

    std::stringstream trace;

    //turn rotors first
    turnRotors();

    //trace start
    for (int i = 0; i < currentRotors.size(); i++) {
        trace << currentRotors[i].getRingOffset();
    }

    trace << ": " << char(std::toupper(letter));

    // convert letter to position (0-25)
    letter = char(std::toupper(letter));
    int letterPos = (int)letter - 65;

    //map through initial rotors
    for (int i = 0; i < currentRotors.size(); i++) {

        int currentRotorIndex = 2-i;

        //get forward mapping
        letterPos = currentRotors[currentRotorIndex].getForward(letterPos);

        //trace
        trace << " =" << currentRotors[currentRotorIndex].getName() << "=> " << char(letterPos + 65);
    }

    // reflect
    letterPos = Enigma_I_UKW_B[letterPos][1];

    // trace
    trace << " =R=> " << char(letterPos + 65);

    // for each rotor (backward)
    for (int i = 0; i < currentRotors.size(); i++) {
        // get mapping from rotor i, plug in last to current
        letterPos = currentRotors[i].getBackward(letterPos);

        //trace
        trace << " =" << currentRotors[i].getName() << "=> " << char(letterPos + 65);
    }

    if (isTracing) {
        std::cout << trace.str() << std::endl;
    }

    char newLetter = char(letterPos + 65);

    return newLetter;
}

char encryptLetterWithoutTrace(char letter) {

    //turn rotors first
    turnRotors();

    //trace start
    for (int i = 0; i < currentRotors.size(); i++) {
    }

    // convert letter to position (0-25)
    letter = char(std::toupper(letter));
    int letterPos = (int)letter - 65;

    //map through initial rotors
    for (int i = 0; i < currentRotors.size(); i++) {

        int currentRotorIndex = 2-i;

        //get forward mapping
        letterPos = currentRotors[currentRotorIndex].getForward(letterPos);
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
    std::string inFileName = "";
    std::cout << "Please type file name to encrypt: ";
    std::getline(std::cin, inFileName);

    std::string inPath = "./in/";
    std::string inFullPath = inPath + inFileName;

    // pull in file
    std::ifstream inputFile(inFullPath);

    // encrypted message
    std::string encrpytedMessage = "";

    // option to save with initial settings or not
    bool showInitialInfo = false;
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

std::string getFileName() {
    // ask which file in /in/ to encode
    std::string inFileName = "";
    std::cout << "Please type file name: ";
    std::getline(std::cin, inFileName);

    return inFileName;
}

std::string getTextFromFile(std::string inFileName) {
    std::string inPath = "./in/";
    std::string inFullPath = inPath + inFileName;

    // pull in file
    std::ifstream inputFile(inFullPath);

    //get entire test as a string
    std::string inputText = "";
    std::string line = "";
    
    while (std::getline(inputFile, line)) {
        inputText += line;
        inputText.push_back('\n');
    }

    inputFile.close();

    return inputText;
}

void testIndexOfCoincidence() {
    //get file
    std::string inFileName = getFileName();
    std::string inputText = getTextFromFile(inFileName);

    // print Ic
    std::cout << "Ic(English text) is approx 0.065, Ic(Random/Uniform text) is approx 0.0384" << std::endl;
    std::cout << "Index of Coincidence = " << indexOfCoincidence(inputText) << std::endl;

    displayMenu();
}

void breakCiphertext() {
    // set up rotors
    currentRotors.clear();

    for (int i = 0; i < 3; i++) {
        Rotor tempRotor = Rotor();
        currentRotors.push_back(tempRotor);
    }

    // set up defaults
    currentRotors[0].setRotor(RotorNumber::I);
    currentRotors[1].setRotor(RotorNumber::II);
    currentRotors[2].setRotor(RotorNumber::III);

    // get file text
    std::string inFileName = getFileName();
    std::string inputText = getTextFromFile(inFileName);

    // the idea is that getting part of the "key" correct
    // will make the index of coincidence better

    // all combos
    std::vector<RotorCombo> combos;

    // for each combination of rotor
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            
            if (j == i) {
                continue;
            }
            
            for (int k = 0; k < 5; k++) {
                
                if (k == j || k == i) {
                    continue;
                }

                //combination
                // change current rotor
                currentRotors[0].reset();
                currentRotors[1].reset();
                currentRotors[2].reset();
                currentRotors[0].setRotor(static_cast<RotorNumber>(i));
                currentRotors[1].setRotor(static_cast<RotorNumber>(j));
                currentRotors[2].setRotor(static_cast<RotorNumber>(k));

                // print out current config
                std::cout << "Trying ";
                for (int m = 0; m < currentRotors.size(); m++) {
                    // print config
                    std::cout << currentRotors[m].getName() << " ";
                }

                std::cout << std::endl;

                // for each initial position combination
                for (int ii = 0; ii < 26; ii++) {
                    for (int jj = 0; jj < 26; jj++) {
                        for (int kk = 0; kk < 26; kk++) {
                            //test all
                            currentRotors[0].setRingOffset(char(ii + 65));
                            currentRotors[1].setRingOffset(char(jj + 65));
                            currentRotors[2].setRingOffset(char(kk + 65));

                            // decode (encrypt)
                            std::string decryptedMessage = encrypt(inputText, true);

                            if ((ii * 676 + jj * 26 + kk) % 4000 == 0) {
                                std::cout << ".";  // Progress indicator
                                std::cout.flush();
                            }

                            // calculate index of coincidence
                            float ic = indexOfCoincidence(decryptedMessage);

                            // save combo
                            if (ic > 0.050) {
                                std::vector<int> tempVector = {i,j,k,ii,jj,kk};
                                combos.push_back({tempVector, ic});
                            }
                        }
                    }
                }
            }
        }
    }
    
    // sort vectors to find top 5
    std::sort(combos.begin(), combos.end(), [](const RotorCombo &a, const RotorCombo &b) {
        return a.ic < b.ic;
    });

    std::cout << "Top Ic(x) Scores: " << std::endl;
    for (int i = 0; i < 5; i++) {
        if (i < combos.size()) {
            for (int j = 0; j < combos[i].combo.size(); j++) {
                std::cout << combos[i].combo[j] << " ";
            }

            std::cout << "Ic(x) = " << combos[i].ic << std::endl;
        }
    }

    // save decrypted text in file
        // save to new file
    std::string outPath = "./out/";
    std::string outFileName = "";

    std::stringstream fileNameComponenets;
    for (int i = 0; i < combos[0].combo.size(); i++) {
        fileNameComponenets << combos[0].combo[i] << "_";
    }

    if (combos.empty()) {
        std::cout << "Not matching settings found" << std::endl;
        return;
    }

    outFileName = fileNameComponenets.str() + inFileName;

    std::string outFullPath = outPath + outFileName;

    std::ofstream outputFile(outFullPath);

    //decrypt message with saved combo
    std::string decryptedMessage = "";

    currentRotors[0].reset();
    currentRotors[1].reset();
    currentRotors[2].reset();
    currentRotors[0].setRotor(static_cast<RotorNumber>(combos[0].combo[0]));
    currentRotors[1].setRotor(static_cast<RotorNumber>(combos[0].combo[1]));
    currentRotors[2].setRotor(static_cast<RotorNumber>(combos[0].combo[2]));
    currentRotors[0].setRingOffset(static_cast<char>(combos[0].combo[3] + 65));
    currentRotors[1].setRingOffset(static_cast<char>(combos[0].combo[4] + 65));
    currentRotors[2].setRingOffset(static_cast<char>(combos[0].combo[5] + 65));

    decryptedMessage = encrypt(inputText, true);

    outputFile << decryptedMessage;
    outputFile.close();

    std::cout << outFileName << " written to /out/" << std::endl;

    // Note, use of Bigrams and Trigrams may be used in addition to index of coincidence.
    // As of now they are not in use.
}
