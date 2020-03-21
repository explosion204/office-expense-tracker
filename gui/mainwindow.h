#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
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

private:
    Ui::MainWindow *ui;

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
    void updateDepartmentsChangedListWidget();
    void updateExpensesChangedListWidget();
};

#endif // MAINWINDOW_H
