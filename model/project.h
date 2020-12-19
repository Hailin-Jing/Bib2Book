#ifndef PROJECT_H
#define PROJECT_H

#include "structdefinition.h"
#include "constraints.h"

#include <QString>
#include <QStringList>
#include <QTextEdit>
#include <QVector>

class Project
{
private:


public:
    Project();

    QString fileText();
    void readString(QString text);



protected:

};

#endif // PROJECT_H
