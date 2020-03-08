#include "controlunit.h"

ControlUnit* ControlUnit::instance = nullptr;

ControlUnit::ControlUnit()
{
    authorized = false;
    departments_list_modified = std::vector<Department*>();
    members_list_modified = std::vector<Employee*>();
    expenses_list_modified = std::vector<Expense*>();
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
                     "(user_id integer primary key unique, "
                     "username text, "
                     "password text, "
                     "account_type text)");
    db->sendSqlQuery("create table Departments "
                     "(Id integer not null primary key unique, "
                     "Title text not null)");
    db->sendSqlQuery("create table Employees "
                     "(Id integer not null primary key unique, "
                     "Department_id integer not null unique, "
                     "Name text not null, "
                     "Position text not null, "
                     "Seniority text not null)");
    db->sendSqlQuery("create table Expenses "
                     "(Id integer not null primary key unique, "
                     "Department_id integer not null primary key, "
                     "Name text not null, "
                     "Description text not null, "
                     "Limit integer not null, "
                     "Value integer not null)");
    db->sendSqlQuery("create table Departments_modified "
                     "(Id integer not null primary key unique, "
                     "Title text not null)");
    db->sendSqlQuery("create table Expenses_modified "
                     "(Id integer not null primary key unique, "
                     "Department_id integer not null primary key, "
                     "Name text not null, "
                     "Description text not null, "
                     "Limit integer not null, "
                     "Value integer not null)");
    db->sendSqlQuery("create table Expenses_modified "
                     "(Id integer not null primary key unique, "
                     "Name text not null, "
                     "Description text not null, "
                     "Limit integer not null, "
                     "Value integer not null)");
    db->sendSqlQuery("insert into auth (user_id, username, password, account_type) values (0, \"" + username + "\", \"" + QString::fromStdString(pass_hash) + "\", "
                    "\"ADMIN\")");
}

bool ControlUnit::authorize(QString db_path, QString master_key, QString username, QString password)
{
    Database::init(db_path, master_key);
    std::string pass_hash = std::string();
    picosha2::hash256_hex_string(password.toStdString(), pass_hash);
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select username, password from auth where username = \"" + username + "\"");
    query.first();
    return !query.value(1).toString().toStdString().compare(pass_hash) ? true : false;
}

void ControlUnit::pullData()
{
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select Id, Title from Departments");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        Department *department = new Department(id, title);
        Aggregator::getInstance()->getDepartments().push_back(department);
    }
    query = Database::getInstance()->sendSqlQuery("select Id, Department_id, Name, Position, Seniority");
    while (query.next())
    {
        int id = query.value(0).toInt();
        int department_id = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString position = query.value(3).toString();
        int seniority = query.value(4).toInt();
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        if (department != nullptr)
            department->addMember(id, name, position, seniority);
    }
}

void ControlUnit::pushAllData()
{
    for (auto department: Aggregator::getInstance()->getDepartments())
    {
        int department_id = department->getId();
        QString title = department->getTitle();
        Database::getInstance()->sendSqlQuery("insert into Departments (Id, Title) values (" + QString(department_id) + ", " + title + ")");
        for (auto employee: department->getEmployees())
        {
            int id = employee->getId();
            QString name = employee->getName();
            QString position = employee->getPosition();
            int seniority = employee->getSeniority();
            Database::getInstance()->sendSqlQuery("insert into Employees (Id, Department_id, Name, Position, Seniority) values (" + QString(id) + ", "
                            + QString(department_id) + "), \"" + QString(name) + "\", \"" + QString(position) + "\", " + QString(seniority) + "");
        }
    }
}

void ControlUnit::pushModifiedData()
{

}
