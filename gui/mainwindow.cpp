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
    ControlUnit::getInstance()->pullModifiedData();
    for (int department_id: ControlUnit::getInstance()->getDepartments())
    {
        auto department = ControlUnit::getInstance()->getDepartment(department_id);
        DepartmentItem *dep_item = new DepartmentItem(department_id, std::get<0>(department));
        ui->departmentsListWidget->addItem(dep_item);
    }
    for (DepartmentSnapshot snapshot: *ControlUnit::getInstance()->getDepartmentSnapshots())
    {
        DepartmentItem *dep_item = new DepartmentItem(snapshot.id, snapshot.title);
        ui->modifiedDepartmentsListWidget->addItem(dep_item);
    }
    for (ExpenseSnapshot snapshot: *ControlUnit::getInstance()->getExpenseSnapshots())
    {
        ExpenseItem *exp_item = new ExpenseItem(snapshot.expense_id, snapshot.department_id, snapshot.name);
        ui->modifiedDepartmentsListWidget->addItem(exp_item);
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
            ExpenseItem *exp_item = new ExpenseItem(expense_id, department_id, std::get<0>(expense));
            ui->expensesListWidget->addItem(exp_item);
        }
    }
}

void MainWindow::on_expensesListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        int expense_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->item(currentRow))->getExpenseId();
        int department_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->currentItem())->getDepartmentId();
        auto expense = ControlUnit::getInstance()->getExpense(expense_id, department_id);
        ui->expenseInfo->setText("Name: " + std::get<0>(expense) + "\nID: " + QString::number(expense_id) + "\nDepartment ID: " + QString::number(department_id) +
                                 "\nDescription: " + std::get<1>(expense) + "\nLimit value per month: " + QString::number(std::get<2>(expense)) + "\nCurrent value: " +
                                 QString::number(std::get<3>(expense)));
    }
}

void MainWindow::enableControls()
{
    ui->departmentsListWidget->setEnabled(true);
    ui->addDepartmentButton->setEnabled(true);
    ui->editDepartmentButton->setEnabled(true);
    ui->removeDepartmentButton->setEnabled(true);
    ui->expensesListWidget->setEnabled(true);
    ui->addExpenseButton->setEnabled(true);
    ui->editExpenseButton->setEnabled(true);
    ui->removeExpenseButton->setEnabled(true);
}

void MainWindow::disableControls()
{
    ui->departmentsListWidget->setEnabled(false);
    ui->addDepartmentButton->setEnabled(false);
    ui->editDepartmentButton->setEnabled(false);
    ui->removeDepartmentButton->setEnabled(false);
    ui->expensesListWidget->setEnabled(false);
    ui->addExpenseButton->setEnabled(false);
    ui->editExpenseButton->setEnabled(false);
    ui->removeExpenseButton->setEnabled(false);
}

void MainWindow::hideAllAddEditTabs()
{
    hideAddDepartmentTab();
    hideAddExpenseTab();
    hideEditDepartmentTab();
    hideEditExpenseTab();
}

void MainWindow::showAddDepartmentTab(DepartmentWidget *widget)
{
    ui->leftBottomWidget->addTab(widget, "Add");
    disableControls();
}

void MainWindow::hideAddDepartmentTab()
{
    ui->leftBottomWidget->removeTab(1);
    enableControls();
}

void MainWindow::showEditDepartmentTab(DepartmentWidget *widget)
{
    ui->leftBottomWidget->addTab(widget, "Edit");
    disableControls();
}

void MainWindow::hideEditDepartmentTab()
{
    ui->leftBottomWidget->removeTab(1);
    enableControls();
}

void MainWindow::showAddExpenseTab(ExpenseWidget *widget)
{
    ui->rightBottomWidget->addTab(widget, "Add");
    disableControls();
}

void MainWindow::hideAddExpenseTab()
{
    ui->rightBottomWidget->removeTab(1);
    enableControls();
}

void MainWindow::showEditExpenseTab(ExpenseWidget *widget)
{
    ui->rightBottomWidget->addTab(widget, "Edit");
    disableControls();
}

void MainWindow::hideEditExpenseTab()
{
    ui->rightBottomWidget->removeTab(1);
    enableControls();
}

void MainWindow::on_addDepartmentButton_clicked()
{
    DepartmentWidget *widget = new DepartmentWidget(WidgetPurpose::ADD, -1, this);
    connect(widget, &DepartmentWidget::updateListWidget, this, &MainWindow::updateDepartmentsListWidget);
    connect(widget, &DepartmentWidget::updateListWidget, this, &MainWindow::updateModifiedDepartmentsListWidget);
    connect(widget, &DepartmentWidget::cancel, this, &MainWindow::hideAllAddEditTabs);
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
        connect(widget, &DepartmentWidget::cancel, this, &MainWindow::hideAllAddEditTabs);
        connect(widget, &DepartmentWidget::updateListWidget, this, &MainWindow::updateModifiedDepartmentsListWidget);
        showEditDepartmentTab(widget);
    }
}

