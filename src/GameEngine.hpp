#pragma once

#include <QObject>
#include <QVariant>

#include <vector>

#include "AIEngine.hpp"
#include "Board.hpp"

class GameEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList boardState READ boardState NOTIFY boardStateChanged);
    Q_PROPERTY(QString currentPlayer READ currentPlayer NOTIFY currentPlayerChanged);
    Q_PROPERTY(bool boardDisabled READ boardDisabled NOTIFY boardDisabledChanged);
    Q_PROPERTY(int oldestPieceIndex READ oldestPieceIndex NOTIFY boardStateChanged);

    public:
        explicit GameEngine(QObject* parent = nullptr);

        QVariantList boardState() const;
        QString currentPlayer() const;
        bool boardDisabled() const;
        int oldestPieceIndex() const;

        Q_INVOKABLE void makeMove(int pos);
        Q_INVOKABLE void resetGame();
        Q_INVOKABLE void setGameMode(int mode);
        Q_INVOKABLE void newGame();
    signals:
        void boardStateChanged();
        void currentPlayerChanged();
        void gameStatusChanged();
        void playerTurnChanged();
        void modeChanged();
        void winDetected();
        void boardDisabledChanged();
    private:
        void updateGameState();

        void checkWinContition();
        bool checkWin(Player player) const;

        void setBoardDisabled(bool disabled);
        void maybeTriggerBotMove();
        void performBotMove();

        void applyNeoRule(Player player, int pos);

        Board _board;
        Player _currentPlayer = Player::X;

        GameMode _mode = GameMode::Versus;
        GameState _gameState = GameState::Playing;
        bool _boardDisabled = false;

        std::vector<int> _xMoves;
        std::vector<int> _oMoves;

        AIEngine _aiEngine;
};