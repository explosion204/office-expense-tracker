#include "aggregator.h"

Aggregator::Aggregator()
{
    departments_list = std::vector<Department*>();
}

Aggregator::~Aggregator()
{
    for (auto department: departments_list)
    {
        delete department;
    }
}

void Aggregator::editDepartment(int id, QString title, int members_count)
{
    Department *department = getDepartment(id);
    department->setTitle(title);
    department->setMembersCount(members_count);
}

Department* Aggregator::getDepartment(int id)
{
    for (auto iter = departments_list.begin(); iter != departments_list.end(); iter++)
    {
        if ((*iter)->getId() == id)
            return *iter;
    }
    return nullptr;
}

std::vector<Department*> Aggregator::getDepartments() { return departments_list; }

void Aggregator::addDepartment(int id, QString title, int members_count)
{
    Department *new_department = new Department(id, title, members_count);
    departments_list.push_back(new_department);
}

void Aggregator::removeDepartment(int id)
{
    auto iter_begin = departments_list.begin();
    auto iter_end = departments_list.end();
    auto predicate = [id] (Department *department)
    {
        return (*department).getId() == id;
    };
    departments_list.erase(std::remove_if(iter_begin, iter_end, predicate));
}