void MainWindow::on_removeDepartmentButton_clicked()
{
    if (ui->departmentsListWidget->currentRow() != -1)
    {
        int department_id = dynamic_cast<DepartmentItem*>(ui->departmentsListWidget->currentItem())->getId();
        ControlUnit::getInstance()->removeDepartment(department_id);
        updateDepartmentsListWidget();
        updateModifiedDepartmentsListWidget();
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
        connect(widget, &ExpenseWidget::updateListWidget, this, &MainWindow::updateModifiedExpensesListWidget);
        connect(widget, &ExpenseWidget::cancel, this, &MainWindow::hideAllAddEditTabs);
        showAddExpenseTab(widget);
    }
}

void MainWindow::on_editExpenseButton_clicked()
{
    auto expense_item = ui->expensesListWidget->currentItem();
    auto department_item = ui->departmentsListWidget->currentItem();
    if (expense_item != nullptr && department_item != nullptr)
    {
        int expense_id = dynamic_cast<ExpenseItem*>(expense_item)->getExpenseId();
        int department_id = dynamic_cast<ExpenseItem*>(expense_item)->getDepartmentId();
        ExpenseWidget *widget = new ExpenseWidget(WidgetPurpose::EDIT, expense_id, department_id, this);
        connect(widget, &ExpenseWidget::updateListWidget, this, &MainWindow::updateExpensesListWidget);
        connect(widget, &ExpenseWidget::updateListWidget, this, &MainWindow::updateModifiedExpensesListWidget);
        connect(widget, &ExpenseWidget::cancel, this, &MainWindow::hideAllAddEditTabs);
        showEditExpenseTab(widget);
    }
}

void MainWindow::on_removeExpenseButton_clicked()
{
    if (ui->departmentsListWidget->currentRow() != -1 && ui->expensesListWidget->currentRow() != -1)
    {
        int department_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->currentItem())->getDepartmentId();
        int expense_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->currentItem())->getExpenseId();
        ControlUnit::getInstance()->removeExpense(expense_id, department_id);
        updateExpensesListWidget();
        updateModifiedExpensesListWidget();
    }
}

void MainWindow::updateDepartmentsListWidget()
{
    int ui_items_count = ui->departmentsListWidget->count();
    int actual_items_count = ControlUnit::getInstance()->getDepartments().size();
    if (ui_items_count < actual_items_count)
    {
        auto departments = ControlUnit::getInstance()->getDepartments();
        auto department = ControlUnit::getInstance()->getDepartment(departments.back());
        DepartmentItem *dep_item = new DepartmentItem(departments.back(), std::get<0>(department));
        ui->departmentsListWidget->addItem(dep_item);
    }
    else if (ui_items_count > actual_items_count)
    {
        ui->departmentsListWidget->takeItem(ui->departmentsListWidget->currentRow());
    }
    else
    {
        int recent_department_id = ControlUnit::getInstance()->getRecentDepartmentId();
        for (int i = 0; i < ui->departmentsListWidget->count(); i++)
        {
            auto *dep_item = dynamic_cast<DepartmentItem*>(ui->departmentsListWidget->item(i));
            if (dep_item->getId() == recent_department_id)
            {
                ui->departmentsListWidget->takeItem(i);
                auto department = ControlUnit::getInstance()->getDepartment(recent_department_id);
                DepartmentItem *new_dep_item = new DepartmentItem(recent_department_id, std::get<0>(department));
                ui->departmentsListWidget->insertItem(i, new_dep_item);
                break;
            }
        }
    }
    hideAddDepartmentTab();
    hideEditDepartmentTab();
}

