/**
 * @file weather.h
 * @brief Weather Header
 * @version 0.1
 * @date 2022-11-27
 */
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
    /// @brief Default Constructor
    Weather();
    /// @brief Overloaded Constructor with default unit
    /// @param unit 
    Weather(QString unit);
    /// @brief Overloaded Constructor with default unit and language
    /// @param unit 
    /// @param lang 
    Weather(QString unit, QString lang);

    /// @brief Change language of the API response 
    /// @param lang 
    /// @brief Refer to API: https://openweathermap.org/current#multi
    /** @code 
     * changeLanguage("fr");    //Set description to French
     * changeLanguage("en");    //Set description to English
     * changeLanguage("ja");    //Set description to Japanese
     * @endcode
     */
    void changeLanguage(QString lang);

    /// @brief Change the current unit system
    /// @param unit 
    /// @brief Example:
    /** @code 
     * changeUnit("standard");  //Temp in Kelvin
     * changeUnit("metric");    //Temp in °C
     * changeUnit("imperial");  //Temp in °F
     * @endcode
     */
    void changeUnit(QString unit);

    /// @brief Return the current unit selected
    /// @return "°C" or "°F" or "F"
    /// @brief Refer to API: https://openweathermap.org/current#data
    QString getTempUnit();

    /// @brief Get data from a City Name
    /// @param city
    /// @return status
    /// @brief Status code:
    /// @brief 1 : ok
    /// @brief 0 : Empty response
    /// @brief -1 Error
    int getFromCity(QString city);

    /// @brief Get data from coordinates
    /// @param lat 
    /// @param lon 
    /// @return status
    /// @brief 1 : ok
    /// @brief 0 : Empty response
    /// @brief -1 Error
    int getFromGeo(double lat, double lon);

    /// @todo Convert city name to coordinates
    /// @param city 
    /// @return TODO
    void city2geo(QString city);

    /// @todo Convert coordinates to list of near-by cities
    /// @param lat 
    /// @param lon 
    /// @return TODO
    QString geo2city(double lat, double lon);

private:
    /// @brief Network Manager
    QNetworkAccessManager _networkManager;
    /// @brief API URL
    QString _api = "api.openweathermap.org";
    /// @brief API Token
    QString _token = API_TOKEN;

    /// @brief send a request from URL and decode JSON response
    /// @param url 
    /// @return status
    int sendAndDecode(QUrl url);

    /// @brief https GET from URL
    /// @param url 
    /// @return server response
    QByteArray get(QUrl url);

    QString _unitSystem, _language;


public:
    /// @todo Set to private and add get set methods
    /// @brief Struct to match the JSON format
    /**
    - data
        - coord
            - double lat
            - double lon
        - weather
            - int id
            - QString main
            - QString description
            - QString icon

        - QString base
        - double temp
        - double feels_like
        - double temp_min
        - double temp_max
        - int pressure
        - int humidity
        - int sea_level
        - int grnd_level
        - int visibility
        - wind
            - double speed
            - int deg
            - double gust
        - clouds
            - int all
        - rain
            - double oneHour
            - double threeHours
        - snow
            - double oneHour
            - double threeHours
        - double dt
        - sys
            - int type
            - int id
            - QString message
            - QString country
            - int sunrise
            - int sunset

        - int timezone
        - int id
        - QString name
    */

    struct{
        struct{
            double lat;
            double lon;
        }coord;

        struct{
            int id;
            QString main;
            QString description;
            QString icon;
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
