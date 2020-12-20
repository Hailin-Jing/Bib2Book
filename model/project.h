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
    QStringList Bibliogarphies;
    QStringList BibliogarphiesPrefix;
    QStringList BibliogarphiesName;
    QString Title;
    QString Author;
    QString Ack;

public:
    Project();

    void setTitle(QString title){
        this->Title = title;
    }
    void setAuthor(QString author){
        this->Author = author;
    }
    void setAck(QString ack){
        this->Ack = ack;
    }
    void setBibliogarphies(QStringList bibliogarphies, QStringList bibliogarphiesPrefix, QStringList bibliogarphiesName){
        this->Bibliogarphies = bibliogarphies;
        this->BibliogarphiesPrefix = bibliogarphiesPrefix;
        this->BibliogarphiesName = bibliogarphiesName;
    }
    void setTitlePage(QString title, QString author, QString ack){
        this->Title = title;
        this->Author = author;
        this->Ack = ack;
    }
    void addBibliogarphies(QStringList bibliogarphies, QStringList bibliogarphiesPrefix, QStringList bibliogarphiesName) {
        this->Bibliogarphies.append(bibliogarphies);
        this->BibliogarphiesPrefix.append(bibliogarphiesPrefix);
        this->BibliogarphiesName.append(bibliogarphiesName);
    }

    void swap(int i, int j) {
        if (i < 0 || i >= Bibliogarphies.length() || j < 0 || j > Bibliogarphies.length()) {
            qDebug("Swap Error");
            return;
        }
        Bibliogarphies.swapItemsAt(i, j);
        BibliogarphiesPrefix.swapItemsAt(i, j);
        BibliogarphiesName.swapItemsAt(i, j);
    }

    QString fileText();
    void readString(QString text);

    void generate();

protected:

};

#endif // PROJECT_H
