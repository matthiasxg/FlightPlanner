/*
 * Author: Matthias Grill
 * Class: 5BHIF
 * Date: 18.02.2019
 */


#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
