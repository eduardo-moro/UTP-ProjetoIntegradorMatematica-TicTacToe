#pragma once

#include <array>

enum class Player { None = 0, X = 1, O = 2 };
enum class GameMode { Versus, Neo, Easy, Medium, Hard };
enum class GameState{ Playing, XWon, OWon, Draw };


class Board {
    public: 
        std::array<Player, 9> cells{};

        bool isValidCell(int pos) const;
        
        void reset();
        void setCell(int pos, Player player);
        Player getCell(int pos) const;
};