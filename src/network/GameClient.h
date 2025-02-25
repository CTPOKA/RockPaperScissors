#pragma once

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class GameClient : public QObject {
    Q_OBJECT

public:
    explicit GameClient(QObject *parent = nullptr);
    void disconnect();
    void sendData(const QString& data);
    void connectToServer(const QString& ip);

signals:
    void connected();
    void disconnected();
    void dataReceived(const QString& data);
    void connectionError(const QString& error);
    void connectionLost();

private slots:
    void receiveData();

private:
    void checkServerConnection();

    QTcpSocket *socket = nullptr;
    QTimer connectionCheckTimer;
};
