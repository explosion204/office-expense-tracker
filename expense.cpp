#include "expense.h"

Expense::Expense(int id, QString name, QString description, int limit, int value)
{
    this->name = name;
    this->description = description;
    this->limit = limit;
    this->value = value;
}

int Expense::getId()
{
    return id;
}

QString Expense::getName()
{
    return name;
}

QString Expense::getDescription()
{
    return description;
}

int Expense::getLimit()
{
    return limit;
}

int Expense::getValue()
{
    return value;
}

void Expense::setValue(int value)
{
    this->value = value;
}
