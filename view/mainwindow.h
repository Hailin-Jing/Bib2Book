#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QString>
#include "workingarea.h"
#include "ui_workingarea.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QVector<WorkingArea*> WA;
    int sequenceNumber = 0;
    QVector<QAction*> actions;
    QSignalMapper *windowMapper;
    QTranslator *trans = nullptr;
    QTranslator *trans_qt_zh_cn = nullptr;

public:
    MainWindow(QString open_file_path = "", QWidget *parent = nullptr);
    ~MainWindow();

    Ui::MainWindow *UI();

    void addSequenceNumber(int addSequenceNumber);

    void dragEnterEvent(QDragEnterEvent *event);
    void dropEvent(QDropEvent *event);
    void closeEvent(QCloseEvent *event);

    void reboot();

protected slots:
    void on_actionNewProject_triggered();
    void on_actionOpenProject_triggered();
    void on_actionSaveAs_triggered();
    void on_actionSave_triggered();
    void on_actionRun_triggered();

    void undateWindowMenu();
    void setActiveSubWindow(QWidget *window);

private slots:
    void on_actionAbout_triggered();
    void on_actionDataFile_triggered();
    void on_actionParameters_triggered();
    void on_actionResult_triggered();
    void on_actionHelpDoc_triggered();
    void on_actionOutput_triggered();
    void on_actionOutputOther_triggered();
    void on_actionChinese_triggered();
    void on_actionEnglish_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
