#pragma once

#include <QObject>

class GameLogic : public QObject {
    Q_OBJECT

    Q_PROPERTY(int playerScore READ getPlayerScore NOTIFY scoreUpdated)
    Q_PROPERTY(int opponentScore READ getOpponentScore NOTIFY scoreUpdated)

public:
    explicit GameLogic(QObject *parent = nullptr);

    bool processChoices(const QString& playerChoice, const QString& opponentChoice);
    int getPlayerScore() const { return playerScore; }
    int getOpponentScore() const { return opponentScore; }
    void resetGame();

signals:
    void gameResult(QString result);
    void finalWinner(bool isPlayerWinner);
    void scoreUpdated();

private:
    int playerScore = 0;
    int opponentScore = 0;
};
