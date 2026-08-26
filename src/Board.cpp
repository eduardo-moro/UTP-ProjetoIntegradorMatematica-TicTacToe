#include "Board.hpp"

/// @brief Verifica a validade de uma célula para escrita
/// @param pos posição a ser validada `0 ... 8`
/// @return `False` se posição P não atende `P <=> "" ^ P >= 0 ^ P <= 8`.
bool Board::isValidCell(int pos) const
{
    if (pos < 0) {
        return false;
    }

    if (pos > 8) {
        return false;
    }

    if (cells[pos] != Player::None) {
        return false;
    }

    return true;
}

/// @brief Define o valor de uma célula;
/// @param pos Posição
/// @param player Qual jogador inserir na célula.
void Board::setCell(int pos, Player player)
{
    if (cells[pos] == Player::None)
    {
        cells[pos] = player;
    }
}

/// @brief Busca o valor de uma célula;
/// @param pos posição
/// @return Player
Player Board::getCell(int pos) const
{
    return cells[pos];
}

void Board::reset() {
    cells.fill(Player::None);
}

/// @brief Esvazia uma célula, independentemente do seu valor atual.
/// @param pos posição
void Board::clearCell(int pos)
{
    cells[pos] = Player::None;
}