/**
 * @file mainwindow.h
 * @brief MainWindow Header
 * @version 0.1
 * @date 2022-11-27
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QDateTime>
#include <weather.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /// @brief Default Constructor
    /// @param parent 
    MainWindow(QWidget *parent = nullptr);
    /// @brief Default Destructor
    ~MainWindow();

private slots:
    /// @brief Slot to search from a city name
    void slotSearch();

private:
    /// @brief ui
    Ui::MainWindow *ui;
    /// @brief Weather object
    Weather weather;
    /// @brief Update the UI value from weather data
    void setUI();
};
#endif // MAINWINDOW_H
