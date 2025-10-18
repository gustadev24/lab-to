#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
    connect(ui->green, &QPushButton::clicked, this, [this]() {
        changeSelectedColorTo("Green", Qt::green);

    });
    connect(ui->blue, &QPushButton::clicked, this, [this]() {
        changeSelectedColorTo("Blue", Qt::blue);

    });
    connect(ui->red, &QPushButton::clicked, this, [this]() {
        changeSelectedColorTo("Red", Qt::red);

    });

}

void MainWindow::changeSelectedColorTo(QString label, Qt::GlobalColor color) {
    ui->selectedColor->setText(label);
    QPalette palette = ui->selectedColor->palette();
    palette.setColor(QPalette::WindowText, color);
    ui->selectedColor->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask() {
    qDebug() << "Slot corresponde al click en el botón...";
}
