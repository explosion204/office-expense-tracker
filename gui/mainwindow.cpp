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
    }
}

void MainWindow::on_departmentsListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    ui->departmentInfo->clear();
    int item_id = dynamic_cast<ListWidgetItem*>(current)->getItemId();
    Department *department = Aggregator::getInstance()->getDepartment(item_id);
    QString title = department->getTitle();
    int members_count = department->getMembersCount();
    ui->departmentInfo->setText("Title: " + title + "\nID: " + QString(item_id) + "\nMembers count: " + QString(members_count));
    ui->expensesListWidget->clear();
    for (auto expense: department->getExpenses())
    {
        ListWidgetItem *exp_item = new ListWidgetItem(expense->getId(), expense->getName());
        ui->expensesListWidget->addItem(exp_item);
    }
}

void MainWindow::on_expensesListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    int item_id = dynamic_cast<ListWidgetItem*>(current)->getItemId();
    int department_id = dynamic_cast<ListWidgetItem*>(ui->departmentsListWidget->currentItem())->getItemId();
    Expense *expense = Aggregator::getInstance()->getDepartment(department_id)->getExpense(item_id);
    /*
     * Name:
     * ID:
     * Department ID:
     * Description:
     * Limit value per month:
     * Current value:
    */
    ui->expenseInfo->setText("Name: " + expense->getName() + "\nID: " + QString(expense->getId()) + "\nDepartment ID: " + QString(expense->getDepartmentId()) +
                             "\nDescription: " + expense->getDescription() + "\nLimit value per month: " + QString(expense->getLimit()) + "\nCurrent value: " +
                             QString(expense->getValue()));
}
