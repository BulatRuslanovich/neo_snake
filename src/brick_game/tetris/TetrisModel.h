#ifndef SNAKE2_TETRISMODEL_H
#define SNAKE2_TETRISMODEL_H

#include "../common-code/SaveScoreManager.h"
#include "Tetromino.h"

namespace s21 {
    struct TetrisData {
        bool isChanged;
        int score;
        int bestScore;
        int lvl;
        State state;
        Tetromino currentTetromino;
        Tetromino projectionTetromino;
        Tetromino nextTetromino;
        std::vector<std::vector<std::pair<bool, int>>> tetrisField;

        TetrisData() : isChanged(true), score(0), bestScore(0), lvl(1), state(State::START), currentTetromino(), projectionTetromino(), nextTetromino(), tetrisField() {}

        bool operator==(const TetrisData& other) const {
            return score == other.score && bestScore == other.bestScore &&
                   lvl == other.lvl && state == other.state &&
                   currentTetromino == other.currentTetromino && tetrisField == other.tetrisField;
        }

        bool operator!=(const TetrisData& other) const {
            return !(*this == other);
        }
    };

    class TetrisModel : public SaveScoreManager {
    public:
        TetrisModel();
        ~TetrisModel();
        TetrisData&GetModelData() { return tetrisData; }
        void SetDefaultData();
        void UpdateModelData(PlayerAction action = PlayerAction::DEFAULT);
        
        using Action = void (TetrisModel::*)();
        
        const Action tetrisActionTable[7][9] = {
                // Start
                {nullptr, nullptr, nullptr, nullptr, nullptr, &TetrisModel::StartGame,
                 &TetrisModel::StartGame, &TetrisModel::ExitGame, nullptr},
                // Spawn
                {&TetrisModel::InitNewTetromino, &TetrisModel::InitNewTetromino,
                 &TetrisModel::InitNewTetromino, &TetrisModel::InitNewTetromino,
                 &TetrisModel::InitNewTetromino, &TetrisModel::InitNewTetromino,
                 &TetrisModel::InitNewTetromino, &TetrisModel::InitNewTetromino,
                 &TetrisModel::InitNewTetromino},
                // Moving,
                {nullptr, &TetrisModel::MoveLeft,
                 &TetrisModel::MoveRight, &TetrisModel::MoveDown,
                 &TetrisModel::Rotate, &TetrisModel::Drop,
                 &TetrisModel::Drop, &TetrisModel::ExitGame,
                 &TetrisModel::SetPause},
                // Collide,
                {&TetrisModel::Collide, &TetrisModel::Collide, &TetrisModel::Collide,
                 &TetrisModel::Collide, &TetrisModel::Collide, &TetrisModel::Collide,
                 &TetrisModel::Collide, &TetrisModel::Collide, &TetrisModel::Collide},
                // Pause,
                {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
                 &TetrisModel::CancelPause, &TetrisModel::ExitGame,
                 &TetrisModel::CancelPause},
                // Exit,
                {&TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame,
                 &TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame,
                 &TetrisModel::ExitGame, &TetrisModel::ExitGame, &TetrisModel::ExitGame},
                // GameOver
                {&TetrisModel::GameOver, &TetrisModel::GameOver, &TetrisModel::GameOver,
                 &TetrisModel::GameOver, &TetrisModel::GameOver, &TetrisModel::GameOver,
                 &TetrisModel::GameOver, &TetrisModel::GameOver, &TetrisModel::GameOver}};
        
    private:
        TetrisData tetrisData;
        long long lastMovingTime{};
        long long currentDelay{};
        
        bool CheckCollision();
        void UpdateBoard();
        void UpdatePlayerResults(int completed_lines);
        void InitBoard();
        void PlacePiece();
        int ClearLines();
        void SetProjection();
        void UpdateLevel();
        bool TryToMove(Tetromino& t, PlayerAction direction);
        
        void MoveLeft();
        void MoveRight();
        void MoveDown();
        void Drop();
        void Rotate();
        void InitNewTetromino();
        void SetPause();
        void CancelPause();
        void ExitGame();
        void Collide();
        void StartGame();
        void GameOver();
    };
}

#endif//SNAKE2_TETRISMODEL_H
