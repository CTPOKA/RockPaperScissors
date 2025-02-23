#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class GameServer : public QObject {
    Q_OBJECT

public:
    explicit GameServer(QObject *parent = nullptr);
    void sendData(const QString& data);
    void stop();
    void start();

signals:
    void clientConnected();
    void clientDisconnected();
    void dataReceived(const QString& data);
    void serverError(const QString& message);

private slots:
    void newClientConnection();
    void handleClientDisconnected();
    void receiveData();

private:
    QTcpServer *server = nullptr;
    QTcpSocket *clientSocket = nullptr;
};
