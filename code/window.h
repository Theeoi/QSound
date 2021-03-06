#ifndef qSound_WINDOW
#define qSound_WINDOW

#include <QMainWindow>
#include <QVariant>
#include <QVector>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QTreeView>
#include <QVBoxLayout>

class MainWindow : public QMainWindow { // QT Menu example
    Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);

        QWidget *mainWidget; 
        QVBoxLayout *vboxLayout;
        QStatusBar *statusbar;
        QTreeView *trackTree;

        QMenu *trackMenu;
        QAction *addAct;
        QAction *removeAct;

    protected:
        #ifndef QT_NO_CONTEXTMENU
            void contextMenuEvent(QContextMenuEvent *event) override;
        #endif

    public slots:
        void updateActions();
    
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
        QMenu *helpMenu;
        QAction *newAct;
        QAction *openAct;
        QAction *saveAct;
        QAction *exitAct;
        QAction *aboutAct;

        QString trackPath;
};

// Taken from simpletreemodel
class TreeItem {
    public:
        explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = nullptr);
        ~TreeItem();

        void appendChild(TreeItem *child);

        TreeItem *child(int row);
        int childCount() const;
        int columnCount() const;
        QVariant data(int column) const;
        bool insertChildren(int position, int count, int columns);
        int childNumber() const;
        TreeItem *parent();
        bool removeChildren(int position, int count);
        bool setData(int column, const QVariant &value);

    private:
        QVector<TreeItem*> m_childItems;
        QVector<QVariant> m_itemData;
        TreeItem *m_parentItem;
};

class TreeModel : public QAbstractItemModel {
    Q_OBJECT

    public:
        explicit TreeModel(const QStringList &headers, const QString &data, QObject *parent = nullptr);
        ~TreeModel();

        QVariant data(const QModelIndex &index, int role) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
        QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
        QModelIndex parent(const QModelIndex &index) const override;
        int rowCount(const QModelIndex &parent = QModelIndex()) const override;
        int columnCount(const QModelIndex &parent = QModelIndex()) const override;

        Qt::ItemFlags flags(const QModelIndex &index) const override;
        bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
        bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
        bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

    private:
        void setupModelData(const QStringList &lines, TreeItem *parent);
        TreeItem *getItem(const QModelIndex &index) const;

        TreeItem *rootItem;
};

#endif
