//
// Created by ice_city on 1/27/17.
//
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc,argv);
    MainWindow w;
    w.show();
    return a.exec();
}
