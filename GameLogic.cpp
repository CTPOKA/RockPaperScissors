#include "GameLogic.h"
#include <QDebug>

GameLogic::GameLogic(QObject *parent) : QObject(parent) {}

bool GameLogic::processChoices(const QString& playerChoice, const QString& opponentChoice) {
    constexpr int maxScore = 5;
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

    if (playerScore == maxScore) {
        emit finalWinner(true);
        return false;
    } else if (opponentScore == maxScore) {
        emit finalWinner(false);
        return false;
    }
    return true;
}

void GameLogic::resetGame() {
    playerScore = 0;
    opponentScore = 0;
}
