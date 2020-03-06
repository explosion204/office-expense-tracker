#include "manager.h"

Manager::Manager(Employee &employee) : Employee(employee.getId(), employee.getName(), employee.getPosition(), employee.getSeniority())
{ }
