#ifndef SNAPSHOTS_H
#define SNAPSHOTS_H

#include <data/datastatus.h>

struct DepartmentSnapshot
{
    DepartmentSnapshot(DataStatus status, int id, QString title, int members_count)
    {
        this->status = status;
        this->id = id;
        this->title = title;
        this->members_count = members_count;
    }
    DataStatus status;
    int id;
    QString title;
    int members_count;
};

struct ExpenseSnapshot
{
    ExpenseSnapshot(DataStatus status, int expense_id, int department_id, QString name, QString description, int limit, int value)
    {
        this->status = status;
        this->expense_id = expense_id;
        this->department_id = department_id;
        this->name = name;
        this->description = description;
        this->limit = limit;
        this->value = value;
    }
    DataStatus status;
    int expense_id;
    int department_id;
    QString name;
    QString description;
    int limit;
    int value;
};

#endif // SNAPSHOTS_H
