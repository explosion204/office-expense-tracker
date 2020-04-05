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

//    QBrush tb(Qt::transparent);
//    ui->pushButton->setPalette(QPalette(tb, tb, tb, tb, tb, tb, tb, tb, tb));
    ui->pushButton->setFlat(true);

    //objects set up
    initViews();
//    QPixmap image("E:\\projects\\office_expenses\\office_expenses\\service\\plot.png");
//    ui->plotLabel->setPixmap(image);
//    ui->plotLabel->setPixmap(QPixmap());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    ControlUnit::getInstance()->pushValidatedData();
    ControlUnit::getInstance()->pushModifiedData();
    delete ControlUnit::getInstance();
}

void MainWindow::initViews()
{
    //access workaround
    switch (ControlUnit::getInstance()->getActiveAccountPermissionType())
    {
        case ADMIN: break;
        case MODERATOR:
            ui->tabWidget->setTabEnabled(3, false);
            break;
        case MANAGER:
            ui->tabWidget->setTabEnabled(2, false);
            ui->tabWidget->setTabEnabled(3, false);
            break;
    }
    //data workaround
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
        ui->modifiedExpensesListWidget->addItem(exp_item);
    }
    for (QString username: ControlUnit::getInstance()->getAccounts())
    {
        if (username != ControlUnit::getInstance()->getActiveAccountUsername())
        {
            switch (ControlUnit::getInstance()->getAccountPermission(username))
            {
                case MODERATOR:
                {
                    QListWidgetItem *acc_item = new QListWidgetItem("[MODERATOR] " + username);
                    ui->accountsListWidget->addItem(acc_item);
                    break;
                }
                case MANAGER:
                {
                    QListWidgetItem *acc_item = new QListWidgetItem("[MANAGER] " + username);
                    ui->accountsListWidget->addItem(acc_item);
                    break;
                }
                default:
                    break;
            }
        }
    }
}

