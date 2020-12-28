#include "project.h"

#include <cmath>
#include <QVector>
#include <QFileInfo>

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
    text.append("\n     && " + QString("Label && ")
                             + QString("Name && ")
                             + QString("Path") + "\n");
    for(int i = 0; i < Bibliogarphies.length(); i++) {
        text.append("  #  && " + BibliogarphiesPrefix[i] + " && "
                               + BibliogarphiesName[i] + " && "
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
            Bibliogarphies.append(line.split("&&").at(3).simplified());
            BibliogarphiesPrefix.append(line.split("&&").at(1).simplified());
            BibliogarphiesName.append(line.split("&&").at(2).simplified());
        }
    }
}

QString Project::generate()
{
    QString TeXString;
    TeXString.append("\\documentclass[12pt]{book}\n\n"
                     "\\usepackage{pdfpages}\n"
                     "\\usepackage{hyperref}\n"
                     "\\usepackage{xeCJK}\n"
                     "\\usepackage{xcolor}\n"
                     "\\usepackage[top=2cm, bottom=2cm, left=4cm, right=3cm]{geometry}\n"
                     "\\pagestyle{empty}\n\n"
                     "\\tolerance=1\n"
                     "\\emergencystretch=\\maxdimen\n"
                     "\\hyphenpenalty=10000\n"
                     "\\hbadness=10000\n\n"
                     "\\begin{document}\n"
                     "\t\\includepdf{Cover.pdf}\n"
                     "\t\\cleardoublepage\n\n"
                     "\t\\begin{center}\n"
                     "\t\t\\bfseries\\centering\\Large Table of Contents\n"
                     "\t\\end{center}\n"
                     "\t\\par\n\n");
    if (Bibliogarphies.length() > 0) {
        TeXString.append("\t\\begin{itemize}\n");
        for(int i = 0; i < Bibliogarphies.length(); i++)
            TeXString.append("\t\t\\item[\\textcolor{red}{" + BibliogarphiesPrefix[i] + "}] "
                             + BibliogarphiesName[i] + " \\hfill\\textcolor{red}{\\pageref{bib:"
                             + QString::number(i + 1) + "}}\n");
        TeXString.append("\t\\end{itemize}\n");
    }
    TeXString.append("\t\\cleardoublepage\n\n"
                     "\t\\includepdfset{pagecommand={\\thispagestyle{headings}}}\n"
                     "\t\\setcounter{page}{1}\n\n");
    for(int i = 0; i < Bibliogarphies.length(); i++) {
        TeXString.append("\t\\label{bib:" + QString::number(i + 1) + "}\n");
        QFileInfo fileInfo(Bibliogarphies[i]);
        QString Name = fileInfo.fileName().replace("~","-").replace("_","-").replace("+","-");
        TeXString.append("\t\\includepdf[pages=1-last]{" + QString("PDFs/File-%1.pdf").arg(QString::number(i + 1)) + "}\n");
    }
    TeXString.append("\n\\end{document}");

    return TeXString;
}

QString Project::generateCover()
{
    QString coverTeXString;
    coverTeXString.append("\\documentclass{article}\n\n"
                          "\\usepackage{aicescover}\n"
                          "\\usepackage{xeCJK}\n"
                          "\\usepackage{hyperref}\n\n"
                          "\\begin{document}\n"
                          "\t\\aicescovertitle{" + Title + "}\n"
                          "\t\\aicescoverauthor{" + Author + "}\n"
                          "\t\\aicescoverack{" + Ack + "}\n\n"
                          "\t\\aicescoverpage\n"
                          "\\end{document}\n");
    return coverTeXString;
}
