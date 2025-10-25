#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "task.h"
#include "country.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()
    , countries{
        new Country("Peru", "Lima", "Castellano"),
        new Country("Mexico", "Ciudad de Mexico", "Español"),
        new Country("Estados Unidos", "Washington D.C.", "Inglés"),
        new Country("Francia", "París", "Francés"),
        new Country("Japon", "Tokio", "Japonés"),
        new Country("Brasil", "Brasilia", "Portugués")

}

{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);

    for (Country *c : countries) {
        QPushButton* b = new QPushButton(c->name, this);
        ui->countriesLayout->addWidget(b);
        connect(b, &QPushButton::clicked, this, [this, c]() {
            ui->countryName->setText(c->name);
            ui->countryCapital->setText(c->capital);
            ui->countryLanguage->setText(c->language);
        });
    }
}

void MainWindow::addTask() {
    Task* t = new Task(this);
    ui->tasksLayout->addWidget(t);
    mTasks.append(t);

    connect(t, &Task::removed, this, [this, t]() {
        removeTask(t);
    });
}

void MainWindow::removeTask(Task* t) {
    ui->tasksLayout->removeWidget(t);
    mTasks.removeOne(t);
    t->deleteLater();

}

MainWindow::~MainWindow()
{
    delete ui;
}
