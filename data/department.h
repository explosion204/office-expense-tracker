#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <vector>
#include <memory>
#include <QString>
#include <permissions/manager.h>
#include <data/expense.h>

class Department
{
private:
    QString title;
    int id;
    int members_count;
    std::vector<Expense*> expense_list;
public:
    Department(int id, QString title, int members_count);
    ~Department();
    std::vector<Expense*> getExpenses();
    QString getTitle();
    int getId();
    int getMembersCount();
    void setTitle(QString title);
    void setMembersCount(int count);
    void addExpense(int id, QString name, QString description, int limit, int value = 0);
    void editExpense(int id, QString name, QString description, int limit, int value);
    Expense* getExpense(int id);
    void removeExpense(int id);
};

#endif // DEPARTMENT_H
