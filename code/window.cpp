#include <QtWidgets>
#include <QFileDialog>
#include <QStringList>

#include "window.h"

MainWindow::MainWindow() {
    QWidget *widget = new QWidget;
    setCentralWidget(widget);

    QWidget *topFiller = new QWidget;
    topFiller -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //infoLabel = new QLabel(tr("<i>This is just a temporary label</i>"));

    //infoLabel -> setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    //infoLabel -> setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller -> setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> setContentsMargins(5, 5, 5, 5);
    layout -> addWidget(topFiller);
    //layout -> addWidget(view);
    layout -> addWidget(bottomFiller);
    widget -> setLayout(layout);

    createActions();
    createMenus();
    
    //QString message = tr("This is a message for the user!");
    //statusBar() -> showMessage(message);

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
    //infoLabel -> setText(tr("Invoked <b>File|New Show</b>"));
}

void MainWindow::openShow() {
    //infoLabel -> setText(tr("Invoked <b>File|Open Show</b>"));
}

void MainWindow::saveShow() {
    //infoLabel -> setText(tr("Invoked <b>File|Save Show</b>"));
}

// Taken from simpledommodel
void MainWindow::addTrack() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Track"), 
            trackPath, tr("WAV files (*.wav);;MP3 files (*.mp3)"));

    if (!filePath.isEmpty()) {
        trackPath = filePath;
    }
}
    
void MainWindow::removeTrack() {
    //infoLabel -> setText(tr("Invoked <b>Track|Remove Track</b>"));
}

void MainWindow::about() {
    //infoLabel -> setText(tr("Invoked <b>Help|About</b>"));
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

// Taken from simpletreemodel
TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent) : m_itemData(data), m_parentItem(parent) {}

TreeItem::~TreeItem() {
    qDeleteAll(m_childItems);
}

void TreeItem::appendChild(TreeItem *item) {
    m_childItems.append(item);
}

TreeItem *TreeItem::child(int row) {
    if (row < 0 || row >= m_childItems.size())
        return nullptr;
    return m_childItems.at(row);
}

int TreeItem::childCount() const {
    return m_childItems.count();
}

int TreeItem::columnCount() const {
    return m_itemData.count();
}

QVariant TreeItem::data(int column) const {
    if (column < 0 || column >= m_itemData.size())
        return QVariant();
    return m_itemData.at(column);
}

TreeItem *TreeItem::parentItem() {
    return m_parentItem;
}

int TreeItem::row() const {
    if (m_parentItem)
        return m_parentItem -> m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

TreeModel::TreeModel(const QString &data, QObject *parent) : QAbstractItemModel(parent) {
    rootItem = new TreeItem({tr("Track"), tr("Full Path")});
    setupModelData(data.split('\n'), rootItem);
}

TreeModel::~TreeModel() {
    delete rootItem;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem -> child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem -> parentItem();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem -> row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem -> childCount();    
}

int TreeModel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer()) -> columnCount();
    return rootItem -> columnCount();
}

QVariant TreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

   return item -> data(index.column()); 
}

Qt::ItemFlags TreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::NoItemFlags;

    return QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem -> data(section);

    return QVariant();
}

void TreeModel::setupModelData(const QStringList &lines, TreeItem *parent) {
    QVector<TreeItem*> parents;
    QVector<int> indentations;
    parents << parent;
    indentations << 0;

    int number = 0;

    while (number < lines.count()) {
        int position = 0;
        while (position < lines[number].length()) {
            if (lines[number].at(position) != ' ')
                break;
            position++;
        }

        const QString lineData = lines[number].mid(position).trimmed();

        if (!lineData.isEmpty()) {
            // Read the column data from the rest of the line.
            const QStringList columnStrings =
                lineData.split(QLatin1Char('\t'), Qt::SkipEmptyParts);
            QVector<QVariant> columnData;
            columnData.reserve(columnStrings.count());
            for (const QString &columnString : columnStrings)
                columnData << columnString;

            if (position > indentations.last()) {
                // The last child of the current parent is now the new parent
                // unless the current parent has no children.

                if (parents.last()->childCount() > 0) {
                    parents << parents.last()->child(parents.last()->childCount()-1);
                    indentations << position;
                }
            } else {
                while (position < indentations.last() && parents.count() > 0) {
                    parents.pop_back();
                    indentations.pop_back();
                }
            }

            // Append a new item to the current parent's list of children.
            parents.last()->appendChild(new TreeItem(columnData, parents.last()));
        }
        ++number;
    }
}











