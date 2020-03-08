#include "employee.h"

Employee::Employee(int id, int department_id, QString name, QString position, int seniority, DataStatus status)
{
    this->id = id;
    this->department_id = department_id;
    this->name = name;
    this->position = position;
    this->seniority = seniority;
    this->status = status;
}

Employee::Employee(Employee &sample)
{
    id = sample.getId();
    name = sample.getName();
    position = sample.getPosition();
    seniority = sample.getSeniority();
}

int Employee::getId() { return id; }

int Employee::getDepartmentId() { return department_id; }

QString Employee::getName() { return name; }

QString Employee::getPosition() { return position; }

int Employee::getSeniority() { return seniority; }

DataStatus Employee::getStatus() { return status; }
