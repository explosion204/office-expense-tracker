#include "expense_item.h"

ExpenseItem::ExpenseItem(int expense_id, int department_id, QString string_repr) : QListWidgetItem(string_repr)
{
    this->expense_id = expense_id;
    this->department_id = department_id;
}

int ExpenseItem::getExpenseId() { return expense_id; }

int ExpenseItem::getDepartmentId() { return department_id; }
