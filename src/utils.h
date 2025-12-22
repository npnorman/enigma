#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <array>

// Utils
// Stores information about the rotors, including settings, ring switches, and more

// rotor settings
// https://en.wikipedia.org/wiki/Enigma_rotor_details

//1930 Enigma I
std::array<std::array<int,2>,26> Enigma_I_I = {{ {0,4},{1,10},{2,12},{3,5},{4,11},{5,6},{6,3},{7,16},{8,21},{9,25},{10,13},{11,19},{12,14},{13,22},{14,24},{15,7},{16,23},{17,20},{18,18},{19,15},{20,0},{21,8},{22,1},{23,17},{24,2},{25,9}, }};
std::array<std::array<int,2>,26> Enigma_I_II = {{ {0,0},{1,9},{2,3},{3,10},{4,18},{5,8},{6,17},{7,20},{8,23},{9,1},{10,11},{11,7},{12,22},{13,19},{14,12},{15,2},{16,16},{17,6},{18,25},{19,13},{20,15},{21,24},{22,5},{23,21},{24,14},{25,4}, }};
std::array<std::array<int,2>,26> Enigma_I_III = {{ {0,1},{1,3},{2,5},{3,7},{4,9},{5,11},{6,2},{7,15},{8,17},{9,19},{10,23},{11,21},{12,25},{13,13},{14,24},{15,4},{16,8},{17,22},{18,6},{19,0},{20,10},{21,12},{22,20},{23,18},{24,16},{25,14}, }};
std::array<std::array<int,2>,26> Enigma_I_IV = {{ {0,4},{1,18},{2,14},{3,21},{4,15},{5,25},{6,9},{7,0},{8,24},{9,16},{10,20},{11,8},{12,17},{13,7},{14,23},{15,11},{16,13},{17,5},{18,19},{19,6},{20,10},{21,3},{22,2},{23,12},{24,22},{25,1}, }};
std::array<std::array<int,2>,26> Enigma_I_V = {{ {0,21},{1,25},{2,1},{3,17},{4,6},{5,8},{6,19},{7,24},{8,20},{9,15},{10,18},{11,3},{12,13},{13,7},{14,11},{15,23},{16,0},{17,22},{18,12},{19,9},{20,16},{21,14},{22,5},{23,4},{24,2},{25,10}, }};
std::array<std::array<int,2>,26> Enigma_I_UKW_B = {{ {0,24},{1,17},{2,20},{3,7},{4,16},{5,18},{6,11},{7,3},{8,15},{9,23},{10,13},{11,6},{12,14},{13,10},{14,12},{15,8},{16,4},{17,1},{18,5},{19,25},{20,2},{21,22},{22,21},{23,9},{24,0},{25,19}, }};
int Enigma_I_I_switch = 16; //Q
int Enigma_I_II_switch = 4; //E
int Enigma_I_III_switch = 21; //V
int Enigma_I_IV_switch = 9; //J
int Enigma_I_V_switch = 25; // Z

