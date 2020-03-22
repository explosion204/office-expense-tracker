#include "controlunit.h"

ControlUnit* ControlUnit::instance = nullptr;

ControlUnit::ControlUnit()
{
    accounts_loaded = false;
    authorized = false;
    department_snapshots = std::vector<DepartmentSnapshot>();
    expense_snapshots = std::vector<ExpenseSnapshot>();
    active_account = nullptr;
    accounts = std::vector<Account>();
    aggregator = new Aggregator();
    recent_department_id = recent_expense_id = -1;
}

ControlUnit* ControlUnit::getInstance()
{
    if (instance  == nullptr)
        instance = new ControlUnit();
    return instance;
}

void ControlUnit::initDatabase(QString db_path, QString master_key, QString username, QString password)
{
    Database::init(db_path, master_key);
    Database *db = Database::getInstance();
    std::string pass_hash = std::string();
    picosha2::hash256_hex_string(password.toStdString(), pass_hash);
    db->sendSqlQuery("create table auth "
                     "(username text primary key unique, "
                     "password text, "
                     "account_type text)");
    db->sendSqlQuery("create table Departments "
                     "(Id integer not null primary key unique, "
                     "Title text not null, "
                     "Members_count integer not null)");
    db->sendSqlQuery("create table Expenses "
                     "(Id integer not null primary key unique, "
                     "Department_id integer not null, "
                     "Name text not null, "
                     "Description text not null, "
                     "Limit_value integer not null, "
                     "Value integer not null)");
    db->sendSqlQuery("create table Departments_modified "
                     "(Id integer not null primary key unique, "
                     "Title text not null, "
                     "Members_count integer not null, "
                     "Status text not null)");
    db->sendSqlQuery("create table Expenses_modified "
                     "(Id integer not null primary key unique, "
                     "Department_id integer not null, "
                     "Name text not null, "
                     "Description text not null, "
                     "Limit_value integer not null, "
                     "Value integer not null,"
                     "Status text not null)");
    db->sendSqlQuery("insert into auth (username, password, account_type) values (\"" + username + "\", \"" + QString::fromStdString(pass_hash) + "\", "
                    "\"ADMIN\")");
}

void ControlUnit::loadAccounts()
{
    accounts.clear();
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select username, password, account_type from auth");
    while (query.next())
    {
        QString username = query.value(0).toString();
        QString password_hash = query.value(1).toString();
        QString account_type = query.value(2).toString();
        if (!account_type.compare("ADMIN"))
        {
            accounts.push_back(Account(username, password_hash, ADMIN));
        }
        else if (!account_type.compare("MODERATOR"))
        {
            accounts.push_back(Account(username, password_hash, MODERATOR));
        }
        else
        {
            accounts.push_back(Account(username, password_hash, MANAGER));
        }
    }
}

void ControlUnit::authorize(QString db_path, QString master_key, QString username, QString password)
{
    Database::init(db_path, master_key);
    std::string pass_hash = std::string();
    picosha2::hash256_hex_string(password.toStdString(), pass_hash);
    loadAccounts();
    for (auto iter = accounts.begin(); iter != accounts.end(); iter++)
    {
        if ((*iter).getUsername() == username)
        {
            if (!pass_hash.compare((*iter).getPasswordHash().toStdString()))
            {
                active_account = &(*iter);
                authorized = true;
            }
            else
            {
                authorized = false;
            }
        }
    }
}

bool ControlUnit::isAuthorized() { return authorized; }


std::tuple<QString, int> ControlUnit::getDepartment(int id)
{
    Department *department = aggregator->getDepartment(id);
    recent_department_id = id;
    if (department != nullptr)
        return std::make_tuple(department->getTitle(), department->getMembersCount());
    else
        throw std::invalid_argument("No department with such id found");
}

int ControlUnit::getRecentDepartmentId() { return recent_department_id; }

int ControlUnit::getRecentExpenseId() { return recent_expense_id; }

std::vector<DepartmentSnapshot>* ControlUnit::getDepartmentSnapshots()
{
    return &department_snapshots;
}

