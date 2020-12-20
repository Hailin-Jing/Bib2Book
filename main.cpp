#include "mainwindow.h"
#include "frame.h"
#include "constraints.h"
#include <QApplication>
#include <QTranslator>
#include <QStyleFactory>

MainWindow *applicationSetup(int argc, char *argv[]);
void registerFileRelation();

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow *window = applicationSetup(argc, argv);

    // Set Font
    int fontId = QFontDatabase::addApplicationFont(QCoreApplication::applicationDirPath() + "/fonts/cormorant-garamond/CormorantGaramond-Regular.ttf");
    // qDebug() << "fontId = "<< fontId;
    QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
    // qDebug() <<"msyh = " <<msyh;
    QFont font(msyh);
    QApplication::setFont(font);

    window->show();

    return app.exec();
}

MainWindow *applicationSetup(int argc, char *argv[])
{
    // Translation
    QTranslator *trans = new QTranslator;
    trans->load(QApplication::applicationDirPath() + "/translations/Bib2Book_en.qm");
    qApp->installTranslator(trans);

    // Application Style
    qApp->setStyle(QStyleFactory::create("Fusion"));

    // Create Registry
    registerFileRelation();

    // QFontDatabase database;
    // foreach(const QString &family, database.families(QFontDatabase::SimplifiedChinese))
    //     qDebug() << family;

    // Open File By Double-click
    QString open_file_path = "";
    if (argc > 1)
        open_file_path = QString::fromLocal8Bit(argv[1]);
    if (!open_file_path.endsWith(".grs"))
        open_file_path = "";
    MainWindow *window = new MainWindow(open_file_path);

    // Spalsh Screen
    /*QPixmap pixmap("://icons/splash_screen.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    splash.showMessage(QStringLiteral("Loading..."), Qt::AlignHCenter|Qt::AlignBottom, Qt::black);
    QDateTime n=QDateTime::currentDateTime();
    QDateTime now;
    int residenceTime = 1;
    do{
        now=QDateTime::currentDateTime();
    }while (n.secsTo(now) <= residenceTime);
    splash.finish(window);*/

    return window;
}

void registerFileRelation()
{
    QString className("Bib2Book");
    QString appPath = QApplication::applicationFilePath().replace("/","\\");
    QString ext(".grs");
    QString extDes("Bib2Book_Project_File");

    QString baseUrl("HKEY_CURRENT_USER\\Software\\Classes");
    QSettings setting(baseUrl,QSettings::NativeFormat);
    setting.setValue("/" + className + "/Shell/Open/Command/.","\"" + appPath + "\" \"%1\"");
    setting.setValue("/" + className + "/.",extDes);
    setting.setValue("/" + className + "/DefaultIcon/.",appPath + ",0");
    setting.setValue("/" + ext + "/OpenWithProgIds/" + className,"");
    setting.sync();
}
