#include "controlunit.h"

ControlUnit* ControlUnit::instance = nullptr;

ControlUnit::ControlUnit()
{
    authorized = false;
    departments_list_modified = std::vector<Department*>();
    members_list_modified = std::vector<Employee*>();
    expenses_list_modified = std::vector<Expense*>();
    permission = nullptr;
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
                     "Title text not null, "
                     "Status text not null)");
    db->sendSqlQuery("create table Employees_modified "
                     "(Id integer not null primary key unique, "
                     "Department_id integer not null unique, "
                     "Name text not null, "
                     "Position text not null, "
                     "Seniority text not null,"
                     "Status text not null)");
    db->sendSqlQuery("create table Expenses_modified "
                     "(Id integer not null primary key unique, "
                     "Department_id integer not null primary key, "
                     "Name text not null, "
                     "Description text not null, "
                     "Limit integer not null, "
                     "Value integer not null,"
                     "Status text not null)");
    db->sendSqlQuery("insert into auth (user_id, username, password, account_type) values (0, \"" + username + "\", \"" + QString::fromStdString(pass_hash) + "\", "
                    "\"ADMIN\")");
}

void ControlUnit::authorize(QString db_path, QString master_key, QString username, QString password)
{
    Database::init(db_path, master_key);
    std::string pass_hash = std::string();
    picosha2::hash256_hex_string(password.toStdString(), pass_hash);
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select username, password, account_type from auth where username = \"" + username + "\"");
    query.first();
    authorized = !query.value(1).toString().toStdString().compare(pass_hash);
    if (authorized)
    {
        QString account_type = query.value(2).toString();
        if (!account_type.compare("ADMIN"))
        {
            permission = new Administrator();
        }
        else if (!account_type.compare("MODERATOR"))
        {
            permission = new Moderator();
        }
        else if (!account_type.compare("MANAGER"))
        {
            permission = new Manager();
        }
        else
        {
            permission = new User();
        }
    }
}

bool ControlUnit::isAuthorized() { return authorized; }

Permission* ControlUnit::getPermission() { return permission; }

void ControlUnit::pullValidatedData()
{
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select Id, Title from Departments");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        Department *department = new Department(id, title);
        Aggregator::getInstance()->getDepartments().push_back(department);
    }
    query = Database::getInstance()->sendSqlQuery("select Id, Department_id, Name, Position, Seniority from Employees");
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
    query = Database::getInstance()->sendSqlQuery("select Id, Department_id, Name, Description, Limit, Value from Expenses");
    while (query.next())
    {
        int id = query.value(0).toInt();
        int department_id = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString description = query.value(3).toString();
        int limit = query.value(4).toInt();
        int value = query.value(5).toInt();
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        if (department != nullptr)
            department->addExpense(id, name, description, limit, value);
    }
}

void ControlUnit::pushValidatedData()
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
                            + QString(department_id) + "), \"" + name + "\", \"" + position + "\", " + QString(seniority) + ")");
        }
        for (auto expense: department->getExpenses())
        {
            int id = expense->getId();
            QString name = expense->getName();
            QString description = expense->getDescription();
            int limit = expense->getLimit();
            int value = expense->getValue();
            Database::getInstance()->sendSqlQuery("insert into Expenses (Id, Department_id, Name, Description, Limit, Value) values (" + QString(id) + ", "
                            + QString(department_id) + "), \"" + name + "\", \"" + description + "\", " + QString(limit) + ", " + QString(value) + ")");
        }
    }
}

void ControlUnit::pullModifiedData()
{
    QSqlQuery query = Database::getInstance()->sendSqlQuery("select Id, Title, Status from Departments_modified");
    while (query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        DataStatus status = DataStatusTools::stringToDataStatus(query.value(2).toString());
        Department *department = new Department(id, title, status);
        departments_list_modified.push_back(department);
    }
    query = Database::getInstance()->sendSqlQuery("select Id, Department_id, Name, Position, Seniority, Status from Employees");
    while (query.next())
    {
        int id = query.value(0).toInt();
        int department_id = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString position = query.value(3).toString();
        int seniority = query.value(4).toInt();
        DataStatus status = DataStatusTools::stringToDataStatus(query.value(5).toString());
        Employee *employee = new Employee(id, department_id, name, position, seniority, status);
        members_list_modified.push_back(employee);
    }
    query = Database::getInstance()->sendSqlQuery("select Id, Department_id, Name, Description, Limit, Value, Status from Expenses");
    while (query.next())
    {
        int id = query.value(0).toInt();
        int department_id = query.value(1).toInt();
        QString name = query.value(2).toString();
        QString description = query.value(3).toString();
        int limit = query.value(4).toInt();
        int value = query.value(5).toInt();
        DataStatus status = DataStatusTools::stringToDataStatus(query.value(6).toString());
        Expense *expense = new Expense(id, department_id, name, description, limit, value, status);
        expenses_list_modified.push_back(expense);
    }
}

