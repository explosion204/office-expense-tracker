#include "department.h"

Department::Department(int id, QString title)
{
    expense_list = std::vector<Expense*>();
    employee_list = std::vector<Employee*>();
    this->title = title;
    this->id = id;
}

std::vector<Expense*> Department::getExpenses()
{
    return expense_list;
}

QString Department::getTitle()
{
    return title;
}

int Department::getId()
{
    return id;
}

int Department::getMemCount()
{
    return mem_count;
}

void Department::addMember(int id, QString name, QString position, int seniority)
{
    Employee *employee = new Employee(id, name, position, seniority);
    employee_list.push_back(employee);
    mem_count++;
}

void Department::addExpense(int id, QString name, QString description, int limit, int value)
{
    Expense *new_expense = new Expense(id, name, description, limit, value);
    expense_list.push_back(new_expense);
}

void Department::setManager(int id)
{
    for (auto iter = employee_list.begin(); iter != employee_list.end(); i++)
    {
        if (typeid(*iter) == typeid(Manager))
        {
            Employee *employee = new Employee(*(*iter));
            employee_list.erase(iter);
            employee_list.insert(iter, employee);
            break;
        }
    }
    for (auto iter = employee_list.begin(); iter != employee_list.end(); i++)
    {
        if ((*iter)->getId() == id)
        {
            Manager *manager = new Manager(*(*iter));
            employee_list.erase(iter);
            employee_list.insert(iter, manager);
            break;
        }
    }
}

void Department::removeMember(int id)
{
    for (auto iter = employee_list.begin(); iter != employee_list.end(); i++)
    {
        if ((*iter)->getId() == id)
        {
            if ((*iter)->getId() == id)
            {
                employee_list.erase(iter);
                break;
            }
        }
    }
}

void Department::removeExpense(int id)
{
    for (auto iter = expense_list.begin(); iter != expense_list.end(); i++)
    {
        if ((*iter)->getId() == id)
        {
            if ((*iter)->getId() == id)
            {
                expense_list.erase(iter);
                break;
            }
        }
    }
}