void MainWindow::on_departmentsListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        ui->departmentInfo->clear();
        int department_id = dynamic_cast<DepartmentItem*>(ui->departmentsListWidget->item(currentRow))->getId();
        try
        {
            auto department = ControlUnit::getInstance()->getDepartment(department_id);
            QString title = std::get<0>(department);
            int members_count = std::get<1>(department);
            ui->departmentInfo->setText("Title: " + title + "\nID: " + QString::number(department_id) + "\nMembers count: " + QString::number(members_count));
            ui->expensesListWidget->clear();
            for (auto expense_id: ControlUnit::getInstance()->getExpenses(department_id))
            {
                auto expense = ControlUnit::getInstance()->getExpense(expense_id, department_id);
                ExpenseItem *exp_item = new ExpenseItem(expense_id, department_id, std::get<0>(expense));
                ui->expensesListWidget->addItem(exp_item);
            }
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_expensesListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        int expense_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->item(currentRow))->getExpenseId();
        int department_id = dynamic_cast<ExpenseItem*>(ui->expensesListWidget->currentItem())->getDepartmentId();
        try
        {
            auto expense = ControlUnit::getInstance()->getExpense(expense_id, department_id);
            ui->expenseInfo->setText("Name: " + std::get<0>(expense) + "\nID: " + QString::number(expense_id) + "\nDepartment ID: " + QString::number(department_id) +
                                     "\nDescription: " + std::get<1>(expense) + "\nLimit value per month: " + QString::number(std::get<2>(expense)) + "\nCurrent value: " +
                                     QString::number(std::get<3>(expense)));
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
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
        try
        {
            auto departments = ControlUnit::getInstance()->getDepartments();
            auto department = ControlUnit::getInstance()->getDepartment(departments.back());
            DepartmentItem *dep_item = new DepartmentItem(departments.back(), std::get<0>(department));
            ui->departmentsListWidget->addItem(dep_item);
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
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
                try
                {
                    auto department = ControlUnit::getInstance()->getDepartment(recent_department_id);
                    DepartmentItem *new_dep_item = new DepartmentItem(recent_department_id, std::get<0>(department));
                    ui->departmentsListWidget->insertItem(i, new_dep_item);
                }
                catch (std::invalid_argument &e)
                {
                    qDebug() << e.what();
                }

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
            try
            {
                auto expenses = ControlUnit::getInstance()->getExpenses(department_id);
                auto expense = ControlUnit::getInstance()->getExpense(expenses.back(), department_id);
                ExpenseItem *exp_item = new ExpenseItem(expenses.back(), department_id, std::get<0>(expense));
                ui->expensesListWidget->addItem(exp_item);
            }
            catch (std::invalid_argument &e)
            {
                qDebug() << e.what();
            }
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
                    try
                    {
                        auto expense = ControlUnit::getInstance()->getExpense(recent_expense_id, department_id);
                        ExpenseItem *new_exp_item = new ExpenseItem(recent_expense_id, department_id, std::get<0>(expense));
                        ui->expensesListWidget->insertItem(i, new_exp_item);
                    }
                    catch (std::invalid_argument &e)
                    {
                        qDebug() << e.what();
                    }

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
        try
        {
            DepartmentItem *dep_item = dynamic_cast<DepartmentItem*>(ui->modifiedDepartmentsListWidget->item(currentRow));
            DepartmentSnapshot snapshot = ControlUnit::getInstance()->getDepartmentSnapshot(dep_item->getId());
            QString status = DataStatusTools::dataStatusToString(snapshot.status);
            ui->changeInfo->setText("ACTION: " + status + "\nTitle: " + snapshot.title + "\nID: " + QString::number(snapshot.id) + "\nMembers count: " + QString::number(snapshot.members_count));
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_modifiedExpensesListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        try
        {
            ExpenseItem *exp_item = dynamic_cast<ExpenseItem*>(ui->modifiedExpensesListWidget->item(currentRow));
            ExpenseSnapshot snapshot = ControlUnit::getInstance()->getExpenseSnapshot(exp_item->getExpenseId(), exp_item->getDepartmentId());
            QString status = DataStatusTools::dataStatusToString(snapshot.status);
            ui->changeInfo->setText("ACTION: " + status + "\nName: " + snapshot.name + "\nID: " + QString::number(snapshot.expense_id) + "\nDepartment ID: " + QString::number(snapshot.department_id) +
                                     "\nDescription: " + snapshot.description + "\nLimit value per month: " + QString::number(snapshot.limit) + "\nCurrent value: " +
                                     QString::number(snapshot.value));
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_departmentApproveButton_clicked()
{
    if (ui->modifiedDepartmentsListWidget->currentRow() != -1)
    {
        try
        {
            DepartmentItem *dep_item = dynamic_cast<DepartmentItem*>(ui->modifiedDepartmentsListWidget->currentItem());
            DepartmentSnapshot snapshot = ControlUnit::getInstance()->getDepartmentSnapshot(dep_item->getId());
            switch (snapshot.status)
            {
                case CREATED:
                    ControlUnit::getInstance()->addDepartment(snapshot.id, snapshot.title, snapshot.members_count);
                    break;
                case MODIFIED:
                    ControlUnit::getInstance()->editDepartment(snapshot.id, snapshot.title, snapshot.members_count);
                    break;
                case DELETED:
                    ControlUnit::getInstance()->removeDepartment(snapshot.id);
                    break;
            }
            ControlUnit::getInstance()->removeModifiedDepartment(snapshot.id);
            updateModifiedDepartmentsListWidget();
            updateDepartmentsListWidget();
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_departmentRejectButton_clicked()
{
    if (ui->modifiedDepartmentsListWidget->currentRow() != -1)
    {
        try
        {
            DepartmentItem *dep_item = dynamic_cast<DepartmentItem*>(ui->modifiedDepartmentsListWidget->currentItem());
            DepartmentSnapshot snapshot = ControlUnit::getInstance()->getDepartmentSnapshot(dep_item->getId());
            ControlUnit::getInstance()->removeModifiedDepartment(snapshot.id);
            updateModifiedDepartmentsListWidget();
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_expenseApproveButton_clicked()
{
    if (ui->modifiedExpensesListWidget->currentRow() != -1)
    {
        try
        {
            ExpenseItem *exp_item = dynamic_cast<ExpenseItem*>(ui->modifiedExpensesListWidget->currentItem());
            ExpenseSnapshot snapshot = ControlUnit::getInstance()->getExpenseSnapshot(exp_item->getExpenseId(), exp_item->getDepartmentId());
            switch (snapshot.status)
            {
                case CREATED:
                    ControlUnit::getInstance()->addExpense(snapshot.expense_id, snapshot.department_id, snapshot.name, snapshot.description, snapshot.limit, snapshot.value);
                    break;
                case MODIFIED:
                    ControlUnit::getInstance()->editExpense(snapshot.expense_id, snapshot.department_id, snapshot.name, snapshot.description, snapshot.limit, snapshot.value);
                    break;
                case DELETED:
                    ControlUnit::getInstance()->removeExpense(snapshot.expense_id, snapshot.department_id);
                    break;
            }
            ControlUnit::getInstance()->removeModifiedExpense(snapshot.expense_id, snapshot.department_id);
            updateModifiedExpensesListWidget();
            updateExpensesListWidget();
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_expenseRejectButton_clicked()
{
    if (ui->modifiedExpensesListWidget->currentRow() != -1)
    {
        try
        {
            ExpenseItem *exp_item = dynamic_cast<ExpenseItem*>(ui->modifiedExpensesListWidget->currentItem());
            ExpenseSnapshot snapshot = ControlUnit::getInstance()->getExpenseSnapshot(exp_item->getExpenseId(), exp_item->getDepartmentId());
            ControlUnit::getInstance()->removeModifiedExpense(snapshot.expense_id, snapshot.department_id);
            updateModifiedExpensesListWidget();
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_addAccountButton_clicked()
{
    QString username = ui->usernameEdit->text();
    QString password = ui->passwordEdit->text();
    if (!username.isEmpty() && !password.isEmpty() && ui->accessRights->currentIndex() != -1)
    {
        switch (ui->accessRights->currentIndex())
        {
            case 0:
                if (!ControlUnit::getInstance()->addAccount(username, password, MODERATOR))
                {
                    //handler
                }
                break;
            case 1:
                if (!ControlUnit::getInstance()->addAccount(username, password, MANAGER))
                {
                    //handler
                }
                break;
        }
        updateAccountsListWidget();
    }
}

void MainWindow::on_removeAccountButton_clicked()
{
    if (ui->accountsListWidget->currentRow() != -1)
    {
        ControlUnit::getInstance()->removeAccount(ui->accountsListWidget->currentItem()->text());
        updateAccountsListWidget();
    }
}

void MainWindow::updateAccountsListWidget()
{
    int ui_items_count = ui->accountsListWidget->count() + 1;
    int actual_items_count = ControlUnit::getInstance()->getAccounts().size();
    if (ui_items_count < actual_items_count)
    {
        QString username = ControlUnit::getInstance()->getAccounts().back();
        try
        {
            switch (ControlUnit::getInstance()->getAccountPermission(username))
            {
                case MODERATOR:
                {
                    QListWidgetItem *acc_item = new QListWidgetItem("[MODERATOR] " + username);
                    ui->accountsListWidget->addItem(acc_item);
                    break;
                }
                case MANAGER:
                {
                    QListWidgetItem *acc_item = new QListWidgetItem("[MANAGER] " + username);
                    ui->accountsListWidget->addItem(acc_item);
                    break;
                }
                default:
                    break;
            }
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
    else if (ui_items_count > actual_items_count)
    {
       ui->accountsListWidget->takeItem(ui->accountsListWidget->currentRow());
    }
}

void MainWindow::on_updateStatsButton_clicked()
{
    auto stat_items = std::vector<std::pair<int, int>>();
    for (int department_id: ControlUnit::getInstance()->getDepartments())
    {
        try
        {
            int sum = 0;
            for (int expense_id: ControlUnit::getInstance()->getExpenses(department_id))
            {
                sum += std::get<3>(ControlUnit::getInstance()->getExpense(expense_id, department_id));
            }
            stat_items.push_back(std::make_pair(department_id, sum));
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
    auto compare_lambda = [] (std::pair<int, int> x, std::pair<int, int> y)
    {
        return std::get<1>(x) > std::get<1>(y);
    };
    std::sort(stat_items.begin(), stat_items.end(), compare_lambda);
    ui->statsListWidget->clear();
    for (auto stat_item: stat_items)
    {
        try
        {
            auto department = ControlUnit::getInstance()->getDepartment(std::get<0>(stat_item));
            DepartmentItem *dep_item = new DepartmentItem(std::get<0>(stat_item), std::get<0>(department));
            ui->statsListWidget->addItem(dep_item);
        }
        catch (std::invalid_argument &e)
        {
            qDebug() << e.what();
        }
    }
}

void MainWindow::on_statsListWidget_currentRowChanged(int currentRow)
{
    if (currentRow != -1)
    {
        ui->statsBrowser->clear();
        int department_id = dynamic_cast<DepartmentItem*>(ui->statsListWidget->item(currentRow))->getId();
        int sum = 0;
        for (int expense_id: ControlUnit::getInstance()->getExpenses(department_id))
        {
            try
            {
                sum += std::get<3>(ControlUnit::getInstance()->getExpense(expense_id, department_id));
            }
            catch (std::invalid_argument &e)
            {
                qDebug() << e.what();
            }
        }
        ui->statsBrowser->clearHistory();
        ui->statsBrowser->setText("TOTAL EXPENSE QUANTITY: " + QString::number(sum));
    }
}

void MainWindow::on_pushButton_clicked()
{
    static int i = 0;
    i++;
    if (i > 5)
    {
        ui->tabWidget->setTabEnabled(3, true);
    }
}
