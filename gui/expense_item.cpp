#include "expense_item.h"

ExpenseItem::ExpenseItem(int id, QString string_repr) : QListWidgetItem(string_repr)
{
    this->id = id;
}

int ExpenseItem::getId() { return id; }
