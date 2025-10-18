#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int x = 47;
    double y = 3.2478;
    char t = 'O';

    QString qtcadena = QString("%1 %2 %3").arg(t).arg(y).arg(x);

    std::string cadena = qtcadena.toStdString();

    qDebug() << cadena.c_str();
    qDebug() << qtcadena;

    qtcadena = "arequipa ciudad blanca 2021";

    qDebug() << qtcadena.contains("ciudad");
    qDebug() << qtcadena.indexOf("2021");

    return a.exec();
}
