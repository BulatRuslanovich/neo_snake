#include "SnakeModel.h"

namespace s21 {
    //!
    SnakeModel::SnakeModel() : snakeData() {
        snakeData.bestScore = LoadScore(Properties::FILE_NAME);
    }

    //!
    SnakeModel::~SnakeModel() {
        SaveScore(snakeData.bestScore, Properties::FILE_NAME);
        snakeData.snakePosition.clear();
    }

    //!
    void SnakeModel::UpdateModelData(PlayerAction action) {
        snakeData.isChanged = false;
        SnakeData oldData = snakeData;
        currentTime = lastMovingTime;

        if (snakeData.state != State::PAUSE) {
            currentTime = GetCurrentTime();
        }

        Action function = snakeActionTable[static_cast<int>(snakeData.state)][static_cast<int>(action)];

        if (function) (this->*function)();

        if (snakeData.state == State::MOVING) {
            if (currentTime - lastMovingTime > currentDelay) {
                MoveSnake();
            }
        }

        if (snakeData != oldData) snakeData.isChanged = true;
    }

    //!
    SnakeData &SnakeModel::GetModelData() {
        return snakeData;
    }

    //!
    void SnakeModel::UpdateApplePosition() {
        std::random_device randomDevice;
        std::default_random_engine defaultRandomEngine(randomDevice());
        std::uniform_int_distribution<int> widthDistribution(0, Properties::FIELD_WIDTH - 1);
        std::uniform_int_distribution<int> heightDistribution(0, Properties::FIELD_HEIGHT - 1);

        snakeData.applePosition.x = widthDistribution(defaultRandomEngine);
        snakeData.applePosition.y = heightDistribution(defaultRandomEngine);

        for (const auto& i : snakeData.snakePosition) {
            if (snakeData.applePosition.x == i.x && snakeData.applePosition.y == i.y) {
                UpdateApplePosition();
            }
        }
    }

    //!
    void SnakeModel::MoveSnakeBody() {
        for (auto i = snakeData.snakePosition.size(); i > 0; --i) {
            snakeData.snakePosition[i] = snakeData.snakePosition[i - 1];
        }
    }

    //!
    void SnakeModel::CheckEating() {
        if (snakeData.snakePosition[0] == snakeData.applePosition) {
            snakeData.snakePosition.push_back({-30, -30});
            snakeData.currentScore++;

            if (snakeData.currentScore % 5 == 0 && snakeData.lvl < 10) {
                snakeData.lvl++;
                currentDelay = Properties::INTERVALS_MS[snakeData.lvl - 1];
            }

            if (snakeData.currentScore > snakeData.bestScore) {
                snakeData.bestScore = snakeData.currentScore;
            }

            if (snakeData.currentScore == Properties::WIN_SCORE) {
                snakeData.isWin = true;
                snakeData.state = State::GAME_OVER;
            }

            UpdateApplePosition();
        }
    }

    //!
    void SnakeModel::CheckCollision() {
        for (std::size_t i = 1; i < snakeData.snakePosition.size(); ++i) {
            if (snakeData.snakePosition[0] == snakeData.snakePosition[i]) {
                snakeData.state = State::COLLIDE;
            }
        }

        if (snakeData.snakePosition[0].x < 0 ||
            snakeData.snakePosition[0].x >= Properties::FIELD_WIDTH) {
            snakeData.state = State::COLLIDE;
        }
        if (snakeData.snakePosition[0].y < 0 ||
            snakeData.snakePosition[0].y >= Properties::FIELD_HEIGHT) {
            snakeData.state = State::COLLIDE;
        }
    }

    //!
    void SnakeModel::MoveSnake() {
        switch (snakeData.direction) {
            case Direction::Up:
                MoveUp();
                break;
            case Direction::Down:
                MoveDown();
                break;
            case Direction::Right:
                MoveRight();
                break;
            case Direction::Left:
                MoveLeft();
                break;
        }
    }

    void SnakeModel::MoveLeft() {
        if (snakeData.direction == Direction::Right) return;
        snakeData.direction = Direction::Left;
        MoveSnakeBody();
        snakeData.snakePosition[0].x -= 1;
        CheckEating();
        CheckCollision();
        lastMovingTime = currentTime;
    }

    void SnakeModel::MoveRight() {
        if (snakeData.direction == Direction::Left) return;
        snakeData.direction = Direction::Right;
        MoveSnakeBody();
        snakeData.snakePosition[0].x += 1;
        CheckEating();
        CheckCollision();
        lastMovingTime = currentTime;
    }
    void SnakeModel::MoveDown() {
        if (snakeData.direction == Direction::Up) return;
        snakeData.direction = Direction::Down;
        MoveSnakeBody();
        snakeData.snakePosition[0].y += 1;
        CheckEating();
        CheckCollision();
        lastMovingTime = currentTime;
    }

    void SnakeModel::MoveUp() {
        if (snakeData.direction == Direction::Down) return;
        snakeData.direction = Direction::Up;
        MoveSnakeBody();
        snakeData.snakePosition[0].y -= 1;
        CheckEating();
        CheckCollision();
        lastMovingTime = currentTime;
    }

    void SnakeModel::Init() {
        snakeData.state = State::MOVING;
    }

    void SnakeModel::SetPause() {
        snakeData.state = State::PAUSE;
    }
    void SnakeModel::CancelPause() {
        Init();
    }
    void SnakeModel::Collide() {
        snakeData.state = State::GAME_OVER;
    }
    void SnakeModel::GameOver() {
        ExitGame();
    }

    void SnakeModel::StartGame() {
        snakeData.state = State::INIT;
    }
    void SnakeModel::ExitGame() {
        snakeData.state = State::EXIT;
    }

    void SnakeModel::SetDefaultData() {
        currentDelay = Properties::INTERVALS_MS[0];
        lastMovingTime = currentTime = GetCurrentTime();
        snakeData.lvl = 1;
        snakeData.currentScore = 0;
        snakeData.direction = Direction::Up;
        snakeData.state = State::START;
        snakeData.snakePosition.clear();
        snakeData.snakePosition.reserve(Properties::MAX_SNAKE_LENGTH);

        snakeData.snakePosition.push_back({5, Properties::FIELD_HEIGHT / 2});
        snakeData.snakePosition.push_back({5, Properties::FIELD_HEIGHT / 2 + 1});
        snakeData.snakePosition.push_back({5, Properties::FIELD_HEIGHT / 2 + 2});
        snakeData.snakePosition.push_back({5, Properties::FIELD_HEIGHT / 2 + 3});

        UpdateApplePosition();
    }



}// namespace s21