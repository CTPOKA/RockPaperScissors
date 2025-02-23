#pragma once

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

class NetworkManager : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool choiceMade READ getChoiceMade NOTIFY choiceUpdated)
    Q_PROPERTY(QString playerChoice READ getPlayerChoice NOTIFY choiceUpdated)
    Q_PROPERTY(QString opponentChoice READ getOpponentChoice NOTIFY choiceUpdated)
    Q_PROPERTY(int playerScore READ getPlayerScore NOTIFY scoreUpdated)
    Q_PROPERTY(int opponentScore READ getOpponentScore NOTIFY scoreUpdated)

public:
    explicit NetworkManager(QObject *parent = nullptr);

    Q_INVOKABLE void startServer();
    Q_INVOKABLE void connectToServer(QString ip);
    Q_INVOKABLE void stopServer();
    Q_INVOKABLE void disconnect();
    Q_INVOKABLE QString getLocalIp();
    Q_INVOKABLE void sendChoice(QString choice);

    Q_INVOKABLE bool getChoiceMade() const { return choiceMade; }
    Q_INVOKABLE QString getPlayerChoice() const { return playerChoice; }
    Q_INVOKABLE QString getOpponentChoice() const { return opponentChoice; }
    Q_INVOKABLE int getPlayerScore() const { return playerScore; }
    Q_INVOKABLE int getOpponentScore() const { return opponentScore; }

signals:
    void playerConnected();
    void connectionFailed();
    void serverStartFailed();
    void gameResult(QString result);
    void choiceUpdated();
    void playerDisconnected();
    void finalWinner(bool isPlayerWinner);
    void scoreUpdated();

private slots:
    void newClientConnection();
    void handleDisconnected();
    void checkServerConnection();
    void receiveChoice();

private:
    QTcpServer *server = nullptr;
    QTcpSocket *clientSocket = nullptr;
    QTimer connectionCheckTimer;

    void checkGameResult();
    void resetGame();

    QString playerChoice;
    QString opponentChoice;
    bool choiceMade = false;
    int playerScore = 0;
    int opponentScore = 0;
};
