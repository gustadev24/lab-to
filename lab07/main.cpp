#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    int (*s)(int) = [](int valor) { return valor + 3; };
    int u = 4;
    qDebug() << s(u) << Qt::endl;
    return a.exec();

}
