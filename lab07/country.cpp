#include "country.h"

Country::Country(const QString &name, const QString &capital, const QString &language, QObject *parent)
    : QObject{parent}
    , name(name)
    , capital(capital)
    , language(language)
{}