std::vector<ExpenseSnapshot>* ControlUnit::getExpenseSnapshots()
{
    return &expense_snapshots;
}

DepartmentSnapshot ControlUnit::getDepartmentSnapshot(int id)
{
    for (auto iter = department_snapshots.begin(); iter != department_snapshots.end(); iter++)
    {
        if ((*iter).id == id)
        {
            return *iter;
        }
    }
    throw std::invalid_argument("Cannot find snapshot.");
}

ExpenseSnapshot ControlUnit::getExpenseSnapshot(int expense_id, int department_id)
{
    for (auto iter = expense_snapshots.begin(); iter != expense_snapshots.end(); iter++)
    {
        if ((*iter).expense_id == expense_id && (*iter).department_id == department_id)
        {
            return *iter;
        }
    }
    throw std::invalid_argument("Cannot find snapshot.");
}

std::tuple<QString, QString, int, int> ControlUnit::getExpense(int expense_id, int department_id)
{
    Expense *expense = aggregator->getDepartment(department_id)->getExpense(expense_id);
    recent_department_id = department_id;
    recent_expense_id = expense_id;
    return std::make_tuple(expense->getName(), expense->getDescription(), expense->getValue(), expense->getLimit());
}

std::vector<int> ControlUnit::getDepartments()
{
    std::vector<int> department_ids = std::vector<int>();
    for (Department *department : aggregator->getDepartments())
    {
        department_ids.push_back(department->getId());
    }
    return department_ids;
}

std::vector<int> ControlUnit::getExpenses(int department_id)
{
    std::vector<int> expense_ids = std::vector<int>();
    Department *department = aggregator->getDepartment(department_id);
    for (Expense *expense : department->getExpenses())
    {
        expense_ids.push_back(expense->getId());
    }
    return expense_ids;
}

void ControlUnit::pullValidatedData()
{
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select Id, Title, Members_count from Departments");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        int members_count = query.value(2).toInt();
        aggregator->addDepartment(id, title, members_count);
    }
    query = Database::getInstance()->sendSqlQuery("select Id, Department_id, Name, Description, Limit_value, Value from Expenses");
    while (query.next())
    {
        int id = query.value(0).toInt();
        int department_id = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString description = query.value(3).toString();
        int limit = query.value(4).toInt();
        int value = query.value(5).toInt();
        Department *department = aggregator->getDepartment(department_id);
        if (department != nullptr)
            department->addExpense(id, name, description, limit, value);
    }
}

void ControlUnit::pushValidatedData()
{
    Database::getInstance()->sendSqlQuery("delete from Departments");
    Database::getInstance()->sendSqlQuery("delete from Expenses");
    Database::getInstance()->sendSqlQuery("delete from auth");
    for (auto account: accounts)
    {
        QString username = account.getUsername();
        QString password_hash = account.getPasswordHash();
        PermissionType permission_type = account.getPermissionType();
        QString str_permission_type;
        switch (permission_type)
        {
            case ADMIN:
                str_permission_type = "ADMIN";
                break;
            case MODERATOR:
                str_permission_type = "MODERATOR";
                break;
            case MANAGER:
                str_permission_type = "MANAGER";
                break;
        }
        Database::getInstance()->sendSqlQuery("insert into auth (username, password, account_type) values (\"" + username + "\", \"" + password_hash + "\", \"" + str_permission_type + "\")");
    }
    for (auto department: aggregator->getDepartments())
    {
        int department_id = department->getId();
        QString title = department->getTitle();
        int members_count = department->getMembersCount();
        Database::getInstance()->sendSqlQuery("insert into Departments (Id, Title, Members_count) values (" + QString::number(department_id) + ", \"" + title + "\", " + QString::number(members_count) + ")");
        for (auto expense: department->getExpenses())
        {
            int id = expense->getId();
            QString name = expense->getName();
            QString description = expense->getDescription();
            int limit = expense->getLimit();
            int value = expense->getValue();
            Database::getInstance()->sendSqlQuery("insert into Expenses (Id, Department_id, Name, Description, Limit_value, Value) values (" + QString::number(id) + ", "
                            + QString::number(department_id) + ", \"" + name + "\", \"" + description + "\", " + QString::number(limit) + ", " + QString::number(value) + ")");
        }
    }
}

