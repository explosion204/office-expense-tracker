#include "department.h"

Department::Department(int id, QString title)
{
    expense_list = std::vector<Expense*>();
    employee_list = std::vector<Employee*>();
    modified_employee_list = std::vector<Employee*>();
    this->title = title;
    this->id = id;
}

std::vector<Expense*> Department::getExpenses()
{
    return expense_list;
}

std::vector<Employee*> Department::getEmployees()
{
    return employee_list;
}

QString Department::getTitle()
{
    return title;
}

int Department::getId()
{
    return id;
}

void Department::addMember(int id, QString name, QString position, int seniority)
{
    Employee *employee = new Employee(id, name, position, seniority);
    employee_list.push_back(employee);
}

void Department::editMember(int id, QString name, QString position, int seniority)
{
    removeMember(id);
    addMember(id, name, position, seniority);
}

Employee* Department::getMember(int id)
{
    for (auto iter = employee_list.begin(); iter != employee_list.end(); iter++)
    {
        if ((*iter)->getId() == id)
        {
            return *iter;
        }
    }
    return nullptr;
}

void Department::addExpense(int id, QString name, QString description, int limit, int value)
{
    Expense *new_expense = new Expense(id, name, description, limit, value);
    expense_list.push_back(new_expense);
}

void Department::setManager(int id)
{
//    for (auto iter = employee_list.begin(); iter != employee_list.end(); iter++)
//    {
//        if (typeid(*iter) == typeid(Manager))
//        {
//            Employee *employee = new Employee(*(*iter));
//            employee_list.erase(iter);
//            employee_list.insert(iter, employee);
//            break;
//        }
//    }
//    for (auto iter = employee_list.begin(); iter != employee_list.end(); iter++)
//    {
//        if ((*iter)->getId() == id)
//        {
//            Manager *manager = new Manager(*(*iter));
//            employee_list.erase(iter);
//            employee_list.insert(iter, manager);
//            break;
//        }
//    }
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

void Department::removeMember(int id)
{
    auto iter_begin = employee_list.begin();
    auto iter_end = employee_list.end();
    auto predicate = [id] (Employee *employee)
    {
        return (*employee).getId() == id;
    };
    employee_list.erase(std::remove_if(iter_begin, iter_end, predicate));
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
