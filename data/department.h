#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <vector>
#include <memory>
#include <QString>
#include <data/employee.h>
#include <permissions/manager.h>
#include <data/expense.h>
#include <data/datastatus.h>

class Department
{
private:
    QString title;
    int id;
    int members_count;
    std::vector<Expense*> expense_list;
    //std::vector<Employee*> employee_list;
    //std::vector<Employee*> modified_employee_list;
    DataStatus status;
public:
    Department(int id, QString title, int members_count, DataStatus status = DataStatus::VALIDATED);
    std::vector<Expense*> getExpenses();
//    std::vector<Employee*> getEmployees();
    QString getTitle();
    int getId();
    int getMembersCount();
    DataStatus getStatus();
    void setTitle(QString title);
    void setMembersCount(int count);
//    void addMember(int id, QString name, QString position, int seniority);
//    void editMember(int id, QString name, QString position, int seniority);
//    Employee* getMember(int id);
    void addExpense(int id, QString name, QString description, int limit, int value = 0);
    void editExpense(int id, QString name, QString description, int limit, int value);
    Expense* getExpense(int id);
//    void removeMember(int id);
    void removeExpense(int id);
};

#endif // DEPARTMENT_H
