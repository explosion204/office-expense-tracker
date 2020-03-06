#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>

class Expense
{
private:
    int id;
    QString name;
    QString description;
    int limit;
    int value;
public:
    Expense(int id, QString name, QString description, int limit, int value = 0);
    int getId();
    QString getName();
    QString getDescription();
    int getLimit();
    int getValue();
    void setValue(int value);
};

#endif // EXPENSE_H
