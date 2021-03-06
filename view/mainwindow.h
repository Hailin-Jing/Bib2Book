#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QString>
#include "workingarea.h"
#include "ui_workingarea.h"

//网络相关头文件
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
//JSON相关头文件
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

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

    QString currentVersion = "V1.0.1";  //当前版本号
    QNetworkAccessManager *manager;		//定义网络请求对象
    QNetworkReply *avatorReply;
    bool iniCheck = true;

public:
    MainWindow(QString open_file_path = "", QWidget *parent = nullptr);
    ~MainWindow();

    void parse_UpdateJSON(QString str, bool iniCheck = false);		//解析数据函数的声明

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

    void undateWindowMenu();
    void setActiveSubWindow(QWidget *window);

private slots:
    void on_actionAbout_triggered();
    void on_actionHelpDoc_triggered();
    void on_actionChinese_triggered();
    void on_actionEnglish_triggered();
    void on_actionMove_Up_triggered();
    void on_actionMove_Down_triggered();
    void on_actionRemove_triggered();
    void on_actionGenerate_TeX_Files_triggered();
    void on_actionCompile_triggered();
    void on_actionUpdate_triggered();

    void httpReadyRead();
    void httpDownloadProgress(qint64, qint64);
    void httpFinished();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
