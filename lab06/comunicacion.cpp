#include "comunicacion.h"
#include <QDebug>

Comunicacion::Comunicacion(QObject *parent)
    : QObject{parent}
{}

void Comunicacion::escuchar(const QString &str) {
    qDebug() << "Estoy escuchando..." << str;
}

void Comunicacion::conversar(const QString &conversa) {
    emit enviarmensaje(conversa);
}
