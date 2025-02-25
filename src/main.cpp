#include <QGuiApplication>
#include <QIcon>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "GameLogic.h"
#include "NetworkManager.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    app.setWindowIcon(QIcon(":/images/scissors"));

    GameLogic gameLogic;
    NetworkManager networkManager(&gameLogic);

    engine.rootContext()->setContextProperty("gameLogic", &gameLogic);
    engine.rootContext()->setContextProperty("networkManager", &networkManager);

    engine.loadFromModule("RockPaperScissors", "Main");

    return app.exec();
}
