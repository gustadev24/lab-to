#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "task.h"

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

private:
    Ui::MainWindow *ui;
    void changeSelectedColorTo(QString label, Qt::GlobalColor hexColor);
    Task *task;
public slots:
    void addTask();
private slots:
    void handleFormData(const QString &text);

};
#endif // MAINWINDOW_H
