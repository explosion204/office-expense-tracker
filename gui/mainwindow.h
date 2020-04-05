#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QGridLayout>
#include <QPixmap>
#include <QDebug>
#include <service/controlunit.h>
#include <gui/department_item.h>
#include <gui/department_widget.h>
#include <gui/expense_item.h>
#include <gui/expense_widget.h>
#include <gui/widget_purpose.h>

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
    void on_addDepartmentButton_clicked();
    void on_editDepartmentButton_clicked();
    void on_removeDepartmentButton_clicked();
    void on_addExpenseButton_clicked();
    void on_editExpenseButton_clicked();
    void on_removeExpenseButton_clicked();
    void on_modifiedDepartmentsListWidget_currentRowChanged(int currentRow);
    void on_modifiedExpensesListWidget_currentRowChanged(int currentRow);
    void on_departmentApproveButton_clicked();
    void on_departmentRejectButton_clicked();
    void on_expenseApproveButton_clicked();
    void on_expenseRejectButton_clicked();
    void on_addAccountButton_clicked();
    void on_removeAccountButton_clicked();
    void on_updateStatsButton_clicked();

    void on_statsListWidget_currentRowChanged(int currentRow);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    void closeEvent(QCloseEvent *event) override;

    void initViews();
    void enableControls();
    void disableControls();
    void hideAllAddEditTabs();
    void showAddDepartmentTab(DepartmentWidget*);
    void showAddExpenseTab(ExpenseWidget*);
    void showEditDepartmentTab(DepartmentWidget*);
    void showEditExpenseTab(ExpenseWidget*);
    void hideAddDepartmentTab();
    void hideAddExpenseTab();
    void hideEditDepartmentTab();
    void hideEditExpenseTab();

    void updateDepartmentsListWidget();
    void updateExpensesListWidget();
    void updateModifiedDepartmentsListWidget();
    void updateModifiedExpensesListWidget();
    void updateAccountsListWidget();
};

#endif // MAINWINDOW_H
