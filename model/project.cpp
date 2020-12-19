#include "project.h"

#include <cmath>
#include <QVector>

Project::Project()
{

}

QString Project::fileText()
{
    QString text;

    return text;
}

void Project::readString(QString text)
{
    QStringList line, lines = text.split("\n");
    QVector<double> data;

}
