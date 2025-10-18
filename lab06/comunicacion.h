#ifndef COMUNICACION_H
#define COMUNICACION_H

#include <QObject>

class Comunicacion : public QObject
{
    Q_OBJECT
private:
    QString strnombre;
public:
    explicit Comunicacion(QObject *parent = nullptr);

    void setNombre(const QString &nomb) {
        strnombre = nomb;
    }

    void conversar(const QString &conversa);

signals:
    void enviarmensaje(QString);
public slots:
    void escuchar(const QString &str);
};

#endif // COMUNICACION_H
