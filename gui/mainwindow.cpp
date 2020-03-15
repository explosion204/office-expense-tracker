#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //gui set up
    ui->setupUi(this);
    ui->centralwidget->setLayout(new QGridLayout());
    ui->centralwidget->layout()->addWidget(ui->tabWidget);
    ui->tabWidget->setTabEnabled(1, false);
    ui->tabWidget->setTabEnabled(3, false);
    //objects set up
    initViews();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initViews()
{
    ControlUnit::getInstance()->pullValidatedData();
    ControlUnit::getInstance()->pullValidatedData();
    for (auto department: Aggregator::getInstance()->getDepartments())
    {
        ListWidgetItem *dep_item = new ListWidgetItem(department->getId(), department->getTitle());
        ui->departmentsListWidget->addItem(dep_item);
        for (auto expense: department->getExpenses())
        {
            ListWidgetItem *exp_item = new ListWidgetItem(expense->getId(), expense->getName());
            ui->expensesListWidget->addItem(exp_item);
        }
    }
}

void MainWindow::on_departmentsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    int item_id = dynamic_cast<ListWidgetItem*>(current)->getItemId();
    /*
     * Title:
     * Identification number:
     * Members count:
    */

}

void MainWindow::on_expensesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}
