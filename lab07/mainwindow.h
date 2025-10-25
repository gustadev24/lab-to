#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"
#include "country.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void addTask();
    void removeTask(Task* t);

private:
    Ui::MainWindow *ui;
    QVector<Task*> mTasks;
    QVector<Country*> countries;
};
#endif // MAINWINDOW_H
