#ifndef AGGREGATOR_H
#define AGGREGATOR_H

#include <vector>
#include <data/department.h>
#include <data/datastatus.h>

class Aggregator
{
private:
    static Aggregator *instance;
    std::vector<Department*> departments_list;
    Aggregator();
public:
    static Aggregator* getInstance();
    std::vector<Department*> getDepartments();
    void addDepartment(int id, QString title);
    void removeDepartment(int id);
    void editDepartment(int id, QString title);
    Department* getDepartment(int id);
};

#endif // AGGREGATOR_H
