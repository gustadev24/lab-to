#include "mainwindow.h"

#include <QApplication>
#include "adulto.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Adulto *papa = new Adulto;
    Adulto *hijo1 = new Adulto(papa);
    Adulto *hijo2 = new Adulto(papa);
    hijo1->setNombre("Manuel");
    hijo2->setNombre("Jose");
    delete papa;

    return a.exec();
}