void ControlUnit::pullModifiedData()
{
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select Id, Title, Members_count, Status from Departments_modified");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        int members_count = query.value(2).toInt();
        DataStatus status = DataStatusTools::stringToDataStatus(query.value(3).toString());
        DepartmentSnapshot snapshot(status, id, title, members_count);
        department_snapshots.push_back(snapshot);
    }
    query = Database::getInstance()->sendSqlQuery("select Id, Department_id, Name, Description, Limit_value, Value, Status from Expenses_modified");
    while (query.next())
    {
        int id = query.value(0).toInt();
        int department_id = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString description = query.value(3).toString();
        int limit = query.value(4).toInt();
        int value = query.value(5).toInt();
        DataStatus status = DataStatusTools::stringToDataStatus(query.value(6).toString());
        ExpenseSnapshot snapshot(status, id, department_id, name, description, limit, value);
        expense_snapshots.push_back(snapshot);
    }
}

void ControlUnit::pushModifiedData()
{
    Database::getInstance()->sendSqlQuery("delete from Departments_modified");
    Database::getInstance()->sendSqlQuery("delete from Expenses_modified");
    for (DepartmentSnapshot department_snapshot: department_snapshots)
    {
        int department_id = department_snapshot.id;
        QString title = department_snapshot.title;
        int members_count = department_snapshot.members_count;
        QString status = DataStatusTools::dataStatusToString(department_snapshot.status);
        Database::getInstance()->sendSqlQuery("insert into Departments_modified (Id, Title, Members_count, Status) values "
                                              "(" + QString::number(department_id) + ", \"" + title + "\", " + QString::number(members_count) + ", \"" + status + "\")");
    }
    for (ExpenseSnapshot expense_snapshot: expense_snapshots)
    {
        int id = expense_snapshot.expense_id;
        int department_id = expense_snapshot.department_id;
        QString name = expense_snapshot.name;
        QString description = expense_snapshot.description;
        int limit = expense_snapshot.limit;
        int value = expense_snapshot.value;
        QString status = DataStatusTools::dataStatusToString(expense_snapshot.status);
        Database::getInstance()->sendSqlQuery("insert into Expenses_modified (Id, Department_id, Name, Description, Limit_value, Value, Status) values (" + QString::number(id) + ", "
                        + QString::number(department_id) + ", \"" + name + "\", \"" + description + "\", " + QString::number(limit) + ", " + QString::number(value) + ", \"" + status + "\")");
    }
}



bool ControlUnit::addExpense(int id, int department_id, QString name, QString description, int limit, int value)
{
    if (aggregator->getDepartment(department_id)->getExpense(id) == nullptr)
    {
        if (active_account->getPermission()->canModifyDataDirectly())
        {
            Department *department = aggregator->getDepartment(department_id);
            department->addExpense(id, name, description, limit, value);
        }
        else
        {
            ExpenseSnapshot snapshot(CREATED, id, department_id, name, description, limit, value);
            expense_snapshots.push_back(snapshot);
        }
        recent_department_id = department_id;
        recent_expense_id = id;
        return true;
    }
    else
        return false;
}

void ControlUnit::editExpense(int id, int department_id, QString name, QString description, int limit, int value)
{
    if (active_account->getPermission()->canModifyDataDirectly())
    {
        Department *department = aggregator->getDepartment(department_id);
        department->editExpense(id, name, description, limit, value);
    }
    else
    {
        ExpenseSnapshot snapshot(MODIFIED, id, department_id, name, description, limit, value);
        expense_snapshots.push_back(snapshot);
    }
    recent_department_id = department_id;
    recent_expense_id = id;
}

