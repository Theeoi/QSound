#ifndef qSound_WINDOW
#define qSound_WINDOW

#include <QMainWindow>
#include <QLabel>
#include <QVariant>
#include <QVector>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QTreeView>

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

        QTreeView *trackTree;
        QString trackPath;
};

// Taken from simpletreemodel
class TreeItem {
    public:
        explicit TreeItem(const QVector<QVariant> &data, TreeItem *parentItem = nullptr);
        ~TreeItem();

        void appendChild(TreeItem *child);

        TreeItem *child(int row);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        int row() const;
        TreeItem *parentItem();

    private:
        QVector<TreeItem*> m_childItems;
        QVector<QVariant> m_itemData;
        TreeItem *m_parentItem;
};

class TreeModel : public QAbstractItemModel {
    Q_OBJECT

    public:
        explicit TreeModel(const QString &data, QObject *parent = nullptr);
        ~TreeModel();

        QVariant data(const QModelIndex &index, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    private:
        void setupModelData(const QStringList &lines, TreeItem *parent);

        TreeItem *rootItem;
};

#endif
