#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <service/controlunit.h>
#include <gui/listwidgetitem.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_departmentsListWidget_currentRowChanged(int currentRow);
    void on_expensesListWidget_currentRowChanged(int currentRow);

private:
    Ui::MainWindow *ui;
    void initViews();
};

#endif // MAINWINDOW_H
