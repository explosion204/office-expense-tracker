#include "department.h"

Department::Department(int id, QString title, int members_count, DataStatus status)
{
    expense_list = std::vector<Expense*>();
    this->title = title;
    this->id = id;
    this->members_count = members_count;
    this->status = status;
}

std::vector<Expense*> Department::getExpenses() { return expense_list; }

QString Department::getTitle() { return title; }

int Department::getMembersCount() { return members_count; }

int Department::getId() { return id; }

DataStatus Department::getStatus() { return status; }

void Department::setTitle(QString title) { this->title = title; }

void Department::setMembersCount(int count) { this->members_count = count; }

void Department::addExpense(int id, QString name, QString description, int limit, int value)
{
    Expense *new_expense = new Expense(id, this->id, name, description, limit, value);
    expense_list.push_back(new_expense);
}

void Department::editExpense(int id, QString name, QString description, int limit, int value)
{
    Expense *expense = getExpense(id);
    expense->setName(name);
    expense->setDescription(description);
    expense->setLimit(limit);
    expense->setValue(value);
}

Expense* Department::getExpense(int id)
{
    for (auto iter = expense_list.begin(); iter != expense_list.end(); iter++)
    {
        if ((*iter)->getId() == id)
        {
            return *iter;
        }
    }
    return nullptr;
}

void Department::removeExpense(int id)
{
    auto iter_begin = expense_list.begin();
    auto iter_end = expense_list.end();
    auto predicate = [id] (Expense *expense)
    {
        return (*expense).getId() == id;
    };
    expense_list.erase(std::remove_if(iter_begin, iter_end, predicate));
}
