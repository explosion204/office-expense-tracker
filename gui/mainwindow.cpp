#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->centralwidget->setLayout(new QGridLayout());
    ui->centralwidget->layout()->addWidget(ui->tabWidget);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(3, false);
}

MainWindow::~MainWindow()
{
    delete ui;
}
