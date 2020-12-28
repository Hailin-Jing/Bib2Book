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
    setGlobalFont(QCoreApplication::applicationDirPath() + "/fonts/cormorant-garamond/CormorantGaramond-Regular.ttf", ui->menu_file);

    windowMapper = new QSignalMapper(this);
    connect(windowMapper, SIGNAL(mapped(QWidget*)),this, SLOT(setActiveSubWindow(QWidget*)));
    connect(ui->menu_window, SIGNAL(aboutToShow()), this, SLOT(undateWindowMenu()));

    if (!open_file_path.isEmpty()) {
        WorkingArea *area = new WorkingArea(open_file_path, sequenceNumber, this);
        WA.append(area);
        ui->mdiArea->addSubWindow(area);
        area->show();
        area->showMaximized();
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

    manager = new QNetworkAccessManager(this);          //新建QNetworkAccessManager对象
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));//关联信号和槽

    ui->retranslateUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::parse_UpdateJSON(QString str)
{
    //    QMessageBox msgBox;
    QJsonParseError err_rpt;
    QJsonDocument  root_Doc = QJsonDocument::fromJson(str.toUtf8(),&err_rpt);//字符串格式化为JSON
    if(err_rpt.error != QJsonParseError::NoError)
    {
        //        qDebug() << "root格式错误";
        QMessageBox::critical(this, "检查失败", "服务器地址错误或JSON格式错误!");
        return -1;
    }
    if(root_Doc.isObject())
    {
        QJsonObject  root_Obj = root_Doc.object();   //创建JSON对象，不是字符串
        QJsonObject PulseValue = root_Obj.value("PulseSensor").toObject();
        QString Verison = PulseValue.value("LatestVerison").toString();  //V1.0
        QString Url = PulseValue.value("Url").toString();        //https://wcc-blog.oss-cn-beijing.aliyuncs.com/QtUpdate/uFun_Pulse_v1.0.exe
        QString UpdateTime = PulseValue.value("UpdateTime").toString();
        QString ReleaseNote = PulseValue.value("ReleaseNote").toString();
        if(Verison > currentVersion)
        {
            QString warningStr =  "检测到新版本!\n版本号：" + Verison + "\n" + "更新时间：" + UpdateTime + "\n" + "更新说明：" + ReleaseNote;
            int ret = QMessageBox::warning(this, "检查更新",  warningStr, "去下载", "不更新");
            if(ret == 0)    //点击更新
                QDesktopServices::openUrl(QUrl(Url));
        }
        else
            QMessageBox::information(this, "检查更新", "当前已经是最新版本!");
    }
    return 0;
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
        area->showMaximized();
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
    area->showMaximized();
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
        area->showMaximized();
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

void MainWindow::on_actionMove_Up_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    if (area != nullptr) {
        area->moveUp();
    }
    else
        statusBar()->showMessage(tr("No window is selected!"), 4000);
}

void MainWindow::on_actionMove_Down_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    if (area != nullptr) {
        area->moveDown();
    }
    else
        statusBar()->showMessage(tr("No window is selected!"), 4000);
}

void MainWindow::on_actionRemove_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    if (area != nullptr) {
        area->remove();
    }
    else
        statusBar()->showMessage(tr("No window is selected!"), 4000);
}

void MainWindow::on_actionGenerate_TeX_Files_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    on_actionSave_triggered();
    if (area != nullptr) {
        if (area->generate()) {
            statusBar()->showMessage(tr("TeX file generated!"), 4000);
            // area->openDirectory();
        }
        else
            statusBar()->showMessage(tr("File generated with errors!"), 4000);
    }
    else
        statusBar()->showMessage(tr("No window is selected!"), 4000);
}

void MainWindow::on_actionCompile_triggered()
{
    WorkingArea *area = qobject_cast<WorkingArea *>(ui->mdiArea->activeSubWindow()->widget());
    if (!area->isRan()) {
        QMessageBox::critical(this, tr("Error"), tr("File does not generate, please generate files!"));
        return;
    }
    if (area->isGeneratedError()) {
        QMessageBox::critical(this, tr("Error"), tr("File generated with error, please re-generated!"));
        return;
    }
    if (area != nullptr) {
        if (area->compile()) {
            statusBar()->showMessage(tr("TeX file generated!"), 4000);
            QMessageBox::information(this, tr("Successfully"), tr("Compiled Successfully!"));
            area->openDirectory();
        }
    }
    else {
        statusBar()->showMessage(tr("No window is selected!"), 4000);
        QMessageBox::information(this, tr("Successfully"), tr("Compiled failed!"));
    }
}

void MainWindow::on_actionUpdate_triggered()
{
    QNetworkRequest quest;
    quest.setUrl(QUrl("https://www.demo.com/software_update.json")); //包含最新版本软件的下载地址
    quest.setHeader(QNetworkRequest::UserAgentHeader,"RT-Thread ART");
    manager->get(quest);    //发送get网络请求
}

void MainWindow::replyFinished(QNetworkReply *reply)
{
    QString str = reply->readAll();//读取接收到的数据
    //    qDebug() << str;
    parse_UpdateJSON(str);
    //文件保存到本地
/*
    QFile file("software_update.json");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) //append 内容追加在文件后面
    {
        QMessageBox::critical(this, "错误", "文件打开失败，信息未写入", "确定");
        return;
    }
    QTextStream out(&file);
    out << str;     //输出到文件
    file.close();   //关闭文件
    qDebug() << "文件保存成功!";
//    file.remove();
//    qDebug() << "文件已经删除";
*/
    reply->deleteLater();               //销毁请求对象
}
