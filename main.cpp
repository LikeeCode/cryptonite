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

    // Start the Qt event loop and return the exit code when the app closes
    return app.exec();
}