//Enigma M3
std::array<std::array<int,2>,26> Enigma_M3_I = {{ {0,4},{1,10},{2,12},{3,5},{4,11},{5,6},{6,3},{7,16},{8,21},{9,25},{10,13},{11,19},{12,14},{13,22},{14,24},{15,7},{16,23},{17,20},{18,18},{19,15},{20,0},{21,8},{22,1},{23,17},{24,2},{25,9}, }};
std::array<std::array<int,2>,26> Enigma_M3_II = {{ {0,0},{1,9},{2,3},{3,10},{4,18},{5,8},{6,17},{7,20},{8,23},{9,1},{10,11},{11,7},{12,22},{13,19},{14,12},{15,2},{16,16},{17,6},{18,25},{19,13},{20,15},{21,24},{22,5},{23,21},{24,14},{25,4}, }};
std::array<std::array<int,2>,26> Enigma_M3_III = {{ {0,1},{1,3},{2,5},{3,7},{4,9},{5,11},{6,2},{7,15},{8,17},{9,19},{10,23},{11,21},{12,25},{13,13},{14,24},{15,4},{16,8},{17,22},{18,6},{19,0},{20,10},{21,12},{22,20},{23,18},{24,16},{25,14}, }};
std::array<std::array<int,2>,26> Enigma_M3_IV = {{ {0,4},{1,18},{2,14},{3,21},{4,15},{5,25},{6,9},{7,0},{8,24},{9,16},{10,20},{11,8},{12,17},{13,7},{14,23},{15,11},{16,13},{17,5},{18,19},{19,6},{20,10},{21,3},{22,2},{23,12},{24,22},{25,1}, }};
std::array<std::array<int,2>,26> Enigma_M3_V = {{ {0,21},{1,25},{2,1},{3,17},{4,6},{5,8},{6,19},{7,24},{8,20},{9,15},{10,18},{11,3},{12,13},{13,7},{14,11},{15,23},{16,0},{17,22},{18,12},{19,9},{20,16},{21,14},{22,5},{23,4},{24,2},{25,10}, }};
std::array<std::array<int,2>,26> Enigma_M3_UKW_B = {{ {0,24},{1,17},{2,20},{3,7},{4,16},{5,18},{6,11},{7,3},{8,15},{9,23},{10,13},{11,6},{12,14},{13,10},{14,12},{15,8},{16,4},{17,1},{18,5},{19,25},{20,2},{21,22},{22,21},{23,9},{24,0},{25,19}, }};

enum RotorNumber {
    I,
    II,
    III,
    IV,
    V
};

// rotor class
class Rotor {
 private:
    std::map<int, int> forward;
    std::map<int, int> backward;
    int ringOffset;
    int ringSwitch; //turnover
    std::string rotorName;

    int getMap(bool isForward, int index) {

        index += ringOffset;
        index %= 26;

        int finalIndex = 0;

        if (isForward) {
            finalIndex = forward[index];
        } else {
            //final letter is the mapped letter - the original offset
            finalIndex = backward[index];
        }

        finalIndex = (((finalIndex- ringOffset) % 26) + 26) % 26;

        return finalIndex;
    }

 public:
    Rotor() {}

    void setRotor(RotorNumber rotorNumber) {

        std::array<std::array<int, 2>, 26> setting = {};
        int ringSwitch;

        switch (rotorNumber)
        {
        case I:
            setting = Enigma_M3_I;
            ringSwitch = Enigma_I_I_switch;
            rotorName = "I";
            break; // to stop falling through other case statements
        case II:
            setting = Enigma_M3_II;
            ringSwitch = Enigma_I_II_switch;
            rotorName = "II";
            break; // to stop falling through other case statements
        case III:
            setting = Enigma_M3_III;
            ringSwitch = Enigma_I_III_switch;
            rotorName = "III";
            break; // to stop falling through other case statements
        case IV:
            setting = Enigma_M3_IV;
            ringSwitch = Enigma_I_IV_switch;
            rotorName = "IV";
            break; // to stop falling through other case statements
        case V:
            setting = Enigma_M3_V;
            ringSwitch = Enigma_I_V_switch;
            rotorName = "V";
            break; // to stop falling through other case statements
        }

        // set up mapping
        for (int i = 0; i < 26; i++) {
            forward.insert({setting[i][0], setting[i][1]});
        }

        // set up mapping
        for (int i = 0; i < 26; i++) {
            backward.insert({setting[i][1], setting[i][0]});
        }

        this->ringSwitch = ringSwitch;
    }

    void setRingOffset(char letter) {

        letter = std::toupper(letter);

        ringOffset = (int)letter - 65;
    }

    void turnRotor() {

        ringOffset += 1;
        ringOffset %= 26;
    }

    bool isAtNotch() {
        if (ringSwitch == ringOffset) {
            //turn over
            return true;
        }

        return false;
    }

    int getForward(int index) {
        return getMap(true, index);
    }

    int getBackward(int index) {
        return getMap(false, index);
    }

    std::string getName() {
        return rotorName;
    }

    char getRingOffset() {
        return char(ringOffset + 65);
    }

    void reset() {
        // reset rotor
        forward.clear();
        backward.clear();
        ringOffset = 0;
        ringSwitch = 0;
        rotorName = "";
    }
};

// hold combinations of rotor pairings
struct RotorCombo {
    std::vector<int> combo;
    float ic;
};

#endif