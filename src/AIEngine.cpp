
#include "AIEngine.hpp"
#include <algorithm>
#include <limits>

int AIEngine::getEasyMove(const Board& board)
{
    auto available = getAvailableMoves(board);
    if (available.empty()) return -1;

    std::uniform_int_distribution<> dis(0, available.size() - 1);
    return available[dis(gen)];
}

int AIEngine::getMediumMove(const Board& board)
{
    auto available = getAvailableMoves(board);
    if (available.empty()) return -1;

    std::uniform_int_distribution<> random(0, 1);
    // 50% random, 50% smart
    if (random(gen) % 2 == 0) {
        std::uniform_int_distribution<> dis(0, available.size() - 1);
        return available[dis(gen)];
    }

    // Try to win
    for (int move : available) {
        Board temp = board;
        temp.cells[move] = Player::O;
        if (checkWin(temp, Player::O)) {
            return move;
        }
    }

    // Try to block
    for (int move : available) {
        Board temp = board;
        temp.cells[move] = Player::X;
        if (checkWin(temp, Player::X)) {
            return move;
        }
    }

    // Random
    std::uniform_int_distribution<> dis(0, available.size() - 1);
    return available[dis(gen)];
}

int AIEngine::getHardMove(const Board& board)
{
    auto available = getAvailableMoves(board);
    if (available.empty()) return -1;

    int bestMove = available[0];
    int bestScore = std::numeric_limits<int>::lowest();

    for (int move : available) {
        Board temp = board;
        temp.cells[move] = Player::O;
        int score = minimax(temp, 0, false, Player::O);
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

int AIEngine::minimax(Board board, int depth, bool isMaximizing, Player aiPlayer)
{
    if (checkWin(board, Player::O)) return 10 - depth;
    if (checkWin(board, Player::X)) return depth - 10;

    auto available = getAvailableMoves(board);
    if (available.empty()) return 0;

    if (isMaximizing) {
        int maxScore = std::numeric_limits<int>::lowest();
        for (int move : available) {
            board.cells[move] = Player::O;
            int score = minimax(board, depth + 1, false, aiPlayer);
            maxScore = std::max(score, maxScore);
            board.cells[move] = Player::None;
        }
        return maxScore;
    } else {
        int minScore = std::numeric_limits<int>::max();
        for (int move : available) {
            board.cells[move] = Player::X;
            int score = minimax(board, depth + 1, true, aiPlayer);
            minScore = std::min(score, minScore);
            board.cells[move] = Player::None;
        }
        return minScore;
    }
}

int AIEngine::evaluateBoard(const Board& board, Player aiPlayer)
{
    if (checkWin(board, aiPlayer)) return 10;
    if (checkWin(board, aiPlayer == Player::X ? Player::O : Player::X)) return -10;
    return 0;
}

std::vector<int> AIEngine::getAvailableMoves(const Board& board)
{
    std::vector<int> moves;
    for (int i = 0; i < 9; ++i) {
        if (board.cells[i] == Player::None) {
            moves.push_back(i);
        }
    }
    return moves;
}

bool AIEngine::checkWin(const Board& board, Player player)
{
    const int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
        {0, 4, 8}, {2, 4, 6}
    };

    for (auto& line : lines) {
        if (board.cells[line[0]] == player &&
            board.cells[line[1]] == player &&
            board.cells[line[2]] == player) {
            return true;
        }
    }
    return false;
}
