#include <iostream>
#include <string>

#include "sound.h"

void soundPlay(const char* mediaPath, WINDOW* inputwin) {

    FMOD::System *system;
    FMOD::Sound *sound;
    FMOD::System_Create(&system);
    FMOD::Channel *channel = 0;
    unsigned int version;
    void *extradriverdata = 0;

    system -> getVersion(&version);

    system -> init(32, FMOD_INIT_NORMAL, extradriverdata);

    system -> createStream(mediaPath, FMOD_LOOP_NORMAL | FMOD_2D, 0, &sound);
    sound -> setMode(FMOD_LOOP_OFF);

    system -> playSound(sound, 0, false, &channel);

    // Get window parameters
    int winHeight, winWidth;
    getmaxyx(inputwin, winHeight, winWidth);

    // Playing!
    std::string playing("Playing: " + std::string(mediaPath));
    std::string stop("Press 's' to stop");  
    mvwprintw(inputwin, winHeight - 2, 1, playing.c_str());
    mvwprintw(inputwin, winHeight - 2, winWidth - stop.length() - 1, stop.c_str());

    while (int key_press = wgetch(inputwin)) { // While loop stops other button presses.
        
        if (key_press == 's') {
            sound -> release();
            system -> close();
            system -> release();
            
            return;
        }
        else
            continue;
    }
}




