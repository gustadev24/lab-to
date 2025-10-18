#ifndef ADULTO_H
#define ADULTO_H

#include <QObject>
#include <QDebug>

class Adulto : public QObject
{
    Q_OBJECT
private:
    QString nombre;
public:
    explicit Adulto(QObject *parent = nullptr): QObject(parent){};

    void setNombre(const QString &nomb) {
        nombre = nomb;
    }

    QString getNombre() const {
        return nombre;
    }

    ~Adulto() {
        qDebug() << "...objeto destruido...";
    }

signals:
};

#endif // ADULTO_H
