#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QString>

class Employee
{
private:
    int id;
    QString name;
    QString position;
    int seniority; // months
public:
    Employee(int id, QString name, QString position, int seniority);
    Employee(Employee&);
    int getId();
    QString getName();
    QString getPosition();
    int getSeniority();
}

#endif // EMPLOYEE_H
