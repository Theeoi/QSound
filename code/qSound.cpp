#include <QApplication>
#include <QFile>
#include <QTreeView>

#include "sound.h"
#include "window.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    MainWindow window;
    window.show();

    QFile file("./saves/default.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel model(file.readAll());
    file.close();

    QTreeView view;
    view.setModel(&model);
    view.show();

    //const char* MEDIAPATH = "resources/wav/wilhelm-scream.wav";

    //soundPlay(MEDIAPATH); 

    return app.exec();
}
