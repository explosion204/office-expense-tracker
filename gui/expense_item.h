#ifndef EXPENSE_ITEM_H
#define EXPENSE_ITEM_H

#include <QListWidgetItem>
#include <QString>

class ExpenseItem : public QListWidgetItem
{
private:
    int expense_id;
    int department_id;
public:
    ExpenseItem(int expense_id, int department_id, QString string_repr);
    int getExpenseId();
    int getDepartmentId();
};

#endif // EXPENSE_ITEM_H
