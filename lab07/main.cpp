#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    std::vector<int> v {5,2,3,7,1,0,14,20};
    std::for_each(v.begin(), v.end(), [](int valor) {
        qDebug() << valor << Qt::endl;
    });
    return a.exec();

}
