#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "task.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mTasks()

{
    ui->setupUi(this);
    connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
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
