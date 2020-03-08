#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <database.h>
#include <department.h>
#include <aggregator.h>
#include <lib/picosha2.h>
#include <QSqlQuery>
#include <QVariant>
#include <QCoreApplication>
#include <QFile>
#include <QObject>
#include <vector>

class ControlUnit : QObject
{
    Q_OBJECT
private:
    static ControlUnit *instance;
    ControlUnit();
    bool authorized;
    std::vector<Department*> departments_list_modified;
    std::vector<Employee*> members_list_modified;
    std::vector<Expense*> expenses_list_modified;
public:
    static ControlUnit* getInstance();
    void initDatabase(QString db_path, QString master_key, QString username, QString password);
    bool authorize(QString db_path, QString master_key, QString username, QString password);
    void pullData();
    void pushAllData();
    void pushModifiedData();

    /*to implement*/
    void addMember();
    void addDepartment();
    void removeMember();
    void removeDepartment();
    void editMember();
    void editDepartment();
};

#endif // CONTROLUNIT_H
