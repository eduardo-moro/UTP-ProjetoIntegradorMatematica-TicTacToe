#include "GameEngine.hpp"

#include <QTimer>

namespace {
    constexpr int BOT_THINK_DELAY_MS = 500;
}

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

bool GameEngine::boardDisabled() const
{
    return _boardDisabled;
}

/// @brief Posição da peça mais antiga do jogador da vez (modo Neo), a ser removida na próxima jogada dele.
/// @return posição da peça, ou -1 se não aplicável.
int GameEngine::oldestPieceIndex() const
{
    if (_mode != GameMode::Neo || _gameState != GameState::Playing) {
        return -1;
    }

    const std::vector<int>& moves = _currentPlayer == Player::X ? _xMoves : _oMoves;
    if (moves.size() < 3) {
        return -1;
    }

    return moves.front();
}

void GameEngine::setGameMode(int mode) {
    resetGame();
    _mode = static_cast<GameMode>(mode);

    emit modeChanged();
}

void GameEngine::setBoardDisabled(bool disabled) {
    if (_boardDisabled == disabled) {
        return;
    }

    _boardDisabled = disabled;
    emit boardDisabledChanged();
}

void GameEngine::resetGame() {
    _currentPlayer = Player::X;
    _gameState = GameState::Playing;
    _board.reset();
    setBoardDisabled(false);
    _xMoves.clear();
    _oMoves.clear();

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

    if (_boardDisabled) {
        return; // Bot está jogando
    }

    if (true != _board.isValidCell(pos)) {
        return; // Jogada inválida
    }

    // Muda o valor da célula
    _board.setCell(pos, _currentPlayer);

    if (_mode == GameMode::Neo) {
        applyNeoRule(_currentPlayer, pos);
    }

    // Valida se houve vitória
    checkWinContition();



    if (_gameState == GameState::Playing) {
        // Troca o Jogador Atual
        _currentPlayer = _currentPlayer == Player::X
            ? Player::O
            : Player::X;
    }

    // Emite um aviso que os seguintes eventos ocorreram:
    emit boardStateChanged();    // Status da tabela mudou
    emit currentPlayerChanged(); // Jogador atual mudou
    emit gameStatusChanged();    // Status do jogo pode ter mudado;
    emit playerTurnChanged();    // Turno mudou

    maybeTriggerBotMove();
}

/// @brief Dispara a jogada do bot (modo fácil) após a jogada do jogador, se aplicável.
void GameEngine::maybeTriggerBotMove() {
    if (_gameState != GameState::Playing) {
        return;
    }

    if (_mode != GameMode::Easy && _mode != GameMode::Medium && _mode != GameMode::Hard) {
        return;
    }

    // Bot sempre joga como O
    if (_currentPlayer != Player::O) {
        return;
    }

    setBoardDisabled(true);
    QTimer::singleShot(BOT_THINK_DELAY_MS, this, &GameEngine::performBotMove);
}

/// @brief Executa a jogada do bot de acordo com o modo de jogo atual.
void GameEngine::performBotMove() {
    if (_gameState != GameState::Playing) {
        setBoardDisabled(false);
        return;
    }

    int pos = -1;
    switch (_mode) {
        case GameMode::Easy:
            pos = _aiEngine.getEasyMove(_board);
            break;
        case GameMode::Medium:
            pos = _aiEngine.getMediumMove(_board);
            break;
        case GameMode::Hard:
            pos = _aiEngine.getHardMove(_board);
            break;
        default:
            break;
    }

    if (pos >= 0) {
        _board.setCell(pos, _currentPlayer);

        checkWinContition();

        if (_gameState == GameState::Playing) {
            _currentPlayer = _currentPlayer == Player::X
                ? Player::O
                : Player::X;
        }

        emit boardStateChanged();
        emit currentPlayerChanged();
        emit gameStatusChanged();
        emit playerTurnChanged();
    }

    setBoardDisabled(false);
}

/// @brief Aplica a regra do modo Neo: cada jogador só pode ter 3 peças no tabuleiro;
///        ao colocar a 4ª, a mais antiga desaparece.
/// @param player jogador que acabou de jogar
/// @param pos posição onde a peça foi colocada
void GameEngine::applyNeoRule(Player player, int pos) {
    std::vector<int>& moves = player == Player::X ? _xMoves : _oMoves;

    moves.push_back(pos);

    if (moves.size() > 3) {
        int oldest = moves.front();
        moves.erase(moves.begin());
        _board.clearCell(oldest);
    }
}

