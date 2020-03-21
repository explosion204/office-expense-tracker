#ifndef EXPENSE_H
#define EXPENSE_H

#include <QString>
#include <data/datastatus.h>

class Expense
{
private:
    int id;
    int department_id;
    QString name;
    QString description;
    int limit;
    int value;
    DataStatus status;
public:
    Expense(int id, int department_id, QString name, QString description, int limit, int value = 0, DataStatus status = DataStatus::VALIDATED);
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
    DataStatus getStatus();
};

#endif // EXPENSE_H
