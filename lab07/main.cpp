#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    std::srand(std::time(nullptr)); // inicializa la semilla aleatoria

    // Generar un vector con números enteros aleatorios
    std::vector<int> numeros;
    const int TAM = 20;
    for (int i = 0; i < TAM; ++i) {
        numeros.push_back(std::rand() % 100);
    }

    // Mostrar el vector generado
    qDebug() << "Vector generado: ";
    for (int n : numeros)
        qDebug() << n << " ";
    qDebug() << "\n";

    // Contar los números impares y menores que 20
    int contador = std::count_if(numeros.begin(), numeros.end(), [](int n) {
        return (n % 2 != 0) && (n < 20);
    });

    qDebug() << "Cantidad de numeros impares y menores de 20: " << contador << Qt::endl;

    return a.exec();

}