void ControlUnit::removeExpense(int id, int department_id)
{
    if (active_account->getPermission()->canModifyDataDirectly())
    {
        Department *department = aggregator->getDepartment(department_id);
        department->removeExpense(id);
    }
    else
    {
        Expense *exp_del = aggregator->getDepartment(department_id)->getExpense(id);
        ExpenseSnapshot snapshot(DELETED, id, department_id, exp_del->getName(), exp_del->getDescription(), exp_del->getLimit(), exp_del->getValue());
        expense_snapshots.push_back(snapshot);
    }
    recent_department_id = department_id;
    recent_expense_id = id;
}

bool ControlUnit::addDepartment(int id, QString title, int members_count)
{
    if (aggregator->getDepartment(id) == nullptr)
    {
        if (active_account->getPermission()->canModifyDataDirectly())
        {
            aggregator->addDepartment(id, title, members_count);
        }
        else
        {
            DepartmentSnapshot snapshot(CREATED, id, title, members_count);
            department_snapshots.push_back(snapshot);
        }
        recent_department_id = id;
        return true;
    }
    else
        return false;
}

void ControlUnit::editDepartment(int id, QString title, int members_count)
{
    if (active_account->getPermission()->canModifyDataDirectly())
    {
        aggregator->editDepartment(id, title, members_count);
    }
    else
    {
        DepartmentSnapshot snapshot(MODIFIED, id, title, members_count);
        department_snapshots.push_back(snapshot);
    }
    recent_department_id = id;
}

void ControlUnit::removeDepartment(int id)
{
    if (active_account->getPermission()->canModifyDataDirectly())
    {
        aggregator->removeDepartment(id);
    }
    else
    {
        Department *dep_del = aggregator->getDepartment(id);
        DepartmentSnapshot snapshot(DELETED, id, dep_del->getTitle(), dep_del->getMembersCount());
        department_snapshots.push_back(snapshot);
    }
    recent_department_id = id;
}

void ControlUnit::removeModifiedDepartment(int id)
{
    auto iter_begin = department_snapshots.begin();
    auto iter_end = department_snapshots.end();
    auto predicate = [id] (DepartmentSnapshot snapshot)
    {
        return snapshot.id == id;
    };
    department_snapshots.erase(std::remove_if(iter_begin, iter_end, predicate));
}

void ControlUnit::removeModifiedExpense(int id, int department_id)
{
    auto iter_begin = expense_snapshots.begin();
    auto iter_end = expense_snapshots.end();
    auto predicate = [id, department_id] (ExpenseSnapshot snapshot)
    {
        return snapshot.expense_id == id && snapshot.department_id == department_id;
    };
    expense_snapshots.erase(std::remove_if(iter_begin, iter_end, predicate));
}

std::vector<QString> ControlUnit::getAccounts()
{
    std::vector<QString> usernames = std::vector<QString>();
    for (auto iter = accounts.begin(); iter != accounts.end(); iter++)
    {
        usernames.push_back((*iter).getUsername());
    }
    return usernames;
}

PermissionType ControlUnit::getAccountPermission(QString username)
{
    for (auto iter = accounts.begin(); iter != accounts.end(); iter++)
    {
        if ((*iter).getUsername() == username)
        {
            return (*iter).getPermissionType();
        }
    }
    throw std::invalid_argument("Cannot find account.");
}

QString ControlUnit::getActiveAccountUsername() { return active_account->getUsername(); }

PermissionType ControlUnit::getActiveAccountPermissionType()
{
    return active_account->getPermissionType();
}

bool ControlUnit::addAccount(QString username, QString password, PermissionType permission_type)
{
    for (auto iter = accounts.begin(); iter != accounts.end(); iter++)
    {
        if ((*iter).getUsername() == username)
        {
            return false;
        }
    }
    std::string pass_hash = std::string();
    picosha2::hash256_hex_string(password.toStdString(), pass_hash);
    accounts.push_back(Account(username, QString::fromStdString(pass_hash), permission_type));
    return true;
}

void ControlUnit::removeAccount(QString username)
{
    auto predicate = [username] (Account account)
    {
        return account.getUsername() == username;
    };
    accounts.erase(std::remove_if(accounts.begin(), accounts.end(), predicate));
}
