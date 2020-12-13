#include <iostream>

//#include "fmod.hpp"

#include "playSound.h"

int main() {

    const char* MEDIAPATH = "../resources/mp3/rule_brittania.mp3";
    int playTime = 10; // Seconds of play

    qPlay(MEDIAPATH, playTime); 

    return 0;
}
