#include "networkmanager.h"
#include <QDebug>
#include <QNetworkInterface>

constexpr int port = 54321;

NetworkManager::NetworkManager(QObject *parent) : QObject(parent), choiceMade(false) {
    connect(&connectionCheckTimer, SIGNAL(timeout()), this, SLOT(checkServerConnection()));
}

void NetworkManager::startServer() {
    server = new QTcpServer(this);

    if (!server->listen(QHostAddress::Any, port)) {
        qDebug() << "[SERVER] Ошибка запуска!";
        emit serverStartFailed();
        return;
    }

    connect(server, SIGNAL(newConnection()), this, SLOT(newClientConnection()));

    qDebug() << "[SERVER] Запущен. Ожидание подключения...";
}

void NetworkManager::connectToServer(QString ip) {
    clientSocket = new QTcpSocket(this);
    clientSocket->connectToHost(ip, port);

    resetGame();

    if (!clientSocket->waitForConnected(3000)) {
        qDebug() << "[CLIENT] Ошибка подключения!";
        emit connectionFailed();
        return;
    }

    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(receiveChoice()));

    qDebug() << "[CLIENT] Подключено к серверу!";
    emit playerConnected();

    connectionCheckTimer.start(2000);
}

void NetworkManager::newClientConnection() {
    QTcpSocket *newClient = server->nextPendingConnection();
    if (!newClient) return;

    if (clientSocket) {
        qDebug() << "[SERVER] Подключение отклонено: уже есть игрок.";
        newClient->disconnectFromHost();
        newClient->deleteLater();
        return;
    }

    clientSocket = newClient;

    resetGame();

    connect(clientSocket, SIGNAL(disconnected()), this, SLOT(handleDisconnected()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(receiveChoice()));

    qDebug() << "[SERVER] Игрок подключился!";
    emit playerConnected();
}

void NetworkManager::sendChoice(QString choice) {
    if (choiceMade) return;

    choiceMade = true;
    playerChoice = choice;
    emit choiceUpdated();

    QByteArray data = choice.toUtf8();

    if (clientSocket) {
        clientSocket->write(data);
        clientSocket->flush();
    } else if (server) {
        for (QTcpSocket *socket : server->findChildren<QTcpSocket *>()) {
            socket->write(data);
            socket->flush();
        }
    }

    if (!opponentChoice.isEmpty()) {
        checkGameResult();
    }
}

void NetworkManager::handleDisconnected() {
    qDebug() << "[NETWORK] Игрок отключился!";
    clientSocket->deleteLater();
    clientSocket = nullptr;
    emit playerDisconnected();
}

QString NetworkManager::getLocalIp() {
    QList<QHostAddress> addresses = QNetworkInterface::allAddresses();
    for (const QHostAddress &addr : addresses) {
        if (addr.protocol() == QAbstractSocket::IPv4Protocol && addr != QHostAddress::LocalHost) {
            return addr.toString();
        }
    }
    return "Не удалось определить IP";
}

void NetworkManager::stopServer() {
    if (server) {
        qDebug() << "[SERVER] Остановка...";
        server->close();
        delete server;
        server = nullptr;
    }
    if (clientSocket) {
        clientSocket->deleteLater();
        clientSocket = nullptr;
    }
}

void NetworkManager::disconnect() {
    if (server) {
        stopServer();
    }
    else if (clientSocket) {
        qDebug() << "[CLIENT] Отключение от сервера...";
        clientSocket->disconnectFromHost();
        delete clientSocket;
        clientSocket = nullptr;
    }
}

void NetworkManager::checkServerConnection() {
    if (clientSocket && clientSocket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "[CLIENT] Сервер отключился!";
        connectionCheckTimer.stop();
        emit playerDisconnected();
    }
}

void NetworkManager::checkGameResult() {
    QString result;

    if (playerChoice == opponentChoice) {
        result = "Ничья!";
    } else if ((playerChoice == "rock" && opponentChoice == "scissors") ||
               (playerChoice == "scissors" && opponentChoice == "paper") ||
               (playerChoice == "paper" && opponentChoice == "rock")) {
        result = "Вы победили!";
        playerScore++;
    } else {
        result = "Вы проиграли!";
        opponentScore++;
    }
    emit scoreUpdated();

    emit gameResult(result);

    if (playerScore == 5) {
        emit finalWinner(true);
        resetGame();
    } else if (opponentScore == 5) {
        emit finalWinner(false);
        resetGame();
    } else {
        choiceMade = false;
        playerChoice = "";
        opponentChoice = "";
        emit choiceUpdated();
    }
}

void NetworkManager::resetGame() {
    choiceMade = false;
    playerChoice = "";
    opponentChoice = "";
    playerScore = 0;
    opponentScore = 0;
}

void NetworkManager::receiveChoice() {
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
    if (!socket) return;

    QByteArray data = socket->readAll();
    QString choice = QString::fromUtf8(data);

    qDebug() << "[NETWORK] Получен выбор соперника: " << choice;

    opponentChoice = choice;

    if (!playerChoice.isEmpty()) {
        checkGameResult();
    }
}
