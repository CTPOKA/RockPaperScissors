#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "networkmanager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    NetworkManager networkManager;
    engine.rootContext()->setContextProperty("networkManager", &networkManager);

    engine.loadFromModule("RockPaperScissors", "Main");

    return app.exec();
}
