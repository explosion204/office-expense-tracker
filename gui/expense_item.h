#ifndef EXPENSE_ITEM_H
#define EXPENSE_ITEM_H

#include <QListWidgetItem>
#include <QString>

class ExpenseItem : public QListWidgetItem
{
private:
    int id;
public:
    ExpenseItem(int id, QString string_repr);
    int getId();
};

#endif // EXPENSE_ITEM_H
