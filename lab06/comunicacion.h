#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <QObject>

class Comunicacion : public QObject
{
    Q_OBJECT
public:
    explicit Comunicacion(QObject *parent = nullptr);

signals:
};

#endif // COMUNICACION_H
