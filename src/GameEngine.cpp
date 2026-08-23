#include "GameEngine.hpp"

/// @brief Classe que gerencia o jogo.
/// @param parent 
GameEngine::GameEngine(QObject* parent) : QObject (parent)
{
    _board.reset();
}

QVariantList GameEngine::boardState() const {
    QVariantList result;
    for (int i = 0; i < 9; i++) {
        int cellValue = static_cast<int>(_board.cells[i]);
        result.append(cellValue);
    }

    return result;
}

QString GameEngine::currentPlayer() const
{
    if (_gameState != GameState::Playing) {
        if (_gameState == GameState::XWon) return "X venceu";
        if (_gameState == GameState::OWon) return "O venceu";
        return "Velha";
    }

    return _currentPlayer == Player::X ? "vez de X" : "vez de O";
}

void GameEngine::setGameMode(GameMode mode) {
    resetGame();
    _mode = mode;

    emit modeChanged();
}

void GameEngine::resetGame() {
    _currentPlayer = Player::X;
    _gameState = GameState::Playing;
    _board.reset();

    emit boardStateChanged();    // Status da tabela mudou
    emit currentPlayerChanged(); // Jogador atual mudou
    emit gameStatusChanged();    // Status do jogo pode ter mudado;
    emit playerTurnChanged();    // Turno mudou
}

void GameEngine::newGame() {
    resetGame();
}

/// @brief Valida a vitória E atualiza o _gameStatus.
void GameEngine::checkWinContition() {
    if (checkWin(Player::X)) {
        _gameState = GameState::XWon;
        return;
    }

    if (checkWin(Player::O)) {
        _gameState = GameState::OWon;
        return;
    }

    bool hasEmpty = false;
    for (int i = 0; i < 9;i++) {
        if (_board.cells[i] == Player::None) {
            hasEmpty = true;
            break;
        }
    }
    
    if (hasEmpty == false) {
        _gameState = GameState::Draw;
    }
}


/// @brief Verifica se um jogador específico ganhou
/// @param player 
/// @return 
bool GameEngine::checkWin(Player player) const {
    const int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8}, // Horizontal
        {0,3,6},{1,4,7},{2,5,8}, // Vertical
        {0,4,8},{2,4,6}          // Diagonal
    };

    for (int i = 0; i < 8; i++) {
        if(_board.cells[lines[i][0]] == player && 
           _board.cells[lines[i][1]] == player &&
           _board.cells[lines[i][2]] == player) {
            return true;
        }
    }

    return false;
}

/// @brief Realiza o movimento do jogador
/// @param pos posição
void GameEngine::makeMove(int pos) {
    if (_gameState != GameState::Playing) {
        return; // Não está jogando
    }
    
    if (true != _board.isValidCell(pos)) {
        return; // Jogada inválida
    }

    qDebug() << "pre: " << pos;
    // Muda o valor da célula
    _board.setCell(pos, _currentPlayer);
 
    // Valida se houve vitória
    checkWinContition();

    

    if (_gameState == GameState::Playing) {
        // Troca o Jogador Atual
        _currentPlayer = _currentPlayer == Player::X 
            ? Player::O 
            : Player::X;
    }
    
    qDebug() << "mid: " << pos;
    // Emite um aviso que os seguintes eventos ocorreram:
    emit boardStateChanged();    // Status da tabela mudou
    emit currentPlayerChanged(); // Jogador atual mudou
    emit gameStatusChanged();    // Status do jogo pode ter mudado;
    emit playerTurnChanged();    // Turno mudou
    
    qDebug() << "pos: " << pos;
}

