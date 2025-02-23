#include "GameClient.h"
#include <QDebug>

constexpr int port = 54321;

GameClient::GameClient(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)) {
    connect(socket, &QTcpSocket::connected, this, &GameClient::connected);
    connect(socket, &QTcpSocket::disconnected, this, &GameClient::disconnected);
    connect(socket, &QTcpSocket::readyRead, this, &GameClient::receiveData);
    connect(&connectionCheckTimer, &QTimer::timeout, this, &GameClient::checkServerConnection);
}

void GameClient::connectToServer(const QString& ip) {
    socket->connectToHost(ip, port);
    if (!socket->waitForConnected(2000)) {
        emit connectionError("Ошибка подключения!");
    }
    qDebug() << "[CLIENT] Подключено к серверу!";
    connectionCheckTimer.start(1000);
}

void GameClient::disconnect() {
    socket->disconnectFromHost();
    connectionCheckTimer.stop();
    emit disconnected();
}

void GameClient::receiveData() {
    QString data = QString::fromUtf8(socket->readAll());
    qDebug() << "[CLIENT] Получены данные: " << data;
    emit dataReceived(data);
}

void GameClient::sendData(const QString& data) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(data.toUtf8());
        socket->flush();
    }
}

void GameClient::checkServerConnection() {
    if (socket->state() == QAbstractSocket::UnconnectedState) {
        qDebug() << "[CLIENT] Сервер отключился!";
        emit connectionError("Потеряно соединение!");
    }
}
