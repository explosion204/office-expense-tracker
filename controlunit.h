#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <database.h>
#include <department.h>
#include <lib/picosha2.h>
#include <QSqlQuery>
#include <QVariant>
#include <QCoreApplication>
#include <QFile>
#include <vector>

enum Groups
{
    USER, MODERATOR, ADMIN
};

class ControlUnit
{
private:
    static ControlUnit *instance;
    ControlUnit();
    bool authorized;
    std::vector<Department*> departments_list;
public:
    static ControlUnit* getInstance();
    void initDatabase(QString db_path, QString master_key, QString username, QString password);
    bool authorize(QString db_path, QString master_key, QString username, QString password);

    std::vector<Department*> getDepartments();
    void addDepartment(int id, QString title);
    void removeDepartment(int id);
};

#endif // CONTROLUNIT_H
