#ifndef EXPENSE_WIDGET_H
#define EXPENSE_WIDGET_H

#include <QWidget>
#include <service/controlunit.h>
#include <gui/widget_purpose.h>

namespace Ui {
class ExpenseWidget;
}

class ExpenseWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExpenseWidget(WidgetPurpose widget_purpose, int id, int department_id, QWidget *parent = nullptr);
    ~ExpenseWidget();

private:
    Ui::ExpenseWidget *ui;
    Expense *expense;
};

#endif // EXPENSE_WIDGET_H
