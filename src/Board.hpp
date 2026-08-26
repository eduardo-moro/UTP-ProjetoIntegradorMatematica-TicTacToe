#pragma once

#include <array>

enum class Player { None = 0, X = 1, O = 2 };
enum class GameMode { Versus, Easy, Medium, Hard, Neo };
enum class GameState{ Playing, XWon, OWon, Draw };


class Board {
    public: 
        std::array<Player, 9> cells{};

        bool isValidCell(int pos) const;
        
        void reset();
        void setCell(int pos, Player player);
        void clearCell(int pos);
        Player getCell(int pos) const;
};