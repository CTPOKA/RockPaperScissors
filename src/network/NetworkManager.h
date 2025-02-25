#pragma once

#include <QObject>
#include "GameServer.h"
#include "GameClient.h"
#include "GameLogic.h"

class NetworkManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool choiceMade READ getChoiceMade NOTIFY choiceUpdated)
    Q_PROPERTY(QString playerChoice READ getPlayerChoice NOTIFY choiceUpdated)
    Q_PROPERTY(QString opponentChoice READ getOpponentChoice NOTIFY choiceUpdated)


public:
    explicit NetworkManager(GameLogic* gameLogic, QObject *parent = nullptr);

    Q_INVOKABLE void startServer();
    Q_INVOKABLE void connectToServer(QString ip);
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE void sendChoice(QString choice);
    Q_INVOKABLE QString getLocalIp() const;

    int getChoiceMade() const { return choiceMade; }
    QString getPlayerChoice() const { return playerChoice; }
    QString getOpponentChoice() const { return opponentChoice; }

signals:
    void serverError(QString message);
    void disconnected();
    void playerConnected();
    void choiceUpdated();

private slots:
    void handleChoiceReceived(const QString& choice);

private:
    void nextRound();
    void onPlayerConnected();
    void onServerError(const QString& message);

    GameServer server;
    GameClient client;
    GameLogic *gameLogic;

    QString playerChoice;
    QString opponentChoice;
    bool choiceMade = false;
    bool isServer = false;
};
