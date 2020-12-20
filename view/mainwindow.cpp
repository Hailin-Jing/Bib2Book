#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "constraints.h"

#include <QDropEvent>
#include <QDragEnterEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QSignalMapper>
#include <QTextStream>
#include <QTranslator>
#include <QMimeData>
#include <QMdiSubWindow>
#include <QProcess>
#include <QDesktopServices>

MainWindow::MainWindow(QString open_file_path, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setAcceptDrops(true);
    this->setAttribute(Qt::WA_DeleteOnClose);

    setGlobalFont(QCoreApplication::applicationDirPath() + "/fonts/cormorant-garamond/CormorantGaramond-Regular.ttf", this);

    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(setActiveSubWindow(QWidget*)));
    connect(ui->menu_window, SIGNAL(aboutToShow()), this, SLOT(undateWindowMenu()));

    if (!open_file_path.isEmpty()) {
        WorkingArea *area = new WorkingArea(open_file_path, sequenceNumber, nullptr);
        WA.append(area);
        ui->mdiArea->addSubWindow(area);
        area->show();
        area->open(open_file_path);
    }
    trans = new QTranslator();
    trans_qt_zh_cn = new QTranslator();
    trans_qt_zh_cn->load(QApplication::applicationDirPath() + "/translations/qt_zh_TW.qm");
    int currentLanguage = currentLanguageSetting();
    switch (currentLanguage) {
    case language::English:
        trans->load(QApplication::applicationDirPath() + "/translations/Bib2Book_en.qm");
        qApp->installTranslator(trans);
        ui->actionEnglish->setChecked(true);
        ui->actionChinese->setChecked(false);
        break;
    case language::Chinese:
        trans->load(QApplication::applicationDirPath() + "/translations/Bib2Book_cn.qm");
        qApp->installTranslator(trans);
        qApp->installTranslator(trans_qt_zh_cn);
        ui->actionChinese->setChecked(true);
        ui->actionEnglish->setChecked(false);
        break;
    default:
        trans->load(QApplication::applicationDirPath() + "/translations/Bib2Book_en.qm");
        qApp->installTranslator(trans);
        ui->actionChinese->setChecked(false);
        ui->actionEnglish->setChecked(true);
        break;
    }
    ui->retranslateUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow *MainWindow::UI()
{
    return ui;
}

void MainWindow::addSequenceNumber(int addSequenceNumber)
{
    this->sequenceNumber += addSequenceNumber;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;
    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        if (!file_name.endsWith(".b2b"))
            continue;
        WorkingArea *area = new WorkingArea(file_name,sequenceNumber,this);
        WA.append(area);
        ui->mdiArea->addSubWindow(area);
        area->show();
        area->open(file_name);
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    QList<QMdiSubWindow*> windows = ui->mdiArea->subWindowList();
    foreach(QMdiSubWindow *window, windows)
        delete window;
}

void MainWindow::reboot()
{
    QString program = QApplication::applicationFilePath();
    QStringList arguments = QApplication::arguments();
    QString workingDirectory = QDir::currentPath();
    QProcess::startDetached(program, arguments, workingDirectory);
    QApplication::exit();
}

void MainWindow::undateWindowMenu()
{
    QList<QMdiSubWindow*> windows = ui->mdiArea->subWindowList();
    foreach(QAction *action, actions)
        ui->menu_window->removeAction(action);
    QVector<QAction*> vector;
    actions.swap(vector);
    ui->menu_window->addSeparator();
    QMdiSubWindow *actionWindow = ui->mdiArea->activeSubWindow();
    int i = 0;
    foreach(QMdiSubWindow* window, windows) {
        WorkingArea *area = qobject_cast<WorkingArea*>(window->widget());
        QAction *action =  new QAction(QString::number(++i) + " " + area->lastFileName());
        action->setFont(QFont("Courier New", 11));
        actions.append(action);
        ui->menu_window->addAction(action);
        action->setCheckable(true);
        action->setChecked(window == actionWindow);
        connect(action, SIGNAL(triggered()), windowMapper, SLOT(map()));
        windowMapper->setMapping(action, window);
    }
}

void MainWindow::setActiveSubWindow(QWidget *window)
{
    if (!window)
        return;
    ui->mdiArea->setActiveSubWindow(qobject_cast<QMdiSubWindow *>(window));
}

void MainWindow::on_actionNewProject_triggered()
{
    WorkingArea *area = new WorkingArea(tr("File-%1.b2b").arg(QString::number(sequenceNumber+1)), sequenceNumber, this);
    WA.append(area);
    ui->mdiArea->addSubWindow(area);
    area->show();
}

