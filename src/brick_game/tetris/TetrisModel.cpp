#include "TetrisModel.h"

s21::TetrisModel::TetrisModel() {
    tetrisData.tetrisField.resize(Properties::FIELD_HEIGHT, std::vector<std::pair<bool, int>>(Properties::FIELD_WIDTH, {false, 0}));
    SetDefaultData();
    tetrisData.bestScore = LoadScore(Properties::FILE_NAME);
}

s21::TetrisModel::~TetrisModel() {
    SaveScore(tetrisData.bestScore, Properties::FILE_NAME);
}

void s21::TetrisModel::SetDefaultData() {
    tetrisData.score = 0;
    tetrisData.lvl = 1;
    tetrisData.state = State::START;
    tetrisData.currentTetromino.SetRandomShape();
    tetrisData.nextTetromino.SetRandomShape();
    tetrisData.projectionTetromino = tetrisData.currentTetromino;
    InitBoard();
    SetProjection();
    lastMovingTime = GetCurrentTime();
    currentDelay = Properties::INTERVALS_MS[0];
}

void s21::TetrisModel::UpdateModelData(s21::PlayerAction action) {
    tetrisData.isChanged = false;
    TetrisData oldData = tetrisData;
    
    long long currentTime = lastMovingTime;
    
    if (tetrisData.state != State::PAUSE) {
        currentTime = GetCurrentTime();
    }
    
    Action function = tetrisActionTable[static_cast<int>(tetrisData.state)][static_cast<int>(action)];
    
    if (function) {
        (this->*function)();
    }
    
    if (tetrisData.state == State::MOVING) {
        if (currentTime - lastMovingTime > currentDelay) {
            lastMovingTime = currentTime;
            
            if (CheckCollision()) UpdateBoard();
            MoveDown();
        }
        
        UpdateLevel();
    }
    
    if (tetrisData != oldData) {
        tetrisData.isChanged = true;
    }
}

bool s21::TetrisModel::CheckCollision() {
    bool isCollide = false;
    
    for (const auto& position : tetrisData.currentTetromino.GetPosition()) {
        if (position.y == Properties::FIELD_HEIGHT) { 
            isCollide = true;
            break;
        }
        
        if (tetrisData.tetrisField[position.y][position.x].first) { 
            isCollide = true;
            break;
        }
    }
    
    return isCollide;
}

void s21::TetrisModel::UpdateBoard() {
    PlacePiece();
    int completedLines = ClearLines();
    UpdatePlayerResults(completedLines);
    InitNewTetromino();
}


void s21::TetrisModel::UpdatePlayerResults(int completedLines) {
    if (completedLines == 1) {
        tetrisData.score += 100;
    } else if (completedLines == 2) {
        tetrisData.score += 300;
    } else if (completedLines == 3) {
        tetrisData.score += 700;
    } else if (completedLines == 4) {
        tetrisData.score += 1500;
    }

    tetrisData.bestScore = std::max(tetrisData.bestScore, tetrisData.score);
    UpdateLevel();
}

void s21::TetrisModel::InitBoard() {
    tetrisData.tetrisField.resize(Properties::FIELD_HEIGHT, std::vector<std::pair<bool, int>>(Properties::FIELD_WIDTH, {false, 0}));

    for (int i = 0; i < Properties::FIELD_HEIGHT; ++i) {
        for (int j = 0; j < Properties::FIELD_WIDTH; ++j) {
            tetrisData.tetrisField[i][j].first = false;
            tetrisData.tetrisField[i][j].second = static_cast<int>(TetroShape::NO_SHAPE);
        }
    }
}

void s21::TetrisModel::PlacePiece() {
    for (const auto& position : tetrisData.currentTetromino.GetPosition()) {
        int x = position.x;
        int y = position.y;
        
        tetrisData.tetrisField[y - 1][x].first = true;
        tetrisData.tetrisField[y - 1][x].second = static_cast<int>(tetrisData.currentTetromino.GetShape());
    }
}

