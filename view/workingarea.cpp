#include "workingarea.h"
#include "ui_workingarea.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

WorkingArea::WorkingArea(QString filename, int ID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkingArea)
{
    ui->setupUi(this);
    this->parent = parent;
    setAttribute(Qt::WA_DeleteOnClose);
    PRO = new Project();

    this->ID = ID;
    Last_FileName = filename;
    setWindowTitle(Last_FileName);

    ui->listWidget->setCurrentRow(0);

    MainWindow *window = qobject_cast<MainWindow*>(parent);
    if (window != nullptr) {
        window->addSequenceNumber(1);
        window->UI()->actionSave->setEnabled(true);
        window->UI()->actionSaveAs->setEnabled(true);
        window->UI()->actionRun->setEnabled(true);
        window->UI()->actionDataFile->setEnabled(true);
        window->UI()->actionParameters->setEnabled(true);
        window->UI()->actionResult->setEnabled(true);
        window->UI()->actionOutput->setEnabled(true);
        window->UI()->actionOutputOther->setEnabled(true);
    }
}

WorkingArea::~WorkingArea()
{
    MainWindow *window = qobject_cast<MainWindow*>(parent);
    if (window != nullptr)
        window->addSequenceNumber(-1);
    if (!Flag_IsSaved)
        saveProject();
    delete ui;
}

bool WorkingArea::open(QString file_name)
{
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("Error"),tr("Open File Failed"));
        return false;
    }
    else
    {
        if(!file.isReadable()) {
            QMessageBox::warning(this,tr("Error"),tr("File Unreadable"));
            return false;
        }
        else
        {
            QTextStream textStream(&file);
            while(!textStream.atEnd())
                PRO->readString(textStream.readAll());
            file.close();
            Flag_IsNew = false;
            Flag_IsSaved = true;
            Last_FileName = file_name;
            return true;
        }
    }
}

bool WorkingArea::save(QString file_name)
{
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("Error"),tr("Open File Failed"),QMessageBox::Ok);
        return false;
    }
    else
    {
        QTextStream textStream(&file);
        QString str = PRO->fileText();
        textStream << str;
        file.close();
        Flag_IsNew = false;
        Flag_IsSaved = true;
        Last_FileName = file_name;
        setWindowTitle(Last_FileName);
        return true;
    }
}

bool WorkingArea::run()
{
    Flag_IsRan = true;
    return true;
}

void WorkingArea::refresh()
{
}

bool WorkingArea::saveOutput(QString file_name)
{

}

bool WorkingArea::isNew()
{
    return Flag_IsNew;
}

bool WorkingArea::isSaved()
{
    return Flag_IsSaved;
}

bool WorkingArea::isRan()
{
    return Flag_IsRan;
}

QString WorkingArea::lastFileName()
{
    return Last_FileName;
}

void WorkingArea::setSavedState(bool Flag_IsSaved)
{
    this->Flag_IsSaved = Flag_IsSaved;
}


Project *WorkingArea::project()
{
    return PRO;
}

Ui::WorkingArea *WorkingArea::UI()
{
    return ui;
}

void WorkingArea::saveProject()
{
    QApplication::beep();
    QMessageBox::StandardButton button =
            QMessageBox::question(this,tr("Info"),tr("File %1 Has Not Been Saved, Whether To Save The File?").arg(Last_FileName),
                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if (button == QMessageBox::Yes) {
        if(!Flag_IsNew)
            save(Last_FileName);
        else {
            QFileDialog fileDialog;
            QString filename = fileDialog.getSaveFileName(this,tr("Save File"),Last_FileName,tr("GRS Project File(*.grs)"));
            if(filename.simplified().isEmpty())
                return;
            save(filename);
        }
        QMainWindow *window = qobject_cast<QMainWindow*>(parent);
        window->statusBar()->showMessage(tr("File %1 Saved Successfully").arg(Last_FileName), 2000);
    }
}

void WorkingArea::on_listWidget_currentRowChanged(int currentRow)
{
    switch (currentRow) { }
}
