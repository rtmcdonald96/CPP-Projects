#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include <QtDebug>

#include <QtSql/QSqlError>
#include <QtSql/QSqlDriver>
#include <QtSql/QtSql>
#include <QSqlQuery>
#include <QtSql/QSqlDatabase>
#include "inventory_table.h"

struct Login{
    QString userName;
    QString password;
    int accessToken;
};
class DataManager
{
public:
    DataManager(QString path);
    Login checkLogin(QString un, QString pw);
    QList<Item> getInventory();
    //add Functionality
private:
     QSqlDatabase db;
    //Vectors for data here
};

#endif // DATAMANAGER_H
