#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

#include <service/database.h>
#include <data/department.h>
#include <data/aggregator.h>
#include <data/snapshots.h>
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
    Aggregator *aggregator;
    std::vector<DepartmentSnapshot> department_snapshots;
    std::vector<ExpenseSnapshot> expense_snapshots;
    int recent_department_id;
    int recent_expense_id;
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

    std::tuple<QString, int> getDepartment(int id);
    std::tuple<QString, QString, int, int> getExpense(int expense_id, int department_id);
    int getRecentDepartmentId();
    int getRecentExpenseId();
    std::vector<DepartmentSnapshot>* getDepartmentSnapshots();
    std::vector<ExpenseSnapshot>* getExpenseSnapshots();
    DepartmentSnapshot getDepartmentSnapshot(int id);
    ExpenseSnapshot getExpenseSnapshot(int expense_id, int department_id);
    std::vector<int> getDepartments();
    std::vector<int> getExpenses(int department_id);
    void addDepartment(int id, QString title, int members_count);
    void addExpense(int id, int department_id, QString name, QString description, int limit, int value);
    void removeDepartment(int id);
    void removeExpense(int id, int department_id);
    void editDepartment(int id, QString title, int members_count);
    void editExpense(int id, int department_id, QString name, QString description, int limit, int value);
};

#endif // CONTROLUNIT_H
