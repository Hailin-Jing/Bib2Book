#include "project.h"

#include <cmath>
#include <QVector>

Project::Project()
{
    Title  = "Book Title";
    Author = "Book Author";
    Ack    = "Book Ack";
}

QString Project::fileText()
{
    QString text;
    text.append("\n******************** Titlepage Information *******************\n");
    text.append(QString("Title").leftJustified(10,' ') + " = " + this->Title + "\n");
    text.append(QString("Author").leftJustified(10,' ') + " = " + this->Author + "\n");
    text.append(QString("Ack").leftJustified(10,' ') + " = " + this->Ack + "\n");
    text.append("\n***************** Biblipgraphies Information *****************");
    text.append("\n     <Separator> " + QString("Prefix <Separator> ")
                                      + QString("Name <Separator> ")
                                      + QString("Path") + "\n");
    for(int i = 0; i < Bibliogarphies.length(); i++) {
        text.append("  #  <Separator> " + BibliogarphiesPrefix[i] + " <Separator> "
                                        + BibliogarphiesName[i] + " <Separator> "
                                        + Bibliogarphies[i] + "\n");
    }
    return text;
}

void Project::readString(QString text)
{
    /*
    QStringList line, lines = text.split("\n");
    QVector<double> data;
    for(QString x : lines) {
        line = x.split("=");
        for (QString y : VAR_NAME_TEXT)
            if (line[0].startsWith(y))
                data.push_back(line[1].toDouble());
    }
    setData(int(data[0]), data.mid(1, data.length() - 1));
    */
    QStringList lines = text.split("\n");
    foreach(QString line, lines) {
        if (line.simplified().isEmpty() || line.startsWith("*"))
            continue;
        else if (line.simplified().startsWith("Title"))
            Title = line.split("=").at(1).simplified();
        else if (line.simplified().startsWith("Author"))
            Author = line.split("=").at(1).simplified();
        else if (line.simplified().startsWith("Ack"))
            Ack = line.split("=").at(1).simplified();
        else if (line.simplified().startsWith("#")) {
            Bibliogarphies.append(line.split("<Separator>").at(3).simplified());
            BibliogarphiesPrefix.append(line.split("<Separator>").at(1).simplified());
            BibliogarphiesName.append(line.split("<Separator>").at(2).simplified());
        }
    }
}
