#pragma once

#include <QObject>
#include <QVariant>

#include "Board.h" 

class GameEngine : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariantList boardState READ boardState NOTIFY boardStateChanged);
    Q_PROPERTY(QString currentPlayer READ currentPlayer NOTIFY currentPlayerChanged);

    public: 
        explicit GameEngine(QObject* parent = nullptr);
        
        QVariantList boardState() const;
        QString currentPlayer() const;

        Q_INVOKABLE void makeMove(int pos);
        Q_INVOKABLE void resetGame();
        Q_INVOKABLE void setGameMode(GameMode mode);
        Q_INVOKABLE void newGame();
    signals: 
        void boardStateChanged();
        void currentPlayerChanged();
        void gameStatusChanged();
        void playerTurnChanged();
        void modeChanged();
        void winDetected();
    private: 
        void updateGameState();

        void checkWinContition();
        bool checkWin(Player player) const;

        Board _board;
        Player _currentPlayer = Player::X;

        GameMode _mode = GameMode::Versus;
        GameState _gameState = GameState::Playing;
};