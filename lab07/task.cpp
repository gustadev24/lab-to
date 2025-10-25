#include "task.h"
#include "ui_task.h"

Task::Task(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Task)
{
    ui->setupUi(this);
    connect(ui->remove, &QPushButton::clicked, [this]{emit removed(this);});
}

Task::~Task()
{
    delete ui;
}
