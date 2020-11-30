//#include "fmod.hpp"

#include "playSound.h"

void qPlay(const char* mediaPath, FMOD::System *system, FMOD::Sound *sound) {
    
    FMOD::Channel *channel = 0;
    unsigned int version;
    void *extradriverdata = 0;

    system -> getVersion(&version);

    system -> init(32, FMOD_INIT_NORMAL, extradriverdata);

    system -> createStream(mediaPath, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);

    system -> playSound(sound, 0, false, &channel);

}

void qStop(FMOD::System *system, FMOD::Sound *sound) {

    sound -> release();
    system -> close();
    system -> release();

}




