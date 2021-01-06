#include <QtWidgets>

#include "window.h"

MainWindow::MainWindow() {
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    infoLabel = new QLabel(tr("<i>This is just a temporary label</i>"));

    infoLabel -> setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel -> setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> setContentsMargins(5, 5, 5, 5);
    layout -> addWidget(topFiller);
    layout -> addWidget(infoLabel);
    layout -> addWidget(bottomFiller);
    widget -> setLayout(layout);

    createActions();
    createMenus();

    QString message = tr("This is a message for the user!");
    statusBar() -> showMessage(message);

    setWindowTitle(tr("qSound"));
    setMinimumSize(250, 190);
    resize(500, 380);
}

#ifndef QT_NO_CONTEXTMENU
void MainWindow::contextMenuEvent(QContextMenuEvent *event) {
    QMenu menu(this);
    menu.addAction(newAct);
    menu.addAction(removeAct);
    menu.exec(event -> globalPos());
}
#endif

void MainWindow::newShow() {
    infoLabel -> setText(tr("Invoked <b>File|New Show</b>"));
}

void MainWindow::openShow() {
    infoLabel -> setText(tr("Invoked <b>File|Open Show</b>"));
}

void MainWindow::saveShow() {
    infoLabel -> setText(tr("Invoked <b>File|Save Show</b>"));
}

void MainWindow::addTrack() {
    infoLabel -> setText(tr("Invoked <b>Track|Add Track</b>"));
}

void MainWindow::removeTrack() {
    infoLabel -> setText(tr("Invoked <b>Track|Remove Track</b>"));
}

void MainWindow::about() {
    infoLabel -> setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About qSound"), 
            tr("A sound player for theater productions. Created by: Theodor Blom"));
}

void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct -> setShortcuts(QKeySequence::New);
    newAct -> setStatusTip(tr("Create a new show.."));
    connect(newAct, &QAction::triggered, this, &MainWindow::newShow);
    
    openAct = new QAction(tr("&Open.."), this);
    openAct -> setShortcuts(QKeySequence::Open);
    openAct -> setStatusTip(tr("Open an existing show.."));
    connect(openAct, &QAction::triggered, this, &MainWindow::openShow);

    saveAct = new QAction(tr("&Save"), this);
    saveAct -> setShortcuts(QKeySequence::Save);
    saveAct -> setStatusTip(tr("Save current show.."));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveShow);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct -> setShortcuts(QKeySequence::Quit);
    exitAct -> setStatusTip(tr("Close qSound"));
    connect(exitAct, &QAction::triggered, this, &QWidget::close);

    addAct = new QAction(tr("&Add"), this);
    addAct -> setShortcuts(QKeySequence::AddTab);
    addAct -> setStatusTip(tr("Add track.."));
    connect(addAct, &QAction::triggered, this, &MainWindow::addTrack);

    removeAct = new QAction(tr("&Remove"), this);
    //removeAct -> setShortcuts(QKeySequence::??);
    removeAct -> setStatusTip(tr("Remove track.."));
    connect(removeAct, &QAction::triggered, this, &MainWindow::removeTrack);

    aboutAct = new QAction(tr("&About"), this);
    //aboutAct -> setShortcuts(QKeySequence::??);
    aboutAct -> setStatusTip(tr("About qSound"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::createMenus() {
    fileMenu = menuBar() -> addMenu(tr("&File"));
    fileMenu -> addAction(newAct);
    fileMenu -> addAction(openAct);
    fileMenu -> addAction(saveAct);
    fileMenu -> addSeparator();
    fileMenu -> addAction(exitAct);

    trackMenu = menuBar() -> addMenu(tr("&Track"));
    trackMenu -> addAction(addAct);
    trackMenu -> addAction(removeAct);

    helpMenu = menuBar() -> addMenu(tr("&Help"));
    helpMenu -> addAction(aboutAct);
}