void MainWindow::updateExpensesListWidget()
{
    auto department_item = ui->departmentsListWidget->currentItem();
    if (department_item != nullptr)
    {
        int department_id = dynamic_cast<DepartmentItem*>(department_item)->getId();
        int ui_items_count = ui->expensesListWidget->count();
        int actual_items_count = ControlUnit::getInstance()->getExpenses(department_id).size();
        if (ui_items_count < actual_items_count)
        {
            auto expenses = ControlUnit::getInstance()->getExpenses(department_id);
            auto expense = ControlUnit::getInstance()->getExpense(expenses.back(), department_id);
            ExpenseItem *exp_item = new ExpenseItem(expenses.back(), department_id, std::get<0>(expense));
            ui->expensesListWidget->addItem(exp_item);
        }
        else if (ui_items_count > actual_items_count)
        {
            ui->expensesListWidget->takeItem(ui->expensesListWidget->currentRow());
        }
        else
        {
            int recent_expense_id = ControlUnit::getInstance()->getRecentExpenseId();
            for (int i = 0; i < ui->expensesListWidget->count(); i++)
            {
                auto exp_item = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->item(i));
                if (exp_item->getExpenseId() == recent_expense_id)
                {
                    ui->expensesListWidget->takeItem(i);
                    auto expense = ControlUnit::getInstance()->getExpense(department_id, recent_expense_id);
                    ExpenseItem *new_exp_item = new ExpenseItem(recent_expense_id, department_id, std::get<0>(expense));
                    ui->expensesListWidget->insertItem(i, new_exp_item);
                    break;
                }
            }
        }
        hideAddExpenseTab();
        hideEditExpenseTab();
    }
}

void MainWindow::updateModifiedDepartmentsListWidget()
{
    int ui_items_count = ui->modifiedDepartmentsListWidget->count();
    int actual_items_count = ControlUnit::getInstance()->getDepartmentSnapshots()->size();
    if (ui_items_count < actual_items_count)
    {
        DepartmentSnapshot snapshot = ControlUnit::getInstance()->getDepartmentSnapshots()->back();
        DepartmentItem *dep_item = new DepartmentItem(snapshot.id, snapshot.title);
        ui->modifiedDepartmentsListWidget->addItem(dep_item);
    }
    else if (ui_items_count > actual_items_count)
    {
        ui->modifiedDepartmentsListWidget->takeItem(ui->modifiedDepartmentsListWidget->currentRow());
    }
}

void MainWindow::updateModifiedExpensesListWidget()
{
    int ui_items_count = ui->modifiedExpensesListWidget->count();
    int actual_items_count = ControlUnit::getInstance()->getExpenseSnapshots()->size();
    if (ui_items_count < actual_items_count)
    {
        ExpenseSnapshot snapshot = ControlUnit::getInstance()->getExpenseSnapshots()->back();
        ExpenseItem *exp_item = new ExpenseItem(snapshot.expense_id, snapshot.department_id, snapshot.name);
        ui->modifiedExpensesListWidget->addItem(exp_item);
    }
    else if (ui_items_count > actual_items_count)
    {
        ui->modifiedExpensesListWidget->takeItem(ui->modifiedExpensesListWidget->currentRow());
    }
}

void MainWindow::on_modifiedDepartmentsListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        DepartmentItem *dep_item = dynamic_cast<DepartmentItem*>(ui->modifiedDepartmentsListWidget->item(currentRow));
        DepartmentSnapshot snapshot = ControlUnit::getInstance()->getDepartmentSnapshot(dep_item->getId());
        QString status = DataStatusTools::dataStatusToString(snapshot.status);
        ui->changeInfo->setText("ACTION: " + status + "\nTitle: " + snapshot.title + "\nID: " + QString::number(snapshot.id) + "\nMembers count: " + QString::number(snapshot.members_count));
    }
}

void MainWindow::on_modifiedExpensesListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        ExpenseItem *exp_item = dynamic_cast<ExpenseItem*>(ui->modifiedExpensesListWidget->item(currentRow));
        ExpenseSnapshot snapshot = ControlUnit::getInstance()->getExpenseSnapshot(exp_item->getExpenseId(), exp_item->getDepartmentId());
        QString status = DataStatusTools::dataStatusToString(snapshot.status);
        ui->changeInfo->setText("ACTION: " + status + "\nName: " + snapshot.name + "\nID: " + QString::number(snapshot.expense_id) + "\nDepartment ID: " + QString::number(snapshot.department_id) +
                                 "\nDescription: " + snapshot.description + "\nLimit value per month: " + QString::number(snapshot.limit) + "\nCurrent value: " +
                                 QString::number(snapshot.value));
    }
}

void MainWindow::on_departmentApproveButton_clicked()
{
    if (ui->modifiedDepartmentsListWidget->currentRow() != -1)
    {

    }
}

void MainWindow::on_departmentRejectButton_clicked()
{
    if (ui->modifiedDepartmentsListWidget->currentRow() != -1)
    {

    }
}

void MainWindow::on_expenseApproveButton_clicked()
{
    if (ui->modifiedExpensesListWidget->currentRow() != -1)
    {

    }
}

void MainWindow::on_expenseRejectButton_clicked()
{
    if (ui->modifiedExpensesListWidget->currentRow() != -1)
    {

    }
}
