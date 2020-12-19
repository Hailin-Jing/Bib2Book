#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

#include <QVector>
#include <QStringList>
#include <QObject>
#include <QSettings>

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

#endif // CONSTRAINTS_H