void MainWindow::on_actionOpenProject_triggered()
{
    QString file_name;
    file_name = QFileDialog::getOpenFileName(this,tr("Open file"),QApplication::applicationDirPath(),tr("Bib2Book Project File (*.b2b)"));
    if(file_name.simplified().isEmpty())
        return;
    else {
        WorkingArea *area = new WorkingArea(file_name, sequenceNumber, this);
        WA.append(area);
        ui->mdiArea->addSubWindow(area);
        area->show();
        area->open(file_name);
    }
}

void MainWindow::on_actionSave_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    if (area != nullptr) {
        if(area->isNew())
            on_actionSaveAs_triggered();
        else {
            if (area->save(area->lastFileName()))
                statusBar()->showMessage(tr("File %1 saved successfully").arg(area->lastFileName()), 4000);
            else
                statusBar()->showMessage(tr("File %1 saved failed").arg(area->lastFileName()), 4000);
        }
    }
    else
        statusBar()->showMessage(tr("File was not opened or created"), 4000);
}

void MainWindow::on_actionSaveAs_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    if (area != nullptr) {
        QFileDialog fileDialog;
        QString filename = fileDialog.getSaveFileName(this,tr("Save file"),area->lastFileName(),tr("Bib2Book Project File(*.b2b)"));
        if(filename.simplified().isEmpty())
            return;
        if (area->save(filename))
            statusBar()->showMessage(tr("File %1 saved successfully").arg(area->lastFileName()), 4000);
        else
            statusBar()->showMessage(tr("File %1 saved failed").arg(area->lastFileName()), 4000);
    }
    else
        statusBar()->showMessage(tr("File was not opened or created"), 4000);
}

void MainWindow::on_actionRun_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    if (area != nullptr) {
        if (area->run())
            statusBar()->showMessage(tr("Calculate complete"), 4000);
        else
            statusBar()->showMessage(tr("File was not opened or created"), 4000);
    }
    else
        statusBar()->showMessage(tr("File was not opened or created"), 4000);
}

void MainWindow::on_actionHelpDoc_triggered()
{
    QString filename = QApplication::applicationDirPath() + "/documentation/doc.pdf";
    bool is_Open = QDesktopServices::openUrl(QUrl::fromLocalFile(filename));
    if (!is_Open)
        QMessageBox::critical(this,tr("Error"),tr("Documentation ppen failed, the path is: ") + filename);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, tr("About"), tr("This is a program that converts biblipgraphies to a book"));
}

void MainWindow::on_actionDataFile_triggered()
{
    WorkingArea *area = nullptr;
    if (ui->mdiArea->activeSubWindow()) {
        area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
        area->UI()->listWidget->setCurrentRow(0);
    }
}


void MainWindow::on_actionChinese_triggered()
{
    ui->actionChinese->setChecked(!ui->actionEnglish->isChecked());
    int currentLanguage = currentLanguageSetting();
    if (currentLanguage == language::Chinese)
        return;
    QApplication::beep();
    QMessageBox::StandardButton button =
            QMessageBox::question(this,tr("Info"),tr("Program needs to rebot to save settings, otherwise there will be some problems, reboot?"), QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if (button == QMessageBox::Yes) {
        ui->actionChinese->setChecked(true);
        ui->actionEnglish->setChecked(false);
        closeEvent(new QCloseEvent());

        qApp->removeTranslator(trans);
        qApp->removeTranslator(trans_qt_zh_cn);

        trans=new QTranslator();
        trans_qt_zh_cn = new QTranslator();
        trans->load(QApplication::applicationDirPath() + "/translations/Bib2Book_cn.qm");
        qApp->installTranslator(trans);
        qApp->installTranslator(trans_qt_zh_cn);
        ui->retranslateUi(this);

        QSettings settings("WWB-Qt","Bib2Book");
        settings.setValue("Language",language::Chinese);
        reboot();
    }
}

void MainWindow::on_actionEnglish_triggered()
{
    ui->actionEnglish->setChecked(!ui->actionChinese->isChecked());
    int currentLanguage = currentLanguageSetting();
    if (currentLanguage == language::English)
        return;
    QApplication::beep();
    QMessageBox::StandardButton button =
            QMessageBox::question(this,tr("Info"),tr("Program needs to rebot to save settings, otherwise there will be some problems, reboot?"), QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if (button == QMessageBox::Yes) {
        ui->actionEnglish->setChecked(true);
        ui->actionChinese->setChecked(false);
        closeEvent(new QCloseEvent());

        qApp->removeTranslator(trans);
        qApp->removeTranslator(trans_qt_zh_cn);

        trans=new QTranslator();
        trans->load(QApplication::applicationDirPath() + "/translations/Bib2Book_en.qm");
        qApp->installTranslator(trans);
        ui->retranslateUi(this);

        QSettings settings("WWB-Qt","Bib2Book");
        settings.setValue("Language",language::English);
        reboot();
    }
}