void ControlUnit::pushModifiedData()
{
    for (auto department: departments_list_modified)
    {
        int department_id = department->getId();
        QString title = department->getTitle();
        QString status = DataStatusTools::dataStatusToString(department->getStatus());
        Database::getInstance()->sendSqlQuery("insert into Departments_modified (Id, Title, Status) values "
                                              "(" + QString(department_id) + ", \"" + title + "\", \"" + status + "\")");
    }
    for (auto employee: members_list_modified)
    {
        int id = employee->getId();
        int department_id = employee->getDepartmentId();
        QString name = employee->getName();
        QString position = employee->getPosition();
        int seniority = employee->getSeniority();
        QString status = DataStatusTools::dataStatusToString(employee->getStatus());
        Database::getInstance()->sendSqlQuery("insert into Employees (Id, Department_id, Name, Position, Seniority, Status) values (" + QString(id) + ", "
                        + QString(department_id) + "), \"" + name + "\", \"" + position + "\", " + QString(seniority) + ", \"" + status + "\")");
    }
    for (auto expense: expenses_list_modified)
    {
        int id = expense->getId();
        int department_id = expense->getDepartmentId();
        QString name = expense->getName();
        QString description = expense->getDescription();
        int limit = expense->getLimit();
        int value = expense->getValue();
        QString status = DataStatusTools::dataStatusToString(expense->getStatus());
        Database::getInstance()->sendSqlQuery("insert into Expenses (Id, Department_id, Name, Description, Limit, Value, Status) values (" + QString(id) + ", "
                        + QString(department_id) + "), \"" + name + "\", \"" + description + "\", " + QString(limit) + ", " + QString(value) + ", \"" + status + "\")");
    }
}

void ControlUnit::addMember(int id, int department_id, QString name, QString position, int seniority)
{
    if (permission->canModifyDataDirectly())
    {
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        department->addMember(id, name, position, seniority);
    }
    else
    {
        Employee *employee = new Employee(id, department_id, name, position, seniority, CREATED);
        members_list_modified.push_back(employee);
    }
}

void ControlUnit::editMember(int id, int department_id, QString name, QString position, int seniority)
{
    if (permission->canModifyDataDirectly())
    {
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        department->editMember(id, name, position, seniority);
    }
    else
    {
        Employee *employee = new Employee(id, department_id, name, position, seniority, MODIFIED);
        members_list_modified.push_back(employee);
    }
}

void ControlUnit::removeMember(int id, int department_id)
{
    if (permission->canModifyDataDirectly())
    {
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        department->removeMember(id);
    }
    else
    {
        Employee *empl_del = Aggregator::getInstance()->getDepartment(department_id)->getMember(id);
        Employee *employee = new Employee(id, department_id, empl_del->getName(), empl_del->getPosition(),
                                          empl_del->getSeniority(), DELETED);
        members_list_modified.push_back(employee);
    }
}

void ControlUnit::addExpense(int id, int department_id, QString name, QString description, int limit, int value)
{
    if (permission->canModifyDataDirectly())
    {
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        department->addExpense(id, name, description, limit, value);
    }
    else
    {
        Expense *expense = new Expense(id, department_id, name, description, limit, value, CREATED);
        expenses_list_modified.push_back(expense);
    }
}

void ControlUnit::editExpense(int id, int department_id, QString name, QString description, int limit, int value)
{
    if (permission->canModifyDataDirectly())
    {
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        department->editExpense(id, name, description, limit, value);
    }
    else
    {
        Expense *expense = new Expense(id, department_id, name, description, limit, value, MODIFIED);
        expenses_list_modified.push_back(expense);
    }
}

void ControlUnit::removeExpense(int id, int department_id)
{
    if (permission->canModifyDataDirectly())
    {
        Department *department = Aggregator::getInstance()->getDepartment(department_id);
        department->removeExpense(id);
    }
    else
    {
        Expense *exp_del = Aggregator::getInstance()->getDepartment(department_id)->getExpense(id);
        Expense *expense = new Expense(id, department_id, exp_del->getName(), exp_del->getDescription(),
                                       exp_del->getLimit(), exp_del->getValue(), DELETED);
        expenses_list_modified.push_back(expense);
    }
}

void ControlUnit::addDepartment(int id, QString title)
{
    if (permission->canModifyDataDirectly())
    {
        Aggregator::getInstance()->addDepartment(id, title);
    }
    else
    {
        Department *department = new Department(id, title, CREATED);
        departments_list_modified.push_back(department);
    }
}

void ControlUnit::editDepartment(int id, QString title)
{
    if (permission->canModifyDataDirectly())
    {
        Aggregator::getInstance()->editDepartment(id, title);
    }
    else
    {
        Department *department = new Department(id, title, MODIFIED);
        departments_list_modified.push_back(department);
    }
}

void ControlUnit::removeDepartment(int id)
{
    if (permission->canModifyDataDirectly())
    {
        Aggregator::getInstance()->removeDepartment(id);
    }
    else
    {
        Department *dep_del = Aggregator::getInstance()->getDepartment(id);
        Department *department = new Department(id, dep_del->getTitle(), DELETED);
        departments_list_modified.push_back(department);
    }
}
