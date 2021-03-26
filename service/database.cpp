#include "database.h"

Database* Database::instance = nullptr;

Database::Database(QString db_path, QString master_key)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(db_path);
    db.setPassword(master_key);
}

bool Database::init(QString db_path, QString master_key)
{
    if (instance == nullptr)
    {
        try { instance = new Database(db_path, master_key); }
        catch (std::string err)
        {
            return false;
        }
        return true;
    }
    else
    {
        instance->db.setDatabaseName(db_path);
        instance->db.setPassword(master_key);
        return true;
    }
}

Database* Database::getInstance() { return instance; }

QSqlQuery Database::sendSqlQuery(QString query)
{
    if (!db.isOpen())
        db.open();
    return QSqlQuery(query);
}

void Database::close()
{
    delete this;
}
