#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), weather("metric","fr"){
    ui->setupUi(this);

    weather.getFromGeo(0.0,10.99);
    qDebug() << weather.data.temp;
    qDebug() << weather.data.temp_min;
    qDebug() << weather.data.temp_max;
    qDebug() << weather.data.weather.description;

    qDebug() << "---------------";
    weather.getFromCity("Paris");
    qDebug() << weather.data.temp;
    qDebug() << weather.data.temp_min;
    qDebug() << weather.data.temp_max;
    qDebug() << weather.data.weather.description;

    qDebug() << "---------------";
    weather.getFromCity("London");
    qDebug() << weather.data.temp;
    qDebug() << weather.data.temp_min;
    qDebug() << weather.data.temp_max;
    qDebug() << weather.data.weather.description;
}

MainWindow::~MainWindow(){
    delete ui;
}

