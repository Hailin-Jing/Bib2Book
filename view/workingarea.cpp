#include "workingarea.h"
#include "ui_workingarea.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDragEnterEvent>
#include <QMimeData>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDesktopServices>
#include <QTextCodec>

WorkingArea::WorkingArea(QString filename, int ID, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WorkingArea)
{
    ui->setupUi(this);
    this->parent = parent;
    this->setAcceptDrops(true);
    setAttribute(Qt::WA_DeleteOnClose);
    PRO = new Project();

    setGlobalFont(QCoreApplication::applicationDirPath() + "/fonts/cormorant-garamond/CormorantGaramond-Regular.ttf", this);

    this->ID = ID;
    Last_FileName = filename;
    CurrentRootPath = Last_FileName;
    setWindowTitle(Last_FileName);

    MainWindow *window = qobject_cast<MainWindow*>(parent);
    if (window != nullptr) {
        window->addSequenceNumber(1);
        window->UI()->actionSave->setEnabled(true);
        window->UI()->actionSaveAs->setEnabled(true);
        window->UI()->actionRun->setEnabled(true);
        window->UI()->actionGenerate_TeX_File->setEnabled(true);
        window->UI()->actionCompile->setEnabled(true);
    }

    FileModel = new QFileSystemModel(this);
    QFileInfo fileInfo(Last_FileName);
    FileModel->setRootPath(fileInfo.path());
    ui->treeView->setModel(FileModel);
    ui->treeView->setAlternatingRowColors(true);
    // ui->treeView->setColumnWidth(0, 250);
    // ui->treeView->header()->setSectionResizeMode(QHeaderView::Interactive);

    TableModel = new QStandardItemModel(0, 3, this);
    SelectionModel = new QItemSelectionModel(TableModel);
    ui->tableView->setModel(TableModel);
    ui->tableView->setSelectionModel(SelectionModel);
    ui->tableView->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    connect(SelectionModel, SIGNAL(currentChanged(QModelIndex,  QModelIndex)),
            this, SLOT(on_currentChanged(QModelIndex,  QModelIndex)));

    QStringList header = {tr("Label"), tr("Name"), tr("Path")};
    TableModel->setHorizontalHeaderLabels(header);
}

WorkingArea::~WorkingArea()
{
    MainWindow *window = qobject_cast<MainWindow*>(parent);
    window->UI()->actionMove_Up->setEnabled(false);
    window->UI()->actionMove_Down->setEnabled(false);
    window->UI()->actionRemove->setEnabled(false);
    window->UI()->actionGenerate_TeX_File->setEnabled(true);
    window->UI()->actionCompile->setEnabled(true);
    if (window != nullptr)
        window->addSequenceNumber(-1);
    if (!Flag_IsSaved)
        saveProject();
    delete ui;
}

void WorkingArea::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}

void WorkingArea::dropEvent(QDropEvent *event)
{
    QList<QUrl> urls = event->mimeData()->urls();
    if(urls.isEmpty())
        return;
    foreach(QUrl url, urls) {
        QString file_name = url.toLocalFile();
        if (!file_name.endsWith(".pdf"))
            continue;
        addFile(file_name);
    }
}

bool WorkingArea::open(QString file_name)
{
    QTextCodec *codec = QTextCodec::codecForName("GBK");
    QFile file(file_name);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("Error"),tr("Open file failed"));
        return false;
    }
    else
    {
        if(!file.isReadable()) {
            QMessageBox::warning(this,tr("Error"),tr("File unreadable"));
            return false;
        }
        else
        {
            QTextStream textStream(&file);
            textStream.setCodec("utf-8");
            while(!textStream.atEnd())
                PRO->readString(textStream.readAll());
            file.close();
            ui->title->setText(PRO->title());
            ui->author->setText(PRO->author());
            ui->ack->setText(PRO->ack());

            QStringList Labels = PRO->bibliogarphiesPrefix();
            QStringList Names = PRO->bibliogarphiesName();
            QStringList Paths = PRO->bibliogarphies();
            for(int i = 0; i < Labels.length(); i++) {
                QStandardItem *LabelItem = new QStandardItem(Labels[i]);
                QStandardItem *NameItem = new QStandardItem(Names[i]);
                QStandardItem *PathItem = new QStandardItem(Paths[i]);
                TableModel->appendRow({LabelItem, NameItem, PathItem});
            }

            Flag_IsNew = false;
            Flag_IsSaved = true;
            Last_FileName = file_name;
            CurrentRootPath = Last_FileName;
            refresh();
            return true;
        }
    }
}

