#ifndef WEATHER_H
#define WEATHER_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QtGui>
#include <token.h>

class Weather
{
public:
    Weather();
    Weather(QString unit);
    Weather(QString unit, QString lang);
    void changeLanguage(QString lang);
    void changeUnit(QString unit);

    int getFromCity(QString city);
    int getFromGeo(double lat, double lon);

private:
    /// @brief Network Manager
    QNetworkAccessManager _networkManager;
    /// @brief API URL
    QString _api = "api.openweathermap.org";
    /// @brief API Token
    QString _token = API_TOKEN;

    int sendAndDecode(QUrl url);
    QByteArray get(QUrl url);

private:
    QString _unitSystem, _language;

    void city2geo(QString city);
    QString geo2city(double lat, double lon);


public:
    //DATA
    struct{
        struct{
            double lat;
            double lon;
        }coord;

        struct{
            int id;
            QString main;
            QString description;
            int icon;
        }weather;

        QString base;

        double temp;
        double feels_like;
        double temp_min;
        double temp_max;
        int pressure;
        int humidity;
        int sea_level;
        int grnd_level;

        int visibility;

        struct{
            double speed;
            int deg;
            double gust;
        }wind;

        struct{
            int all;
        }clouds;

        struct{
            double oneHour;
            double threeHours;
        }rain;

        struct{
            double oneHour;
            double threeHours;
        }snow;

        double dt;

        struct{
            int type;
            int id;
            QString message;
            QString country;
            int sunrise;
            int sunset;
        }sys;

        int timezone;
        int id;
        QString name;
    }data;
};



#endif // WEATHER_H
