#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>

class Expense
{
private:
    int id;
    int department_id;
    QString name;
    QString description;
    int limit;
    int value;
public:
    Expense(int id, int department_id, QString name, QString description, int limit, int value = 0);
    int getId();
    int getDepartmentId();
    QString getName();
    QString getDescription();
    int getLimit();
    int getValue();
    void setName(QString name);
    void setDescription(QString description);
    void setLimit(int limit);
    void setValue(int value);
};

#endif // EXPENSE_H
