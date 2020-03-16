#include "expense_widget.h"
#include "ui_expense_widget.h"

ExpenseWidget::ExpenseWidget(WidgetPurpose widget_purpose, int expense_id, int department_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpenseWidget)
{
    ui->setupUi(this);
    switch (widget_purpose)
    {
        case ADD:
            ui->pushButton->setText("Add");
            break;
        case EDIT:
        {
            auto expense = ControlUnit::getInstance()->getExpense(expense_id, department_id);
            ui->expenseIdEdit->setText(QString::number(expense_id));
            ui->departmentIdEdit->setText(QString::number(department_id));
            ui->nameEdit->setText(std::get<0>(expense));
            ui->descriptionEdit->setText(std::get<1>(expense));
            ui->valueEdit->setText(QString::number(std::get<2>(expense)));
            ui->limitEdit->setText(QString::number(std::get<3>(expense)));
            ui->pushButton->setText("Save");
            break;
        }
    }
}

ExpenseWidget::~ExpenseWidget()
{
    delete ui;
}
