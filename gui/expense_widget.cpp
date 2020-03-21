#include "expense_widget.h"
#include "ui_expense_widget.h"

ExpenseWidget::ExpenseWidget(WidgetPurpose widget_purpose, int expense_id, int department_id, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExpenseWidget)
{
    ui->setupUi(this);
    this->purpose = widget_purpose;
    switch (widget_purpose)
    {
        case ADD:
            ui->pushButton->setText("Add");
            ui->departmentIdEdit->setText(QString::number(department_id));
            ui->departmentIdEdit->setReadOnly(true);
            break;
        case EDIT:
        {
            auto expense = ControlUnit::getInstance()->getExpense(expense_id, department_id);
            ui->expenseIdEdit->setText(QString::number(expense_id));
            ui->departmentIdEdit->setText(QString::number(department_id));
            ui->expenseIdEdit->setReadOnly(true);
            ui->departmentIdEdit->setReadOnly(true);
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

void ExpenseWidget::on_pushButton_clicked()
{
    QString expense_id = ui->expenseIdEdit->text();
    QString department_id = ui->departmentIdEdit->text();
    QString name = ui->nameEdit->text();
    QString description = ui->descriptionEdit->text();
    QString value = ui->valueEdit->text();
    QString limit = ui->limitEdit->text();
    if (!expense_id.isEmpty() && !department_id.isEmpty() && !name.isEmpty() && !description.isEmpty() && !value.isEmpty() && !limit.isEmpty())
    {
        switch (purpose)
        {
            case ADD:
                ControlUnit::getInstance()->addExpense(expense_id.toInt(), department_id.toInt(), name, description, value.toInt(), limit.toInt());
                break;
            case EDIT:
                ControlUnit::getInstance()->editExpense(expense_id.toInt(), department_id.toInt(), name, description, value.toInt(), limit.toInt());
                break;
        }
        updateListWidget();
    }
}

void ExpenseWidget::on_cancelButton_clicked()
{
    cancel();
}
