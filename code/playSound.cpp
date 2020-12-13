//#include "fmod.hpp"
#include <iostream>
#include <unistd.h>

#include "playSound.h"

void qPlay(const char* mediaPath, int playTime) {

    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::System_Create(&system);
    FMOD::Channel *channel = 0;
    unsigned int version;
    void *extradriverdata = 0;

    system -> getVersion(&version);

    system -> init(32, FMOD_INIT_NORMAL, extradriverdata);

    system -> createStream(mediaPath, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);

    system -> playSound(sound, 0, false, &channel);

    std::cout << "Playing " << mediaPath << " for " << playTime << " seconds.\n";
    sleep(playTime);

    sound -> release();
    system -> close();
    system -> release();

}




