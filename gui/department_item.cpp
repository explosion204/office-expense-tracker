#include "department_item.h"

DepartmentItem::DepartmentItem(int id, QString string_repr) : QListWidgetItem(string_repr)
{
    this->id = id;
}

int DepartmentItem::getId() { return id; }
