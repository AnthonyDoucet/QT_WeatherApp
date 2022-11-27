/**
 * @file weather.cpp
 * @brief Weather Source
 * @version 0.1
 * @date 2022-11-27
 */
#include "weather.h"

Weather::Weather(){}
Weather::Weather(QString unit): _unitSystem(unit){}
Weather::Weather(QString unit, QString lang): _unitSystem(unit), _language(lang){}

//https://openweathermap.org/current#data
void Weather::changeLanguage(QString lang){ _language = lang; }
void Weather::changeUnit(QString unit){ _unitSystem = unit; }
QString Weather::getTempUnit(){
    if(_unitSystem == "metric"){
        return "°C";
    }
    else if(_unitSystem == "imperial"){
        return "°F";
    }
    return "K";
}



int Weather::getFromCity(QString city){
    //city2geo(city);
    QUrl url = QString("https://" + _api + "/data/2.5/weather"
                       + "?q=" + city
                       + "&units=" + _unitSystem
                       + "&lang=" + _language
                       + "&appid=" + _token);
    qDebug() << "[URL] " << url;
    return sendAndDecode(url);
    return 0;
}

//https://api.openweathermap.org/data/2.5/weather?lat={lat}&lon={lon}&appid={API key}
int Weather::getFromGeo(double lat, double lon){
    QUrl url = QString("https://" + _api + "/data/2.5/weather"
                       + "?lat=" + QString::number(lat)
                       + "&lon=" + QString::number(lon)
                       + "&units=" + _unitSystem
                       + "&lang=" + _language
                       + "&appid=" + _token);
    qDebug() << "[URL] " << url;
    return sendAndDecode(url);
}

int Weather::sendAndDecode(QUrl url){
    QJsonObject jroot = QJsonDocument::fromJson(get(url)).object();

    if(jroot.isEmpty())
        return 0;

    //qDebug() << "[JSON]" << jroot;

    int cod = jroot["cod"].toInt();
    switch(cod){
        case 200: break;
        case 400: return -1;
        default: return -1;
    }

    QJsonObject jcoord = jroot["coord"].toObject();
        data.coord.lat = jcoord["lat"].toDouble();
        data.coord.lon = jcoord["lon"].toDouble();

    QJsonObject jweather = jroot["weather"].toArray().at(0).toObject();
        data.weather.id = jweather["id"].toInt();
        data.weather.description = jweather["description"].toString();
        data.weather.icon = jweather["icon"].toString();

    QJsonObject jmain = jroot["main"].toObject();
        data.temp = jmain["temp"].toDouble();
        data.feels_like = jmain["feels_like"].toDouble();
        data.temp_min = jmain["temp_min"].toDouble();
        data.temp_max = jmain["temp_max"].toDouble();
        data.pressure = jmain["pressure"].toInt();
        data.humidity = jmain["humidity"].toInt();
        data.sea_level = jmain["sea_level"].toInt();
        data.grnd_level = jmain["grnd_level"].toInt();

    QJsonObject jwind = jroot["wind"].toObject();
        data.wind.speed = jwind["speed"].toDouble();
        data.wind.deg = jwind["deg"].toDouble();
        data.wind.gust = jwind["gust"].toDouble();

    QJsonObject jclouds = jroot["clouds"].toObject();
        data.clouds.all = jclouds["all"].toInt();

    QJsonObject jrain = jroot["rain"].toObject();
        data.rain.oneHour = jrain["1h"].toDouble();
        data.rain.threeHours = jrain["3h"].toDouble();

    QJsonObject jsnow = jroot["snow"].toObject();
        data.snow.oneHour = jrain["1h"].toDouble();
        data.snow.threeHours = jrain["3h"].toDouble();

    QJsonObject jsys = jroot["sys"].toObject();
        data.sys.type = jsys["type"].toInt();
        data.sys.id = jsys["id"].toInt();
        data.sys.message = jsys["message"].toString();
        data.sys.country = jsys["country"].toString();
        data.sys.sunrise = jsys["sunrise"].toInt();
        data.sys.sunset = jsys["sunset"].toInt();


    data.base = jroot["base"].toString();
    data.visibility = jroot["visibility"].toInt();
    data.dt = jroot["dt"].toDouble();
    data.timezone = jroot["timezone"].toInt();
    data.id = jroot["id"].toInt();
    data.name = jroot["name"].toString();

    return 1;
}

QByteArray Weather::get(QUrl url){
    //config url
    QNetworkRequest request(url);

    //https
    QSslConfiguration config = QSslConfiguration::defaultConfiguration();
    config.setProtocol(QSsl::TlsV1_2);
    request.setSslConfiguration(config);

    //get
    QNetworkReply *reply = _networkManager.get(request);
    while (!reply->isFinished()){
        qApp->processEvents();
    }

    //response
    QByteArray read = reply->readAll();
    reply->close();
    reply->deleteLater();
    return read;
}

//http://api.openweathermap.org/geo/1.0/direct?q={city name},{state code},{country code}&limit={limit}&appid={API key}
void Weather::city2geo(QString city){
    QUrl url = QString("https://" + _api + "/geo/1.0/direct?q=" + city + "&appid=" + _token);
    qDebug() << "[URL] " << url;
    QJsonObject jroot = QJsonDocument::fromJson(get(url)).object();
    qDebug() << jroot;
}

QString Weather::geo2city(double lat, double lon){
    return "";
}
