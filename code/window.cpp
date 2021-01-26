#include <QtWidgets>
#include <QFileDialog>
#include <QStringList>

#include "window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    mainWidget = new QWidget(this);

    vboxLayout = new QVBoxLayout(mainWidget);
    vboxLayout -> setSpacing(0);
    vboxLayout -> setContentsMargins(0, 0, 0, 0);

    trackTree = new QTreeView(mainWidget);
    trackTree -> setAlternatingRowColors(true);
    trackTree -> setSelectionBehavior(QAbstractItemView::SelectRows);
    trackTree -> setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
    trackTree -> setAnimated(false);
    trackTree -> setAllColumnsShowFocus(true);

    vboxLayout -> addWidget(trackTree);
    setCentralWidget(mainWidget);

    createActions();
    createMenus();
    
    setWindowTitle(tr("qSound"));
    setMinimumSize(250, 190);
    resize(500, 380);

    const QStringList headers({tr("Track No."), tr("Name"), tr("Full Path")});

    QFile file("./saves/test.txt");
    file.open(QIODevice::ReadOnly);
    TreeModel *model = new TreeModel(headers, file.readAll());
    file.close();

    trackTree -> setModel(model);
    for (int column = 0; column < model -> columnCount(); ++column)
        trackTree -> resizeColumnToContents(column);

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

}

void MainWindow::openShow() {

}

void MainWindow::saveShow() {

}

// Taken from simpledommodel
void MainWindow::addTrack() {
    QString filePath = QFileDialog::getOpenFileName(this, tr("Select Track"), 
            trackPath, tr("WAV files (*.wav);;MP3 files (*.mp3)"));

    if (!filePath.isEmpty()) {
        trackPath = filePath;
    }

    const QModelIndex index = trackTree -> selectionModel() -> currentIndex();
    QAbstractItemModel *model = trackTree -> model();

    if (!model -> insertRow(index.row() + 1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model -> columnCount(index.parent()); ++column) {
        const QModelIndex child = model -> index(index.row() + 1, column, index.parent());
        model -> setData(child, QVariant(tr("[No Data]")), Qt::EditRole);
    }
}
    
void MainWindow::removeTrack() {

}

void MainWindow::about() {
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

void MainWindow::updateActions() {
    const bool hasSelection = !trackTree -> selectionModel() -> selection().isEmpty();
    removeAct -> setEnabled(hasSelection);

    const bool hasCurrent = trackTree -> selectionModel() -> currentIndex().isValid();
    addAct -> setEnabled(hasCurrent);
}

// ------ TreeItem Class --------

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

bool TreeItem::insertChildren(int position, int count, int columns) {
    if (position < 0 || position > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row) {
        QVector<QVariant> data(columns);
        TreeItem *item = new TreeItem(data, this);
        m_childItems.insert(position, item);
    }

    return true;
}

TreeItem *TreeItem::parent() {
    return m_parentItem;
}

int TreeItem::row() const {
    if (m_parentItem)
        return m_parentItem -> m_childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}

bool TreeItem::removeChildren(int position, int count) {
    if (position < 0 || position + count > m_childItems.size())
        return false;

    for (int row = 0; row < count; ++row)
        delete m_childItems.takeAt(position);

    return true;
}

bool TreeItem::setData(int column, const QVariant &value) {
    if (column < 0 || column >= m_itemData.size())
       return false;

    m_itemData[column] = value;
    return true;
}

// ----- TreeModel Class ------

TreeModel::TreeModel(const QStringList &headers, const QString &data, QObject *parent) : QAbstractItemModel(parent) {
    QVector<QVariant> rootData;
    for (const QString &header : headers)
        rootData << header;
    
    rootItem = new TreeItem(rootData);
    setupModelData(data.split('\n'), rootItem);
}

TreeModel::~TreeModel() {
    delete rootItem;
}

TreeItem *TreeModel::getItem(const QModelIndex &index) const {
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) 
            return item;
    }
    return rootItem;
}

QModelIndex TreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (!parent.isValid() && parent.column() != 0)
        return QModelIndex();

    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return QModelIndex();

    TreeItem *childItem = parentItem -> child(row);
    if (childItem)
        return createIndex(row, column, childItem);

    return QModelIndex();
}

QModelIndex TreeModel::parent(const QModelIndex &index) const {
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = getItem(index);
    TreeItem *parentItem = childItem ? childItem -> parent() : nullptr;

    if (parentItem == rootItem || !parentItem)
        return QModelIndex();

    return createIndex(parentItem -> row(), 0, parentItem);
}

int TreeModel::rowCount(const QModelIndex &parent) const {
    const TreeItem *parentItem = getItem(parent);

    return parentItem ? parentItem -> childCount() : 0;
}

int TreeModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

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

    return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
}

QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem -> data(section);

    return QVariant();
}

bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item -> setData(index.column(), value);

    if (result)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

    return result;    
}

bool TreeModel::insertRows(int position, int rows, const QModelIndex &parent) {
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginInsertRows(parent, position, position + rows - 1);
    const bool success = parentItem -> insertChildren(position, rows, rootItem -> columnCount());
    endInsertRows();

    return success;
}

bool TreeModel::removeRows(int position, int rows, const QModelIndex &parent) {
    TreeItem *parentItem = getItem(parent);
    if (!parentItem)
        return false;

    beginRemoveRows(parent, position, position + rows - 1);
    const bool success = parentItem -> removeChildren(position, rows);
    endRemoveRows();

    return success;
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











