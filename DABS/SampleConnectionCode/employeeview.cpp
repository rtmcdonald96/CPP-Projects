#include "employeeview.h"
#include "ui_employeeview.h"

EmployeeView::EmployeeView(DataManager *DM, Login user, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::EmployeeView)
{
    dm = DM;
    ui->setupUi(this);
    QString uInfo = ("Welcome, " + user.userName + "\nAccess Level: " + QString::number(user.accessToken));
    ui->eInfo->setText(uInfo);
    this->populateTableView();
}

EmployeeView::~EmployeeView()
{
    delete ui;
}
void EmployeeView::populateTableView(){
    this->itemList = dm->getInventory();
    Inventory_Table* model = new Inventory_Table(this->itemList);
    this->proxyModel = new QSortFilterProxyModel(this);
    proxyModel->setSourceModel(model);
    ui->tableView->setModel(proxyModel);
    ui->tableView->setSortingEnabled(true);

}
void EmployeeView::on_Inventory_Button_clicked()
{

}

void EmployeeView::on_Sales_Button_clicked()
{

}
