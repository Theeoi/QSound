#include <iostream>
#include <unistd.h>

//#include "fmod.hpp"

#include "playSound.h"

int main() {

    const char* MEDIAPATH = "../resources/mp3/rule_brittania.mp3";

    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::System_Create(&system);

    qPlay(MEDIAPATH, *system, *sound); 

    sleep(10);

    qStop(*system, *sound);

    return 0;
}
