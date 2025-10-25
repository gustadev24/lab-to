#ifndef COUNTRY_H
#define COUNTRY_H

#include <QObject>

class Country : public QObject
{
    Q_OBJECT
public:
    explicit Country(const QString &name, const QString &capital, const QString &language, QObject *parent = nullptr);
    QString name;
    QString capital;
    QString language;
signals:
};

#endif // COUNTRY_H
