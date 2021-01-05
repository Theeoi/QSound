#include <iostream>
#include <string>

#include "sound.h"

void soundPlay(const char* mediaPath) {

    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::System_Create(&system);
    FMOD::Channel *channel = 0;
    unsigned int version;
    void *extradriverdata = 0;

    system -> getVersion(&version);

    system -> init(32, FMOD_INIT_NORMAL, extradriverdata);

    system -> createStream(mediaPath, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
    sound -> setMode(FMOD_LOOP_OFF); // ONLY PLAY ONCE

    system -> playSound(sound, 0, false, &channel);

    std::string playing("Playing: " + std::string(mediaPath));
    std::cout << playing << std::endl;

    sound -> release();
    system -> close();
    system -> release(); 

}




