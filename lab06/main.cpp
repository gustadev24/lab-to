#include <QApplication>
#include "comunicacion.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();

    QObject *person = new QObject;
    Comunicacion *pepe = new Comunicacion(person);
    Comunicacion *jose = new Comunicacion(person);

    pepe->setNombre("Pepe");
    jose->setNombre("Jose");

    QObject::connect(pepe, SIGNAL(enviarmensaje(QString)), jose, SLOT(escuchar(QString)));
    QObject::connect(jose, SIGNAL(enviarmensaje(QString)), pepe, SLOT(escuchar(QString)));

    pepe->conversar("Buenos días");
    jose->conversar("¿Cómo vas?");

    delete person;

    return a.exec();
}
