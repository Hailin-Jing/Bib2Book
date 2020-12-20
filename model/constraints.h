#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <QVector>
#include <QStringList>
#include <QObject>
#include <QSettings>
#include <QWidget>
#include <QFontDatabase>
#include <QApplication>

enum language
{
    English,
    Chinese
};

inline int currentLanguageSetting()
{
    QString organization = "WWB-Qt";
    QString appName = "Bib2Book";
    QSettings settings(organization, appName);
    int currentLanguage = settings.value("Language",language::English).toInt();
    return currentLanguage;
}

inline void setGlobalFont(QString fontPath, QWidget *parent)
{
    int fontId = QFontDatabase::addApplicationFont(fontPath);
    QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
    QFont font(msyh, 12);
    QList<QWidget*> widgetList = parent->findChildren<QWidget*>();
    foreach(QWidget *widget, widgetList)
        widget->setFont(font);
}

#endif // CONSTRAINTS_H
