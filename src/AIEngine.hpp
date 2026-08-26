
#pragma once

#include "Board.hpp"
#include <vector>
#include <random>

class AIEngine {
public:
    int getEasyMove(const Board& board);
    int getMediumMove(const Board& board);
    int getHardMove(const Board& board);

private:
    int minimax(Board board, int depth, bool isMaximizing, Player aiPlayer);
    int evaluateBoard(const Board& board, Player aiPlayer);
    std::vector<int> getAvailableMoves(const Board& board);
    bool checkWin(const Board& board, Player player);

    std::random_device rd;
    std::mt19937 gen{rd()};
};
