//#include "fmod.hpp"
#include <iostream>
#include <string>
#include <unistd.h>
#include <curses.h>

#include "playSound.h"

void qPlay(const char* mediaPath) {

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

    // Initialize ncurses (user input) 
    initscr();
    cbreak();
    noecho();

    // Creating window!
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW* inputwin = newwin(3, xMax-12, yMax-5, 5);
    box(inputwin, 0, 0);
    refresh();
    wrefresh(inputwin); 
   
    // Playing!
    std::string playing("Playing: " + std::string(mediaPath));  
    mvwprintw(inputwin, 1, 1, playing.c_str());
    mvwprintw(inputwin, 1, 95, "Press 's' to stop.");
    while (1) { // While loop stops other button presses.
        int key_press = wgetch(inputwin);
        if (key_press == 's') {
            sound -> release();
            system -> close();
            system -> release();

            getch();
            endwin();

            return;
        }
        else
            continue;
    }
}




