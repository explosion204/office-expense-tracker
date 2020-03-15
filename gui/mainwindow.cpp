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
    ui->centralwidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
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
    for (auto department: Aggregator::getInstance()->getDepartments())
    {
        ListWidgetItem *dep_item = new ListWidgetItem(department->getId(), department->getTitle());
        ui->departmentsListWidget->addItem(dep_item);
    }
}

void MainWindow::on_departmentsListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        ui->departmentInfo->clear();
        int item_id = dynamic_cast<ListWidgetItem*>(ui->departmentsListWidget->item(currentRow))->getItemId();
        Department *department = Aggregator::getInstance()->getDepartment(item_id);
        QString title = department->getTitle();
        int members_count = department->getMembersCount();
        ui->departmentInfo->setText("Title: " + title + "\nID: " + QString::number(item_id) + "\nMembers count: " + QString::number(members_count));
        ui->expensesListWidget->clear();
        for (auto expense: department->getExpenses())
        {
            ListWidgetItem *exp_item = new ListWidgetItem(expense->getId(), expense->getName());
            ui->expensesListWidget->addItem(exp_item);
        }
    }
}

void MainWindow::on_expensesListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        int item_id = dynamic_cast<ListWidgetItem*>(ui->expensesListWidget->item(currentRow))->getItemId();
        int department_id = dynamic_cast<ListWidgetItem*>(ui->departmentsListWidget->currentItem())->getItemId();
        Expense *expense = ControlUnit::getInstance()->getDepartment(department_id)->getExpense(item_id);
        ui->expenseInfo->setText("Name: " + expense->getName() + "\nID: " + QString::number(expense->getId()) + "\nDepartment ID: " + QString::number(expense->getDepartmentId()) +
                                 "\nDescription: " + expense->getDescription() + "\nLimit value per month: " + QString::number(expense->getLimit()) + "\nCurrent value: " +
                                 QString::number(expense->getValue()));
    }
}

void MainWindow::showAddDepartmentTab(DepartmentWidget *widget)
{
    if (!department_add_tab_opened && !department_edit_tab_opened)
    {
        ui->leftBottomWidget->addTab(widget, "Add");
        department_add_tab_opened = true;
    }
}

void MainWindow::hideAddDepartmentTab()
{
    ui->leftBottomWidget->removeTab(1);
    department_add_tab_opened = false;
}

void MainWindow::showEditDepartmentTab(DepartmentWidget *widget)
{
    if (!department_add_tab_opened && !department_edit_tab_opened)
    {
        ui->leftBottomWidget->addTab(widget, "Edit");
        department_edit_tab_opened = true;
    }
}

void MainWindow::hideEditDepartmentTab()
{
    ui->leftBottomWidget->removeTab(1);
    department_edit_tab_opened = false;
}

void MainWindow::showAddExpenseTab(ExpenseWidget *widget)
{
    if (!expense_add_tab_opened && !expense_edit_tab_opened)
    {
        ui->rightBottomWidget->addTab(widget, "Add");
        expense_add_tab_opened = true;
    }
}

void MainWindow::hideAddExpenseTab()
{
    ui->rightBottomWidget->removeTab(1);
    expense_add_tab_opened = false;
}

void MainWindow::showEditExpenseTab(ExpenseWidget *widget)
{
    if (!expense_add_tab_opened && !expense_edit_tab_opened)
    {
        ui->rightBottomWidget->addTab(widget, "Edit");
        expense_edit_tab_opened = true;
    }
}

void MainWindow::hideEditExpenseTab()
{
    ui->rightBottomWidget->removeTab(1);
    expense_edit_tab_opened = false;
}

void MainWindow::on_addDepartmentButton_clicked()
{
    auto item = ui->departmentsListWidget->currentItem();
    if (item != nullptr)
    {
        int item_id = dynamic_cast<ListWidgetItem*>(item)->getItemId();
        Department *department = ControlUnit::getInstance()->getDepartment(item_id);
        DepartmentWidget *widget = new DepartmentWidget(WidgetPurpose::ADD, department, this);
        showAddDepartmentTab(widget);
    }
}

void MainWindow::on_editDepartmentButton_clicked()
{
    auto item = ui->departmentsListWidget->currentItem();
    if (item != nullptr)
    {
        int item_id = dynamic_cast<ListWidgetItem*>(item)->getItemId();
        Department *department = ControlUnit::getInstance()->getDepartment(item_id);
        DepartmentWidget *widget = new DepartmentWidget(WidgetPurpose::EDIT, department, this);
        showAddDepartmentTab(widget);
    }
}

void MainWindow::on_removeDepartmentButton_clicked()
{

}

void MainWindow::on_addExpenseButton_clicked()
{
    auto expense_item = ui->expensesListWidget->currentItem();
    auto department_item = ui->departmentsListWidget->currentItem();
    if (expense_item != nullptr && department_item != nullptr)
    {
        int expense_id = dynamic_cast<ListWidgetItem*>(expense_item)->getItemId();
        int department_id = dynamic_cast<ListWidgetItem*>(department_item)->getItemId();
        Expense *expense = ControlUnit::getInstance()->getDepartment(department_id)->getExpense(expense_id);
        ExpenseWidget *widget = new ExpenseWidget(WidgetPurpose::ADD, expense, this);
        showAddExpenseTab(widget);
    }
}

void MainWindow::on_editExpenseButton_clicked()
{
    auto expense_item = ui->expensesListWidget->currentItem();
    auto department_item = ui->departmentsListWidget->currentItem();
    if (expense_item != nullptr && department_item != nullptr)
    {
        int expense_id = dynamic_cast<ListWidgetItem*>(expense_item)->getItemId();
        int department_id = dynamic_cast<ListWidgetItem*>(department_item)->getItemId();
        Expense *expense = ControlUnit::getInstance()->getDepartment(department_id)->getExpense(expense_id);
        ExpenseWidget *widget = new ExpenseWidget(WidgetPurpose::EDIT, expense, this);
        showEditExpenseTab(widget);
    }
}

void MainWindow::on_removeExpenseButton_clicked()
{

}
