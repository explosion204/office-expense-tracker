#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <service/database.h>
#include <data/department.h>
#include <data/aggregator.h>
#include <permissions/administrator.h>
#include <permissions/moderator.h>
#include <permissions/manager.h>
#include <permissions/user.h>
#include <lib/picosha2.h>
#include <QSqlQuery>
#include <QVariant>
#include <QCoreApplication>
#include <QFile>
#include <vector>

class ControlUnit
{
private:
    static ControlUnit *instance;
    ControlUnit();
    bool authorized;
    Permission *permission;
    std::vector<Department*> departments_list_modified;
    std::vector<Employee*> members_list_modified;
    std::vector<Expense*> expenses_list_modified;
public:
    static ControlUnit* getInstance();
    void initDatabase(QString db_path, QString master_key, QString username, QString password);
    void authorize(QString db_path, QString master_key, QString username, QString password);
    bool isAuthorized();
    Permission* getPermission();
    void pullValidatedData();
    void pushValidatedData();
    void pullModifiedData();
    void pushModifiedData();

    void addMember(int id, int department_id, QString name, QString position, int seniority);
    void addDepartment(int id, QString title);
    void addExpense(int id, int department_id, QString name, QString description, int limit, int value);
    void removeMember(int id, int department_id);
    void removeDepartment(int id);
    void removeExpense(int id, int department_id);
    void editMember(int id, int department_id, QString name, QString position, int seniority);
    void editDepartment(int id, QString title);
    void editExpense(int id, int department_id, QString name, QString description, int limit, int value);
};

#endif // CONTROLUNIT_H
