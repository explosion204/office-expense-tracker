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
    for (int department_id: ControlUnit::getInstance()->getDepartments())
    {
        auto department = ControlUnit::getInstance()->getDepartment(department_id);
        DepartmentItem *dep_item = new DepartmentItem(department_id, std::get<0>(department));
        ui->departmentsListWidget->addItem(dep_item);
    }
}

void MainWindow::on_departmentsListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        ui->departmentInfo->clear();
        int department_id = dynamic_cast<DepartmentItem*>(ui->departmentsListWidget->item(currentRow))->getId();
        auto department = ControlUnit::getInstance()->getDepartment(department_id);
        QString title = std::get<0>(department);
        int members_count = std::get<1>(department);
        ui->departmentInfo->setText("Title: " + title + "\nID: " + QString::number(department_id) + "\nMembers count: " + QString::number(members_count));
        ui->expensesListWidget->clear();
        for (auto expense_id: ControlUnit::getInstance()->getExpenses(department_id))
        {
            auto expense = ControlUnit::getInstance()->getExpense(department_id, expense_id);
            ExpenseItem *exp_item = new ExpenseItem(expense_id, std::get<0>(expense));
            ui->expensesListWidget->addItem(exp_item);
        }
    }
}

void MainWindow::on_expensesListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        int expense_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->item(currentRow))->getId();
        int department_id = dynamic_cast<DepartmentItem*>(ui->departmentsListWidget->currentItem())->getId();
        auto expense = ControlUnit::getInstance()->getExpense(expense_id, department_id);
        ui->expenseInfo->setText("Name: " + std::get<0>(expense) + "\nID: " + QString::number(expense_id) + "\nDepartment ID: " + QString::number(department_id) +
                                 "\nDescription: " + std::get<1>(expense) + "\nLimit value per month: " + QString::number(std::get<2>(expense)) + "\nCurrent value: " +
                                 QString::number(std::get<3>(expense)));
    }
}

void MainWindow::showAddDepartmentTab(DepartmentWidget *widget)
{
    if (!department_add_tab_opened && !department_edit_tab_opened)
    {
        ui->leftBottomWidget->addTab(widget, "Add");
        department_add_tab_opened = true;
        ui->departmentsListWidget->setEnabled(false);
    }
}

void MainWindow::hideAddDepartmentTab()
{
    ui->leftBottomWidget->removeTab(1);
    department_add_tab_opened = false;
    ui->departmentsListWidget->setEnabled(true);
}

void MainWindow::showEditDepartmentTab(DepartmentWidget *widget)
{
    if (!department_add_tab_opened && !department_edit_tab_opened)
    {
        ui->leftBottomWidget->addTab(widget, "Edit");
        department_edit_tab_opened = true;
        ui->departmentsListWidget->setEnabled(false);
    }
}

void MainWindow::hideEditDepartmentTab()
{
    ui->leftBottomWidget->removeTab(1);
    department_edit_tab_opened = false;
    ui->departmentsListWidget->setEnabled(true);
}

void MainWindow::showAddExpenseTab(ExpenseWidget *widget)
{
    if (!expense_add_tab_opened && !expense_edit_tab_opened)
    {
        ui->rightBottomWidget->addTab(widget, "Add");
        expense_add_tab_opened = true;
        ui->expensesListWidget->setEnabled(false);
    }
}

void MainWindow::hideAddExpenseTab()
{
    ui->rightBottomWidget->removeTab(1);
    expense_add_tab_opened = false;
    ui->expensesListWidget->setEnabled(true);
}

void MainWindow::showEditExpenseTab(ExpenseWidget *widget)
{
    if (!expense_add_tab_opened && !expense_edit_tab_opened)
    {
        ui->rightBottomWidget->addTab(widget, "Edit");
        expense_edit_tab_opened = true;
        ui->expensesListWidget->setEnabled(false);
    }
}

void MainWindow::hideEditExpenseTab()
{
    ui->rightBottomWidget->removeTab(1);
    expense_edit_tab_opened = false;
    ui->expensesListWidget->setEnabled(true);
}

void MainWindow::on_addDepartmentButton_clicked()
{
    DepartmentWidget *widget = new DepartmentWidget(WidgetPurpose::ADD, -1, this);
    connect(widget, &DepartmentWidget::updateListWidget, this, &MainWindow::updateDepartmentsListWidget);
    showAddDepartmentTab(widget);
}

