#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAHPY_H

#include <iostream>
#include <map>

// Cryptopgrahy
// Stores functionality for breaking the enigma

float indexOfCoincidence(std::string text);
std::map<char,int> calculateLetterFrequency(std::string text);

float indexOfCoincidence(std::string text) {

    // takes in text
    // calculates Ic(x)

    // calculate the frequency of each letter (count)
    std::map<char,int> frequencies = calculateLetterFrequency(text);

    // sum frequencies (fi(fi - 1))
    float sum = 0;
    for (int i = 0; i < 26; i++) {
        char currentChar = char(i + 65);

        // if in map
        if (frequencies.find(currentChar) != frequencies.end()) {
            int currentFrequency = frequencies[currentChar];
            sum += currentFrequency * (currentFrequency - 1);
        }
    }

    // divide by length of text (n(n - 1))
    int n = text.length();
    float indexOfCoincidence = sum / (n * (n - 1));

    return indexOfCoincidence;
}

std::map<char,int> calculateLetterFrequency(std::string text) {

    std::map<char, int> frequencies;

    // for each character in text
    for (int i = 0; i < text.length(); i++) {
        // if alpha
        if (std::isalpha(text[i])) {
            // lower case
            char currentLetter = char(std::toupper(text[i]));
            
            // if exists in map
            if (frequencies.find(currentLetter) != frequencies.end()) {
                // ++
                frequencies[currentLetter]++;
            } else {
                // add it as 1
                frequencies[currentLetter] = 1;
            }
        }
    }
    
    //return map
    return frequencies;
}

#endif