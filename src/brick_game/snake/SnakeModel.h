//
// Created by bulatruslanovich on 03/06/2024.
//

#ifndef CPP3_BRICKGAME_V2_0_2_SNAKEMODEL_H
#define CPP3_BRICKGAME_V2_0_2_SNAKEMODEL_H

#include <random>
#include <vector>

#include "../common-code/SaveScoreManager.h"

namespace s21 {
    enum class Direction {
        Right,
        Left,
        Down,
        Up
    };

    struct SnakeData {
        Position applePosition;
        std::vector<Position> snakePosition;
        Direction direction;
        bool isWin;
        State state;
        int currentScore;
        int bestScore;
        int lvl;
        bool isChanged;

        SnakeData() : applePosition(), snakePosition(), direction(Direction::Right), isWin(false), state(State::START), currentScore(0), bestScore(0), lvl(1), isChanged(true) {}

        bool operator==(const SnakeData& other) const {
            return currentScore == other.currentScore && state == other.state && applePosition == other.applePosition && snakePosition == other.snakePosition;
        }
        
        bool operator!=(const SnakeData& other) const {
            return !(*this == other);
        }
    };
    
class SnakeModel : public SaveScoreManager {
public:
    SnakeModel();
    ~SnakeModel();
    
    void UpdateModelData(PlayerAction action);
    
    SnakeData& GetModelData();

    void SetDefaultData();

    using Action = void (SnakeModel::*)();

    const Action snakeActionTable[7][9] = {
            // Start
            {nullptr, nullptr, nullptr, nullptr, nullptr, &SnakeModel::StartGame,
             &SnakeModel::StartGame, &SnakeModel::ExitGame, nullptr},
            // Init
            {&SnakeModel::Init, &SnakeModel::Init, &SnakeModel::Init,
             &SnakeModel::Init, &SnakeModel::Init, &SnakeModel::Init,
             &SnakeModel::Init, &SnakeModel::Init, &SnakeModel::Init},
            // Moving,
            {nullptr, &SnakeModel::MoveLeft, &SnakeModel::MoveRight,
             &SnakeModel::MoveDown, &SnakeModel::MoveUp,
             &SnakeModel::SetPause, nullptr, &SnakeModel::ExitGame,
             &SnakeModel::SetPause},
            // Collide,
            {&SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
             &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide,
             &SnakeModel::Collide, &SnakeModel::Collide, &SnakeModel::Collide},
            // Pause,
            {nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
             &SnakeModel::CancelPause, &SnakeModel::ExitGame,
             &SnakeModel::CancelPause},
            // Exit,
            {&SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
             &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame,
             &SnakeModel::ExitGame, &SnakeModel::ExitGame, &SnakeModel::ExitGame},
            // GameOver
            {&SnakeModel::GameOver, &SnakeModel::GameOver, &SnakeModel::GameOver,
             &SnakeModel::GameOver, &SnakeModel::GameOver, &SnakeModel::GameOver,
             &SnakeModel::GameOver, &SnakeModel::GameOver, &SnakeModel::GameOver}};
private:
    SnakeData snakeData;
    long long lastMovingTime{};
    long long currentTime{};
    long long currentDelay{};

    void MoveSnake();
    void UpdateApplePosition();
    void MoveSnakeBody();
    void CheckEating();
    void CheckCollision();
    void MoveLeft();
    void MoveRight();
    void MoveDown();
    void MoveUp();
    void Init();
    void SetPause();
    void CancelPause();
    void Collide();
    void GameOver();
    void StartGame();
    void ExitGame();
};
}// namespace s21


#endif// CPP3_BRICKGAME_V2_0_2_SNAKEMODEL_H
