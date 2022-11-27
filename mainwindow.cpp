/**
 * @file mainwindow.cpp
 * @brief MainWindow Source
 * @version 0.1
 * @date 2022-11-27
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow), weather("metric","en"){
    ui->setupUi(this);
    weather.getFromCity("Paris");
    setUI();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::slotSearch(){
    QString input = ui->lineEditSearch->text();
    if(input.isEmpty() || input.isNull())
        return;

    if(weather.getFromCity(input)){
        setUI();
    }
}

void MainWindow::setUI(){
    ui->label_CityName->setText(weather.data.name + " " + weather.data.sys.country);
    ui->label_Temp->setText(QString::number(weather.data.temp) + weather.getTempUnit());

    QString filePath = ":/resources/img/" + weather.data.weather.icon + ".png";
    ui->label_Icon->setPixmap(QPixmap(filePath));

    ui->label_Description->setText(weather.data.weather.description);
    ui->label_FeelsLike->setText("Feels Like: " + QString::number(weather.data.feels_like) + weather.getTempUnit());
    ui->label_Wind->setText("Wind speed: " + QString::number(weather.data.wind.speed) + "km/h");
    ui->label_Humidity->setText("Humidity: " + QString::number(weather.data.humidity) + "%");

    ui->label_minTemp->setText("min: "+QString::number(weather.data.temp_min) + weather.getTempUnit());
    ui->label_maxTemp->setText("max: "+QString::number(weather.data.temp_max) + weather.getTempUnit());

    int hour = QDateTime::fromSecsSinceEpoch(weather.data.sys.sunset).time().hour();
    double minute = QDateTime::fromSecsSinceEpoch(weather.data.sys.sunset).time().minute();
    QString str = QString::number(hour) + ":" + QString::number(minute);
    qDebug() << str;
    ui->label_Sunset->setText("Sunset(utc): "+str);

    hour = QDateTime::fromSecsSinceEpoch(weather.data.sys.sunrise).time().hour();
    minute = QDateTime::fromSecsSinceEpoch(weather.data.sys.sunrise).time().minute();
    str = QString::number(hour) + ":" + QString::number(minute);
    qDebug() << str;
    ui->label_Sunrise->setText("Sunrise(utc): "+str);
}