void MainWindow::on_editDepartmentButton_clicked()
{
    auto item = ui->departmentsListWidget->currentItem();
    if (item != nullptr)
    {
        int department_id = dynamic_cast<DepartmentItem*>(item)->getId();
        DepartmentWidget *widget = new DepartmentWidget(WidgetPurpose::EDIT, department_id, this);
        connect(widget, &DepartmentWidget::updateListWidget, this, &MainWindow::updateDepartmentsListWidget);
        showEditDepartmentTab(widget);
    }
}

void MainWindow::on_removeDepartmentButton_clicked()
{
    if (ui->departmentsListWidget->currentRow() != -1)
    {
        int department_id = dynamic_cast<DepartmentItem*>(ui->departmentsListWidget->currentItem())->getId();
        ControlUnit::getInstance()->removeDepartment(department_id);
        //ui->departmentsListWidget->takeItem(ui->departmentsListWidget->currentRow());
        updateDepartmentsListWidget();
    }
}

void MainWindow::on_addExpenseButton_clicked()
{
    auto department_item = ui->departmentsListWidget->currentItem();
    if (department_item != nullptr)
    {
        int department_id = dynamic_cast<DepartmentItem*>(department_item)->getId();
        ExpenseWidget *widget = new ExpenseWidget(WidgetPurpose::ADD, -1, department_id, this);
        connect(widget, &ExpenseWidget::updateListWidget, this, &MainWindow::updateExpensesListWidget);
        showAddExpenseTab(widget);
    }
}

void MainWindow::on_editExpenseButton_clicked()
{
    auto expense_item = ui->expensesListWidget->currentItem();
    auto department_item = ui->departmentsListWidget->currentItem();
    if (expense_item != nullptr && department_item != nullptr)
    {
        int expense_id = dynamic_cast<ExpenseItem*>(expense_item)->getId();
        int department_id = dynamic_cast<DepartmentItem*>(department_item)->getId();
        ExpenseWidget *widget = new ExpenseWidget(WidgetPurpose::EDIT, expense_id, department_id, this);
        showEditExpenseTab(widget);
    }
}

void MainWindow::on_removeExpenseButton_clicked()
{
    if (ui->departmentsListWidget->currentRow() != -1 && ui->expensesListWidget->currentRow() != -1)
    {
        int department_id = dynamic_cast<DepartmentItem*>(ui->departmentsListWidget->currentItem())->getId();
        int expense_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->currentItem())->getId();
        ControlUnit::getInstance()->removeExpense(expense_id, department_id);
        updateExpensesListWidget();
    }
}

void MainWindow::updateDepartmentsListWidget()
{
    int ui_items_count = ui->departmentsListWidget->count();
    int aggregator_items_count = ControlUnit::getInstance()->getDepartments().size();
    if (ui_items_count < aggregator_items_count)
    {
        auto departments = ControlUnit::getInstance()->getDepartments();
        auto department = ControlUnit::getInstance()->getDepartment(departments.back());
        DepartmentItem *dep_item = new DepartmentItem(departments.back(), std::get<0>(department));
        ui->departmentsListWidget->addItem(dep_item);
    }
    if (ui_items_count > aggregator_items_count)
    {
        ui->departmentsListWidget->takeItem(ui->departmentsListWidget->currentRow());
    }
    hideAddDepartmentTab();
}

void MainWindow::updateExpensesListWidget()
{
    auto department_item = ui->departmentsListWidget->currentItem();
    if (department_item != nullptr)
    {
        int department_id = dynamic_cast<DepartmentItem*>(department_item)->getId();
        int ui_items_count = ui->expensesListWidget->count();
        int aggregator_items_count = ControlUnit::getInstance()->getExpenses(department_id).size();
        if (ui_items_count < aggregator_items_count)
        {
            auto expenses = ControlUnit::getInstance()->getExpenses(department_id);
            auto expense = ControlUnit::getInstance()->getExpense(expenses.back(), department_id);
            ExpenseItem *exp_item = new ExpenseItem(expenses.back(), std::get<0>(expense));
            ui->expensesListWidget->addItem(exp_item);
        }
        if (ui_items_count > aggregator_items_count)
        {
            ui->expensesListWidget->takeItem(ui->expensesListWidget->currentRow());
        }
        hideAddExpenseTab();
    }
}
