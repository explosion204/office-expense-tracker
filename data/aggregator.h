#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <vector>
#include <data/department.h>
#include <data/datastatus.h>

class Aggregator
{
private:
    std::vector<Department*> departments_list;
public:
    Aggregator();
    std::vector<Department*> getDepartments();
    void addDepartment(int id, QString title, int members_count);
    void removeDepartment(int id);
    void editDepartment(int id, QString title, int members_count);
    Department* getDepartment(int id);
};

#endif // AGGREGATOR_H
