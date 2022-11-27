/**
 * @file main.cpp
 * @brief Entrypoint
 * @version 0.1
 * @date 2022-11-27
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
