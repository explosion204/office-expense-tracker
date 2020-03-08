#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>
#include <data/datastatus.h>

class Employee
{
private:
    int id;
    int department_id;
    QString name;
    QString position;
    int seniority; // months
    DataStatus status;
public:
    Employee(int id, int department_id, QString name, QString position, int seniority, DataStatus status = DataStatus::VALIDATED);
    Employee(Employee&);
    int getId();
    int getDepartmentId();
    QString getName();
    QString getPosition();
    int getSeniority();
    DataStatus getStatus();
};

#endif // EMPLOYEE_H
