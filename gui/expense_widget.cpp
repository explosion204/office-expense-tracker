#include "expense_widget.h"
#include "ui_expense_widget.h"

ExpenseWidget::ExpenseWidget(WidgetPurpose widget_purpose, Expense *expense, QWidget *parent) :
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
            ui->pushButton->setText("Save");
            break;
    }
    this->expense = expense;
}

ExpenseWidget::~ExpenseWidget()
{
    delete ui;
}
