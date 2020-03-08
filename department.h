#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <vector>
#include <memory>
#include <QString>
#include <QObject>
#include <employee.h>
#include <manager.h>
#include <expense.h>

class Department : QObject
{
    Q_OBJECT
private:
    QString title;
    int id;
    std::vector<Expense*> expense_list;
    std::vector<Employee*> employee_list;
    std::vector<Employee*> modified_employee_list;
public:
    Department(int id, QString title);
    std::vector<Expense*> getExpenses();
    std::vector<Employee*> getEmployees();
    QString getTitle();
    int getId();
    void addMember(int id, QString name, QString position, int seniority);
    void editMember(int id, QString name, QString position, int seniority);
    Employee* getMember(int id);
    void setManager(int id);
    void addExpense(int id, QString name, QString description, int limit, int value = 0);
    Expense* getExpense(int id);
    void removeMember(int id);
    void removeExpense(int id);
};

#endif // DEPARTMENT_H
