#include "task.h"
#include "ui_task.h"

Task::Task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Task)
{
    ui->setupUi(this);
    connect(ui->submit, &QPushButton::clicked, this, [this]() {
        emit dataSubmitted(ui->mitext->toPlainText());
    });
}

Task::~Task()
{
    delete ui;
}
