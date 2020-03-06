#include "controlunit.h"

ControlUnit* ControlUnit::instance = nullptr;

ControlUnit::ControlUnit()
{
    authorized = false;
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
                     "(user_id integer primary key autoincrement unique, "
                     "username varchar(32), "
                     "password varchar(64), "
                     "account_type varchar(9))");
    db->sendSqlQuery("insert into auth (username, password, account_type) values (\"" + username + "\", \"" + QString::fromStdString(pass_hash) + "\", "
                    "\"ADMIN\")");
    db->close();
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

std::vector<Department*> ControlUnit::getDepartments()
{
    return departments_list;
}

void ControlUnit::addDepartment(int id, QString title)
{
    Department *new_department = new Department(id, title);
    departments_list.push_back(new_department);
}

void ControlUnit::removeDepartment(int id)
{
    for (auto iter = departments_list.begin(); iter != departments_list.end(); i++)
    {
        if ((*iter)->getId() == id)
        {
            departments_list.erase(iter);
            break;
        }
    }
}
