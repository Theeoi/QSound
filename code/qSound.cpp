#include <iostream>

#include "sound.h"

int main() {

    // Initialize ncurses (window) 
    initscr();
    cbreak();
    noecho();

    // Creating main window!
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int winHeight, winWidth;
    winHeight = yMax;
    winWidth = xMax - 2;

    WINDOW* mainwin = newwin(winHeight, winWidth, (LINES - winHeight)/2, (COLS - winWidth)/2);
    box(mainwin, 0, 0);
    refresh();
    wrefresh(mainwin); 
   
    const char* MEDIAPATH = "resources/mp3/rule-brittania.mp3";

    soundPlay(MEDIAPATH, mainwin); 

    // Deallocate main window
    wborder(mainwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(mainwin);
    delwin(mainwin);

    endwin(); // End ncurses

    return 0;
}
