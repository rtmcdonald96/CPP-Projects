#include "main.h"
#include <QApplication>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    DataManager* DM;
    QString path = "iRobot.db"; // AF path
    DM = new DataManager(path);

    MainWindow* w;
    w = new MainWindow(DM);
    w->show();

    return a.exec();
}
