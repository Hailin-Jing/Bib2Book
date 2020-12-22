#ifndef WORKINGAREA_H
#define WORKINGAREA_H

#include <QFileSystemModel>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QWidget>

#include "project.h"

namespace Ui {
class WorkingArea;
}

class WorkingArea : public QWidget
{
    Q_OBJECT

    QWidget *parent = nullptr;
    int ID;
    Project *PRO;

    bool Flag_IsNew = true;
    bool Flag_IsSaved = false;
    bool Flag_IsRan = false;
    QString Last_FileName;
    QString CurrentRootPath;

    QFileSystemModel *FileModel;
    QStandardItemModel *TableModel;
    QItemSelectionModel *SelectionModel;

public:
    explicit WorkingArea(QString filename, int ID, QWidget *parent = nullptr);
    ~WorkingArea();

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);

    void saveProject();

    void openDirectory();

    bool open(QString file_name);
    bool saveFile(QString file_name, QString text, bool project = false);
    bool save(QString file_name);
    bool saveTex(QString file_name);
    bool saveCoverTex(QString file_name);
    bool generate();
    bool compile();
    bool copyFiles();
    bool generateBatFiles();
    void refresh();

    //bool isOpen();
    bool isNew();
    bool isSaved();
    bool isRan();
    QString lastFileName();

    void setSavedState(bool Flag_IsSaved);
    Project *project();

    void moveUp();
    void moveDown();
    void remove();

    void addFile(QString);

    Ui::WorkingArea *UI();

private slots:
    void on_listWidget_currentRowChanged(int currentRow);
    void on_listView_doubleClicked(const QModelIndex &index);
    void on_title_textChanged();
    void on_author_textChanged();
    void on_ack_textChanged();
    void on_currentChanged(const QModelIndex &, const QModelIndex &);
    void on_itemChanged(QStandardItem *);
    void on_treeView_doubleClicked(const QModelIndex &index);

private:
    Ui::WorkingArea *ui;
};

#endif // WORKINGAREA_H
