#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <tuple>

class Database
{
private:
    static Database *instance;
    QSqlDatabase db;
    Database(QString db_path, QString master_key);
public:
    static bool init(QString db_path, QString master_key);
    static Database* getInstance();
    QSqlQuery sendSqlQuery(QString query);
    void close();
};

#endif // DATABASE_H
