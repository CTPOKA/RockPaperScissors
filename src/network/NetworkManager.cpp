#include "NetworkManager.h"
#include <QNetworkInterface>

NetworkManager::NetworkManager(GameLogic* gameLogic, QObject *parent)
    : gameLogic(gameLogic), QObject(parent) {

    connect(&server, &GameServer::clientConnected, this, &NetworkManager::onPlayerConnected);
    connect(&client, &GameClient::connected, this, &NetworkManager::onPlayerConnected);

    connect(&server, &GameServer::serverError, this, &NetworkManager::onServerError);
    connect(&client, &GameClient::connectionError, this, &NetworkManager::onServerError);

    connect(&server, &GameServer::dataReceived, this, &NetworkManager::handleChoiceReceived);
    connect(&client, &GameClient::dataReceived, this, &NetworkManager::handleChoiceReceived);

    connect(&server, &GameServer::clientDisconnected, this, &NetworkManager::disconnect);
    connect(&client, &GameClient::connectionLost, this, &NetworkManager::disconnect);

    connect(gameLogic, &GameLogic::finalWinner, this, [](bool isPlayerWinner) {
        qDebug() << (isPlayerWinner ? "[GAME] Ты победил!" : "[GAME] Ты проиграл!");
    });
}

void NetworkManager::startServer() {
    isServer = true;
    server.start();
}

void NetworkManager::connectToServer(QString ip) {
    isServer = false;
    client.connectToServer(ip);
}

void NetworkManager::disconnect() {
    if (isServer) {
        server.stop();
    } else {
        client.disconnect();
    }
    nextRound();
    gameLogic->resetGame();
    emit disconnected();
}

void NetworkManager::sendChoice(QString choice) {
    playerChoice = choice;
    choiceMade = true;
    emit choiceUpdated();

    if (isServer) {
        server.sendData(choice);
    } else {
        client.sendData(choice);
    }

    if (!opponentChoice.isEmpty()) {
        if (gameLogic->processChoices(playerChoice, opponentChoice)) {
            nextRound();
        }
    }
}

void NetworkManager::handleChoiceReceived(const QString& choice) {
    opponentChoice = choice;
    if (!playerChoice.isEmpty()) {
        if (gameLogic->processChoices(playerChoice, opponentChoice)) {
            nextRound();
        }
    }
}

void NetworkManager::nextRound() {
    playerChoice.clear();
    opponentChoice.clear();
    choiceMade = false;
    emit choiceUpdated();
}

QString NetworkManager::getLocalIp() const {
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &addr : addresses) {
        if (addr.protocol() == QAbstractSocket::IPv4Protocol && addr != QHostAddress::LocalHost) {
            return addr.toString();
        }
    }
    return "Не удалось определить IP";
}

void NetworkManager::onPlayerConnected() {
    emit playerConnected();
}

void NetworkManager::onServerError(const QString& message) {
    emit serverError(message);
}
