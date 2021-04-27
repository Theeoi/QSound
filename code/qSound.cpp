#include <QApplication>

#include "sound.h"
#include "window.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    //const char* MEDIAPATH = "resources/wav/wilhelm-scream.wav";

<<<<<<< HEAD
    WINDOW* mainwin = newwin(winHeight, winWidth, (LINES - winHeight)/2, (COLS - winWidth)/2);
    box(mainwin, 0, 0);
    refresh();
    wrefresh(mainwin); 
   
    const char* MEDIAPATH = "resources/wav/wilhelm-scream.wav";
=======
    //soundPlay(MEDIAPATH); 
>>>>>>> tryQt

    return app.exec();
}
