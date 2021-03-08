#include "inventory_table.h"

Inventory_Table::Inventory_Table(QList<Item> current_inv,QObject *parent)
    : QAbstractTableModel(parent)
{
    this->inv.inventory_list = current_inv;
}

QVariant Inventory_Table::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return tr("Item ID");
            case 1:
                return tr("Item Name");
            case 2:
                return tr("Item Description");
            case 3:
                return tr("Purchase Price");
            case 4:
                return tr("Sale Price");
            case 5:
                return tr("Markup(%)");
            default:
                return QVariant();
            }
        }
        return section + 1;
}

int Inventory_Table::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return inv.inventory_list.size();
}

int Inventory_Table::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return Item::COLUMN_COUNT;
}

QVariant Inventory_Table::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
            return QVariant();
        if (index.row() >= inv.inventory_list.size() || index.row() < 0)
            return QVariant();
    if (role == Qt::DisplayRole) {
        const Item& item = inv.inventory_list.at(index.row());

        switch(index.column()){
        case 0:
            return item.item_id;
        case 1:
            return item.item_name;
        case 2:
            return item.item_description;
        case 3:
            return item.item_cost;
        case 4:
            return item.item_sale;
        case 5:
            return item.item_markup;
        default:
            return QVariant();
        }
    }else if (role == Qt::TextAlignmentRole){
        return Qt::AlignCenter;
    }
    return QVariant();
}
