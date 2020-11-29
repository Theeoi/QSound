#include <iostream>
#include <unistd.h>

#include "fmod.hpp"

int main() {

    const char* MEDIAPATH = "../resources/mp3/rule_brittania.mp3";

    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::Channel *channel = 0;
    unsigned int version;
    void *extradriverdata = 0;

    FMOD_RESULT result = FMOD::System_Create(&system);
    result = system -> getVersion(&version);

    result = system -> init(32, FMOD_INIT_NORMAL, extradriverdata);

    result = system -> createStream(MEDIAPATH, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);

    result = system -> playSound(sound, 0, false, &channel);

    sleep(10);

    // QUITING
    result = sound -> release();
    result = system -> close();
    result = system -> release();

    return 0;
}
