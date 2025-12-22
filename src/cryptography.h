#ifndef CRYPTOGRAPHY_H
#define CRYPTOGRAHPY_H

#include <iostream>
#include <map>

// Cryptopgrahy
// Stores functionality for breaking the enigma

float indexOfCoincidence(std::string text);
void calculateLetterFrequency(std::string text, int frequencies[]);

float indexOfCoincidence(std::string text) {

    // takes in text
    // calculates Ic(x)

    // calculate the frequency of each letter (count)
    int frequencies[26] = {0};
    calculateLetterFrequency(text, frequencies);

    // sum frequencies (fi(fi - 1))
    float sum = 0;
    for (int i = 0; i < 26; i++) {
        int currentFrequency = frequencies[i];
        sum += currentFrequency * (currentFrequency - 1);
    }

    // divide by length of text (n(n - 1))
    int n = text.length();
    float indexOfCoincidence = sum / (n * (n - 1));

    return indexOfCoincidence;
}

void calculateLetterFrequency(std::string text, int frequencies[]) {

    // for each character in text
    for (int i = 0; i < text.length(); i++) {
        // if alpha
        if (std::isalpha(text[i])) {
            // lower case
            int currentLetter = std::toupper(text[i]) - 65;
            
            frequencies[currentLetter]++;
        }
    }
}

#endif