bool WorkingArea::saveFile(QString file_name, QString text, bool project)
{
    QFile file(file_name);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("Error"),tr("Open file failed"),QMessageBox::Ok);
        return false;
    }
    else
    {
        QTextStream textStream(&file);
        textStream.setCodec("utf-8");
        textStream << text;
        file.close();
        Flag_IsNew = false;
        Flag_IsSaved = true;
        if (project) {
            Last_FileName = file_name;
            CurrentRootPath = Last_FileName;
        }
        setWindowTitle(Last_FileName);
        refresh();
        return true;
    }
}

bool WorkingArea::save(QString file_name)
{
    return saveFile(file_name, PRO->fileText(), true);
}

bool WorkingArea::saveTex(QString file_name)
{
    return saveFile(file_name, PRO->generate());
}

bool WorkingArea::saveCoverTex(QString file_name)
{
    return saveFile(file_name, PRO->generateCover());
}

bool WorkingArea::generate()
{
    QFileInfo fileInfo(Last_FileName);
    QString TeXFilePath = fileInfo.filePath().replace(".b2b", ".tex");
    QString CoverTeXFilePath = fileInfo.path()+ "/Cover.tex";
    if (saveTex(TeXFilePath) && saveCoverTex(CoverTeXFilePath) && copyFiles() && generateBatFiles()) {
        QMessageBox::information(this, "Successfully", "TeX file generated!");
        Flag_IsRan = true;
        return true;
    }
    return false;
}

bool WorkingArea::compile()
{
    QFileInfo fileInfo(Last_FileName);
    QString CompileBatFilePath = fileInfo.path() + "/Compile.bat";
    bool is_open_compile = QDesktopServices::openUrl(QUrl(CompileBatFilePath, QUrl::TolerantMode));
    if(is_open_compile)
        return true;
    return false;
}

bool WorkingArea::copyFiles()
{
    bool coverFileIfExist = true;

    QString aicescoverFilePath = QCoreApplication::applicationDirPath() + "/stys";
    QFileInfo fileInfo(Last_FileName);
    QString TeXDirPath = fileInfo.path();
    QFile::copy(aicescoverFilePath + "/aicescover.sty", TeXDirPath + "/aicescover.sty");

    QDir sourceDir(aicescoverFilePath + "/aiceslogos");
    QDir targetDir(TeXDirPath + "/aiceslogos");
    if(!targetDir.exists()){
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;
        else{
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName()))
                targetDir.remove(fileInfo.fileName());
            if(!QFile::copy(fileInfo.filePath(), targetDir.filePath(fileInfo.fileName())))
                return false;
        }
    }
    QDir PDFDir(TeXDirPath + "/PDFs");
    if(!PDFDir.exists()){
        if(!PDFDir.mkdir(PDFDir.absolutePath()))
            return false;
    }
    QStringList Paths = PRO->bibliogarphies();
    QStringList Names = PRO->bibliogarphiesName();
    for(int i = 0; i < Paths.length(); i++)
        QFile::copy(Paths[i], TeXDirPath + "/PDFs/" + Names[i] + ".pdf");
    return true;
}

bool WorkingArea::generateBatFiles()
{
    QFileInfo fileInfo(Last_FileName);
    QString CompileBatFile;
    QString CompileBatFilePath = fileInfo.path() + "/Compile.bat";
    QString fileName =  fileInfo.fileName().replace(".b2b", "");
    CompileBatFile.append("@echo off\n\n"
                          "cd \"" + fileInfo.path() + "\"\n\n"
                          "xelatex Cover\n\n"
                          "xelatex " + fileName + "\n" +
                          "xelatex " + fileName + "\n\n");
    CompileBatFile.append("del Cover.aux\n"
                         "del Cover.log\n"
                         "del Cover.out\n"
                         "del Cover.synctex.gz\n\n"
                         "del " +fileName + ".aux\n"
                         "del " +fileName + ".log\n"
                         "del " +fileName + ".out\n"
                         "del " +fileName + ".synctex.gz\n");
    if (saveFile(CompileBatFilePath, CompileBatFile))
        return true;
    return false;
}

