#ifndef INVENTORY_TABLE_H
#define INVENTORY_TABLE_H

#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

struct Item{
    const static int COLUMN_COUNT = 6;
    Item() {}
    explicit Item(int item_id, QString item_name, QString item_description, double item_cost, double item_sale, double item_markup){
        this->item_id = item_id;
        this->item_name = item_name;
        this->item_description = item_description;
        this->item_cost = item_cost;
        this->item_sale = item_sale;
        this->item_markup = item_markup;
    }

    int item_id;
    QString item_name;
    QString item_description;
    double item_cost;
    double item_sale;
    double item_markup;
};

struct Inventory{
    QList<Item> inventory_list;
};

class Inventory_Table : public QAbstractTableModel
{
    Q_OBJECT

public:
    Inventory_Table(QList<Item> current_inv, QObject *parent = nullptr);

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
    Inventory inv;

};

#endif // INVENTORY_TABLE_H
