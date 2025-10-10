#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "rest-api/BinanceAPI.h"
#include "rest-api/GeneralDataParser.h"

int main(int argc, char *argv[])
{
    // Create the core application object
    QGuiApplication app(argc, argv);

    // Create the engine that will run the QML code
    QQmlApplicationEngine engine;

    // Define the URL to our main QML file.
    // The "qrc:/" scheme means we are loading it from the compiled-in resources.
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    // Load the QML file at the specified URL
    engine.load(url);

    // Load Binance API
    Binance::BinanceAPI *binanceApi = new Binance::BinanceAPI(&app, true); // true for test network
    // QObject::connect(binanceApi, &Binance::BinanceAPI::apiKeysFileError, []()
    //                  { qDebug() << "API Keys file error!\n"; });
    // QObject::connect(binanceApi, &Binance::BinanceAPI::apiError, [](const QString &error)
    //                  { qDebug() << "API error:\n"
    //                             << error; });
    // QObject::connect(binanceApi, &Binance::BinanceAPI::pingResponse, [](const QJsonDocument &data)
    //                  { qDebug() << "Ping response:\n"
    //                             << data.toJson(QJsonDocument::Compact); });
    // QObject::connect(binanceApi, &Binance::BinanceAPI::timeResponse, [](const QJsonDocument &data)
    //                  { qDebug() << "Time response:\n"
    //                             << data.toJson(QJsonDocument::Compact); });
    // QObject::connect(binanceApi, &Binance::BinanceAPI::exchangeInfoResponse, [](const QJsonDocument &data)
    //                  {
    //                     qDebug() << "Exchange Info response:\n" << data.toJson(QJsonDocument::Compact);
    //                     auto exchangeInfo = Binance::GeneralDataParser::parseExchangeInfo(data);
    //                 });

    // Example usage: Call some API methods
    // binanceApi->ping();
    // binanceApi->time();
    // binanceApi->exchangeInfo();

    // Start the Qt event loop and return the exit code when the app closes
    return app.exec();
}
