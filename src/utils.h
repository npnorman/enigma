#ifndef UTILS_H
#define UTILS_H

#include <map>

// Utils
// Stores information about the rotors, including settings, ring switches, and more

// rotor settings
// https://en.wikipedia.org/wiki/Enigma_rotor_details

//1930 Enigma I
const int Enigma_I_I[26][2] = {{0,20},{1,22},{2,24},{3,6},{4,0},{5,3},{6,5},{7,15},{8,21},{9,25},{10,1},{11,4},{12,2},{13,10},{14,12},{15,19},{16,7},{17,23},{18,18},{19,11},{20,17},{21,8},{22,13},{23,16},{24,14},{25,9},};
const int Enigma_I_II[26][2] = {{0,0},{1,9},{2,15},{3,2},{4,25},{5,22},{6,17},{7,11},{8,5},{9,1},{10,3},{11,10},{12,14},{13,19},{14,24},{15,20},{16,16},{17,6},{18,4},{19,13},{20,7},{21,23},{22,12},{23,8},{24,21},{25,18},};
const int Enigma_I_III[26][2] = {{0,19},{1,0},{2,6},{3,1},{4,15},{5,2},{6,18},{7,3},{8,16},{9,4},{10,20},{11,5},{12,21},{13,13},{14,25},{15,7},{16,24},{17,8},{18,23},{19,9},{20,22},{21,11},{22,17},{23,10},{24,14},{25,12},};
const int Enigma_I_IV[26][2] = {{0,7},{1,25},{2,22},{3,21},{4,0},{5,17},{6,19},{7,13},{8,11},{9,6},{10,20},{11,15},{12,23},{13,16},{14,2},{15,4},{16,9},{17,12},{18,1},{19,18},{20,10},{21,3},{22,24},{23,14},{24,8},{25,5},};
const int Enigma_I_V[26][2] = {{0,16},{1,2},{2,24},{3,11},{4,23},{5,22},{6,4},{7,13},{8,5},{9,19},{10,25},{11,14},{12,18},{13,12},{14,21},{15,9},{16,20},{17,3},{18,10},{19,6},{20,8},{21,0},{22,17},{23,15},{24,7},{25,1},};
const int Enigma_I_UKW_B[26][2] = {{0,24},{1,17},{2,20},{3,7},{4,16},{5,18},{6,11},{7,3},{8,15},{9,23},{10,13},{11,6},{12,14},{13,10},{14,12},{15,8},{16,4},{17,1},{18,5},{19,25},{20,2},{21,22},{22,21},{23,9},{24,0},{25,19},};

// rotor class
class Rotor {
 private:
    std::map<int, int> forward;
    std::map<int, int> backward;
    int ringOffset;
    int ringSwitch; //turnover

 public:
    Rotor(int setting[26][2], int ringSwitch, int ringOffset = 0) {

        // set up mapping
        for (int i = 0; i < 26; i++) {
            forward.insert({setting[i][0], setting[i][1]});
        }

        this->ringSwitch = ringSwitch;
        this->ringOffset = ringOffset;
    }

    bool turnRotor() {
        ringOffset += 1;
        ringOffset %= 26;

        if (ringSwitch - ringOffset == 0) {
            //turn over
            return true;
        }

        return false;
    }

    int getForward(int index) {
        index += ringOffset;
        index %= 26;

        return forward[index];
    }

    int getBackward(int index) {
        index += ringOffset;
        index %= 26;

        return backward[index];
    }

};

#endif