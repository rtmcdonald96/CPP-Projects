#ifndef EMPLOYEEVIEW_H
#define EMPLOYEEVIEW_H

#include <QMainWindow>
#include "DataManager.h"
#include "inventory_table.h"
namespace Ui {
class EmployeeView;
}

class EmployeeView : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeView(DataManager *DM, Login user, QWidget *parent = nullptr);
    ~EmployeeView();

    void populateTableView();
private slots:
    void on_Inventory_Button_clicked();

    void on_Sales_Button_clicked();

private:
    Ui::EmployeeView *ui;
    DataManager *dm;
    QSortFilterProxyModel* proxyModel;
    QList<Item> itemList;
    Login currentUser;
};

#endif // EMPLOYEEVIEW_H
