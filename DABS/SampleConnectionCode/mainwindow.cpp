#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(DataManager *DM, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    dm = DM;
    ui->setupUi(this);
    ui->logo->setStyleSheet("background-image: url(:/new/images/rc/dabs2.png)");

}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_LoginButton_clicked()
{
    Login attempt;
    QString usernameentered = ui->lineEdit_username->text();
    QString passwordentered = ui->lineEdit_password->text();
    attempt = dm->checkLogin(usernameentered,passwordentered);

    if(attempt.accessToken == 1){
        attempt.userName = usernameentered;
        attempt.password = passwordentered;
        EmployeeView* ev = new EmployeeView(dm, attempt);
        ev->show();
        this->hide();
        qDebug() << attempt.userName << attempt.password << attempt.accessToken;
    }
    //int success = login(usernameentered, passwordentered);
    /*if(success == 0){
     *  CustomerView* custView = new CustomerView;
     *  custView->open();
     *  this->close();
     * } else {
     *   EmployeeView* empView = new EmployeeView;
     *   empView->open();
     *   this->close();
     * }
     */
}
