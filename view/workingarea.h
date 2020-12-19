#ifndef WORKINGAREA_H
#define WORKINGAREA_H

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


public:
    explicit WorkingArea(QString filename, int ID, QWidget *parent = nullptr);
    ~WorkingArea();

    void saveProject();

    bool open(QString file_name);
    bool save(QString file_name);
    bool run();
    void refresh();

    bool saveOutput(QString file_name);

    //bool isOpen();
    bool isNew();
    bool isSaved();
    bool isRan();
    QString lastFileName();

    void setSavedState(bool Flag_IsSaved);

    Project *project();

    Ui::WorkingArea *UI();

private slots:
    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::WorkingArea *ui;
};

#endif // WORKINGAREA_H