int s21::TetrisModel::ClearLines() {
    int countLines = 0;

    for (int i = 0; i < Properties::FIELD_HEIGHT; ++i) {
        bool lineFilled = true;

        for (int j = 0; j < Properties::FIELD_WIDTH; ++j) {
            if (!tetrisData.tetrisField[i][j].first) {
                lineFilled = false;
                break;
            }
        }
        
        if (lineFilled) {
            tetrisData.tetrisField.erase(tetrisData.tetrisField.begin() + i);
            tetrisData.tetrisField.insert(tetrisData.tetrisField.begin(), std::vector<std::pair<bool, int>>(Properties::FIELD_WIDTH, {false, 0}));
            
            countLines++;
        }
    }
    
    return countLines;
}

void s21::TetrisModel::SetProjection() {
    tetrisData.projectionTetromino = tetrisData.currentTetromino;

    while (TryToMove(tetrisData.projectionTetromino, PlayerAction::DOWN)) {
        tetrisData.projectionTetromino.MoveDown();
    }
}

void s21::TetrisModel::UpdateLevel() {
    if (tetrisData.lvl < 10 && tetrisData.score > 600) {
        tetrisData.lvl = tetrisData.score / 600; //TODO: move 600 in properties
    }
    
    currentDelay = Properties::INTERVALS_MS[tetrisData.lvl - 1];
}

bool s21::TetrisModel::TryToMove(s21::Tetromino &tetromino, s21::PlayerAction direction) {
    bool canMove = true;
    
    for (const auto& position : tetromino.GetPosition()) {
        switch (direction) {
            case PlayerAction::DOWN:
                if (position.y == Properties::FIELD_HEIGHT ||
                    tetrisData.tetrisField[position.y][position.x].first) {
                    canMove = false;
                }

                break;
            case PlayerAction::LEFT:
                if (position.x < 1 || tetrisData.tetrisField[position.y - 1][position.x - 1].first) {
                    canMove = false;
                }

                break;
            case PlayerAction::RIGHT:
                if (position.x == Properties::FIELD_WIDTH - 1 ||
                    tetrisData.tetrisField[position.y - 1][position.x + 1].first) {
                    canMove = false;
                }

                break;
            default:
                break;
        }

        if (!canMove) break;
    }

    return canMove;
}

void s21::TetrisModel::MoveLeft() {
    if (TryToMove(tetrisData.currentTetromino, PlayerAction::LEFT)) {
        tetrisData.currentTetromino.MoveLeft();
        SetProjection();
    }
}

void s21::TetrisModel::MoveRight() {
    if (TryToMove(tetrisData.currentTetromino, PlayerAction::RIGHT)) {
        tetrisData.currentTetromino.MoveRight();
        SetProjection();
    }
}

void s21::TetrisModel::MoveDown() {
    if (TryToMove(tetrisData.currentTetromino, PlayerAction::DOWN)) {
        tetrisData.currentTetromino.MoveDown();
        SetProjection();
    }
}

void s21::TetrisModel::Drop() {
    tetrisData.currentTetromino = tetrisData.projectionTetromino;
    UpdateBoard();
}

void s21::TetrisModel::Rotate() {
    auto tempTetromino = tetrisData.currentTetromino;
    tetrisData.currentTetromino.Rotate();
    bool canRotate = true;
    
    for (const auto& position : tetrisData.currentTetromino.GetPosition()) {
        if (tetrisData.tetrisField[position.y - 1][position.x].first) {
            canRotate = false;
            break;
        }
    }
    
    if (!canRotate) {
        tetrisData.currentTetromino = tempTetromino;
    }    
    
    SetProjection();
}

void s21::TetrisModel::InitNewTetromino() {
    tetrisData.state = State::MOVING;
    tetrisData.currentTetromino = tetrisData.nextTetromino;
    tetrisData.nextTetromino.SetRandomShape();
    tetrisData.projectionTetromino = tetrisData.currentTetromino;
    SetProjection();
    
    if (CheckCollision()) tetrisData.state = State::GAME_OVER;
}

void s21::TetrisModel::SetPause() {
    tetrisData.state = State::PAUSE;
}

void s21::TetrisModel::CancelPause() {
    tetrisData.state = State::MOVING;
}

void s21::TetrisModel::ExitGame() {
    tetrisData.state = State::EXIT;
}

void s21::TetrisModel::Collide() {
    tetrisData.state = State::INIT;
    UpdateBoard();
}

void s21::TetrisModel::StartGame() {
    SetDefaultData();
    tetrisData.state = State::INIT;
}

void s21::TetrisModel::GameOver() {
    tetrisData.state = State::EXIT;
}
