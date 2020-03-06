#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <vector>
#include <memory>
#include <QString>
#include <employee.h>
#include <manager.h>
#include <expense.h>

class Department
{
private:
    QString title;
    int id;
    int mem_count;
    std::vector<Expense*> expense_list;
    std::vector<Employee*> employee_list;
public:
    Department(int id, QString title);
    std::vector<Expense*> getExpenses();
    QString getTitle();
    int getId();
    int getMemCount();
    void addMember(int id, QString name, QString position, int seniority);
    void setManager(int id);
    void addExpense(int id, QString name, QString description, int limit, int value = 0);
    void removeMember(int id);
    void removeExpense(int id);
};

#endif // DEPARTMENT_H
