#include "employee.h"

Employee::Employee(int id, QString name, QString position, int seniority)
{
    this->id = id;
    this->name = name;
    this->position = position;
    this->seniority = seniority;
}

Employee::Employee(Employee &sample)
{
    id = sample.getId();
    name = sample.getName();
    position = sample.getPosition();
    seniority = sample.getSeniority();
}

int Employee::getId() { return id; }

QString Employee::getName() { return name; }

QString Employee::getPosition() { return position; }

int Employee::getSeniority() { return seniority; }
