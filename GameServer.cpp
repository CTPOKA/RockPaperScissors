#include "GameServer.h"
#include <QDebug>

constexpr int port = 54321;

GameServer::GameServer(QObject *parent) : QObject(parent), server(new QTcpServer(this)) {
    connect(server, &QTcpServer::newConnection, this, &GameServer::newClientConnection);
}

void GameServer::start() {
    if (!server->listen(QHostAddress::Any, port)) {
        emit serverError("Ошибка запуска сервера");
        return;
    }
    qDebug() << "[SERVER] Сервер запущен на порту" << port;
}

void GameServer::stop() {
    if (server->isListening()) {
        server->close();
        if (clientSocket)
            clientSocket->disconnectFromHost();
        qDebug() << "[SERVER] Сервер остановлен";
    }
}

void GameServer::newClientConnection() {
    if (clientSocket) {
        qDebug() << "[SERVER] Отклонено новое подключение: уже есть игрок.";
        server->nextPendingConnection()->disconnectFromHost();
        return;
    }

    clientSocket = server->nextPendingConnection();
    connect(clientSocket, &QTcpSocket::disconnected, this, &GameServer::handleClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &GameServer::receiveData);

    qDebug() << "[SERVER] Игрок подключился!";
    emit clientConnected();
}

void GameServer::handleClientDisconnected() {
    qDebug() << "[SERVER] Игрок отключился!";
    clientSocket->deleteLater();
    clientSocket = nullptr;
    emit clientDisconnected();
}

void GameServer::receiveData() {
    if (!clientSocket) return;
    QString data = QString::fromUtf8(clientSocket->readAll());
    qDebug() << "[SERVER] Получены данные: " << data;
    emit dataReceived(data);
}

void GameServer::sendData(const QString& data) {
    if (clientSocket) {
        clientSocket->write(data.toUtf8());
        clientSocket->flush();
    }
}
