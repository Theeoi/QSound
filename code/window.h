#ifndef qSound_WINDOW
#define qSound_WINDOW

#include <QMainWindow>
#include <QLabel>

class MainWindow : public QMainWindow { // QT Menu example
    Q_OBJECT

    public:
        MainWindow();

    protected:
        #ifndef QT_NO_CONTEXTMENU
            void contextMenuEvent(QContextMenuEvent *event) override;
        #endif
    
    private slots:
        void newShow();
        void openShow();
        void saveShow();
        void addTrack();
        void removeTrack();
        void about();

    private:
        void createActions();
        void createMenus();

        QMenu *fileMenu;
        QMenu *trackMenu;
        QMenu *helpMenu;
        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *exitAct;
        QAction *addAct;
        QAction *removeAct;
        QAction *aboutAct;
        QLabel *infoLabel;
};
#endif
