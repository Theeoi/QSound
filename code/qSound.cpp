#include <QApplication>

#include "sound.h"
#include "window.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    //const char* MEDIAPATH = "resources/wav/wilhelm-scream.wav";

    //soundPlay(MEDIAPATH); 

    return app.exec();
}
