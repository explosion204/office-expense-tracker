#include "expense.h"

Expense::Expense(int id, int department_id, QString name, QString description, int limit, int value, DataStatus status)
{
    this->id = id;
    this->department_id = department_id;
    this->name = name;
    this->description = description;
    this->limit = limit;
    this->value = value;
    this->status = status;
}

int Expense::getId() { return id; }

int Expense::getDepartmentId() { return department_id; }

QString Expense::getName() { return name; }

QString Expense::getDescription() { return description; }

int Expense::getLimit() { return limit; }

int Expense::getValue() { return value; }

DataStatus Expense::getStatus() { return status; }