void WorkingArea::refresh()
{
    QFileInfo fileInfo(Last_FileName);
    FileModel->setRootPath(fileInfo.path());
    ui->treeView->setRootIndex(FileModel->index(fileInfo.path()));
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

void WorkingArea::moveUp()
{
    QModelIndexList selectedIndex = SelectionModel->selectedIndexes();
    foreach(QModelIndex index, selectedIndex) {
        if (index.row() > 0) {
            PRO->swap(index.row(), index.row() - 1);
            QList<QStandardItem *> row = TableModel->takeRow(index.row());
            TableModel->insertRow(index.row() - 1, row);
        }
    }
    Flag_IsSaved = false;
}

void WorkingArea::moveDown()
{
    QModelIndexList selectedIndex = SelectionModel->selectedIndexes();
    foreach(QModelIndex index, selectedIndex) {
        if (index.row() < TableModel->rowCount() - 1) {
            PRO->swap(index.row(), index.row() + 1);
            QList<QStandardItem *> row = TableModel->takeRow(index.row());
            TableModel->insertRow(index.row() + 1, row);
        }
    }
    Flag_IsSaved = false;
}

void WorkingArea::remove()
{
    QModelIndexList selectedIndex = SelectionModel->selectedIndexes();
    foreach(QModelIndex index, selectedIndex) {
        PRO->remove(index.row());
        TableModel->removeRow(index.row());
    }
    Flag_IsSaved = false;
}

void WorkingArea::addFile(QString filePath)
{
    QFile file(filePath);
    if (filePath.contains("~")){
        if (!file.rename(filePath.replace("~","-")))
            QMessageBox::information(this, "", "File contains '~', the program tried to rename the file, but it failed, please rename the file manually!");
    }
    QFileInfo fileInfo(filePath);
    QString Name = fileInfo.fileName().replace(".pdf","");
    Name.replace("~","-").replace("_","-").replace(" ","-");
    QString Label = QString::number(TableModel->rowCount() + 1);
    QStandardItem *LabelItem = new QStandardItem(Label);
    QStandardItem *NameItem = new QStandardItem(Name);
    QStandardItem *PathItem = new QStandardItem(filePath);
    TableModel->appendRow({LabelItem, NameItem, PathItem});
    PRO->addBibliogarphies({filePath}, {Label}, {Name});
    Flag_IsSaved = false;
}

Ui::WorkingArea *WorkingArea::UI()
{
    return ui;
}

void WorkingArea::saveProject()
{
    QApplication::beep();
    QMessageBox::StandardButton button =
            QMessageBox::question(this,tr("Info"),tr("File %1 has not been saved, whether to save the file?").arg(Last_FileName),
                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
    if (button == QMessageBox::Yes) {
        if(!Flag_IsNew)
            save(Last_FileName);
        else {
            QFileDialog fileDialog;
            QString filename = fileDialog.getSaveFileName(this,tr("Save file"),Last_FileName,tr("Bib2Book Project File(*.b2b)"));
            if(filename.simplified().isEmpty())
                return;
            save(filename);
        }
        QMainWindow *window = qobject_cast<QMainWindow*>(parent);
        window->statusBar()->showMessage(tr("File %1 saved successfully").arg(Last_FileName), 2000);
    }
}

void WorkingArea::on_listWidget_currentRowChanged(int currentRow)
{
    switch (currentRow) { }
}

void WorkingArea::on_listView_doubleClicked(const QModelIndex &index)
{
    CurrentRootPath += FileModel->filePath(index);
    FileModel->setRootPath(CurrentRootPath);
}

void WorkingArea::on_title_textChanged()
{
    PRO->setTitle(ui->title->toPlainText());
    Flag_IsSaved = false;
}

void WorkingArea::on_author_textChanged()
{
    PRO->setAuthor(ui->author->toPlainText());
    Flag_IsSaved = false;
}

void WorkingArea::on_ack_textChanged()
{
    PRO->setAck(ui->ack->toPlainText());
    Flag_IsSaved = false;
}

void WorkingArea::on_currentChanged(const QModelIndex &current, const QModelIndex &previous)
{
    Q_UNUSED(current);
    Q_UNUSED(previous);
    MainWindow *window = qobject_cast<MainWindow*>(parent);
    window->UI()->actionMove_Up->setEnabled(true);
    window->UI()->actionMove_Down->setEnabled(true);
    window->UI()->actionRemove->setEnabled(true);
    window->UI()->actionGenerate_TeX_File->setEnabled(true);
    window->UI()->actionCompile->setEnabled(true);
}

void WorkingArea::on_treeView_doubleClicked(const QModelIndex &index)
{
    QString Path = FileModel->filePath(index);
    addFile(Path);
}
