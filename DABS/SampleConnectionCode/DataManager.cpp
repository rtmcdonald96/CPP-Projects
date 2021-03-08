#include "DataManager.h"

DataManager::DataManager(QString path)
{
    QString connectionString = ("DRIVER={ODBC Driver 13 for SQL Server};Server=tcp:dabsdb.database.windows.net,1433;Database=DABS_DB;Uid=cpsc362;Pwd=CSUFdabs!;Encrypt=yes;TrustServerCertificate=no;Connection Timeout=30;");
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");


    db.setDatabaseName(connectionString);
    if(!db.open()){
        db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(path);
        if(!db.open())
        {
            qDebug() << "Error: could not connect to Database";
        } else {
                qDebug() << "Database: connection is A-okay";
        }
    } else {
        qDebug() << "Connected to Azure";
    }

}

Login DataManager::checkLogin(QString un, QString pw){
    QSqlQuery checkQuery;
        Login attempt;
        checkQuery.prepare("SELECT accessToken FROM logins WHERE Username = :un AND Password = :pw");
        checkQuery.bindValue(":un", un);
        checkQuery.bindValue(":pw", pw);

        if(checkQuery.exec()){
            while(checkQuery.next()){
                attempt.userName = un;
                attempt.password = pw;
                attempt.accessToken = checkQuery.value(0).toInt();
            }

        }
        return attempt;
}
QList<Item> DataManager::getInventory(){
    QSqlQuery query;
    QList<Item> inv;
    if(query.exec("SELECT Item_ID, Item_Name, Item_Description, Purchase_Price, Selling_Price, Percent_Markup FROM item")){
        if(query.first()){
            while(query.isValid()){
                int itemID = query.value(0).toInt();
                QString itemName = query.value(1).toString();
                QString itemDescription = query.value(2).toString();
                double itemCost = query.value(3).toDouble();
                double itemSale = query.value(4).toDouble();
                double itemMarkup = query.value(5).toDouble();
                Item tempItem = Item(itemID,itemName,itemDescription,itemCost,itemSale,itemMarkup);
                inv.append(tempItem);
                query.next();
            }
        }
    } else {
        qDebug() << "SQL Error: " << query.lastError().text();
    }
    return inv;
}
