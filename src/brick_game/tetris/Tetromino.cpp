#include "Tetromino.h"

s21::Tetromino::Tetromino() {
    tetroPosition.resize(4); //TODO: можно 4 добавить в константы
    SetRandomShape();
}
s21::Tetromino::Tetromino(const s21::Tetromino &other) {
    if (this != &other) {
        tetroShape = other.tetroShape;
        tetroPosition = other.tetroPosition;
    }
}
s21::Tetromino &s21::Tetromino::operator=(const s21::Tetromino &other) {
    if (this != &other) {
        tetroShape = other.tetroShape;
        tetroPosition = other.tetroPosition;
    }

    return *this;
}

void s21::Tetromino::SetShape(s21::TetroShape shape) {
    tetroShape = shape;

    for (int i = 0; i < 4; ++i) {
        tetroPosition[i].x = TetroPosition::positionTable[static_cast<int>(shape)][i][1] + (Properties::FIELD_WIDTH / 2);
        tetroPosition[i].y = TetroPosition::positionTable[static_cast<int>(shape)][i][0] - 1;
    }

    while (GetMinY() < 1) MoveDown();
}

void s21::Tetromino::SetRandomShape() {
    std::random_device randomDevice;
    std::default_random_engine defaultRandomEngine(randomDevice());
    std::uniform_int_distribution<int> distribution(1, 7);
    auto randomShape = static_cast<TetroShape>(distribution(defaultRandomEngine));
    SetShape(randomShape);
}
void s21::Tetromino::Rotate() {
    if (tetroShape == TetroShape::SQUARED_SHAPE) return;

    int centerX = GetMaxX() - 1;
    int centerY = GetMaxY() - 1;

    std::vector<Position> newPosition(4);
    int rotationMatrix[2][2] = {
            {0, -1},
            {1, 0}
    };

    for (int i = 0; i < 4; ++i) {
        int x = tetroPosition[i].x - centerX;
        int y = tetroPosition[i].y - centerY;
        int newX = rotationMatrix[0][0] * x + rotationMatrix[0][1] * y + (centerX);
        int newY = rotationMatrix[1][0] * x + rotationMatrix[1][1] * y + (centerY);
        newPosition[i] = {newX, newY};
    }

    tetroPosition = newPosition;

    while (GetMinY() <= 0) {
        MoveDown();
    }

    while (GetMaxX() >= static_cast<int>(Properties::FIELD_WIDTH)) {
        MoveLeft();
    }

    while (GetMinX() < 0) {
        MoveRight();
    }

}
void s21::Tetromino::MoveDown() {
    if (GetMaxY() > Properties::FIELD_HEIGHT) return;

    for (auto &i : tetroPosition) {
        i.y += 1;
    }
}
void s21::Tetromino::MoveLeft() {
    if (GetMinX() < 1) return;

    for (auto &i : tetroPosition) {
        i.x -= 1;
    }
}
void s21::Tetromino::MoveRight() {
    if (GetMaxX() == Properties::FIELD_WIDTH - 1) return;

    for (auto &i : tetroPosition) {
        i.x += 1;
    }
}
int s21::Tetromino::GetMinX() {
    int result = tetroPosition[0].x;

    for (int i = 0; i < 4; ++i) {
        result = std::min(result, tetroPosition[i].x);
    }

    return result;
}

int s21::Tetromino::GetMaxX() {
    int result = tetroPosition[0].x;

    for (int i = 0; i < 4; ++i) {
        result = std::max(result, tetroPosition[i].x);
    }

    return result;
}
int s21::Tetromino::GetMinY() {
    int result = tetroPosition[0].y;

    for (int i = 0; i < 4; ++i) {
        result = std::min(result, tetroPosition[i].y);
    }

    return result;
}
int s21::Tetromino::GetMaxY() {
    int result = tetroPosition[0].y;

    for (int i = 0; i < 4; ++i) {
        result = std::max(result, tetroPosition[i].y);
    }

    return result;
}
