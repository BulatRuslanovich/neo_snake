#ifndef SNAKE2_TETROMINO_H
#define SNAKE2_TETROMINO_H

#include "../common-code/Constants.h"
#include <vector>
#include <random>

namespace s21 {
    enum struct TetroShape {
        NO_SHAPE,
        Z_SHAPE,
        S_SHAPE,
        LINE_SHAPE,
        T_SHAPE,
        L_SHAPE,
        MIRRORED_L_SHAPE,
        SQUARED_SHAPE
    };

    namespace TetroPosition {
        static constexpr int positionTable[8][4][2] = {
                {{0, 0}, {0, 0}, {0, 0}, {0, 0}},   // NoShape
                {{0, -1}, {0, 0}, {-1, 0}, {-1, 1}},// ZShape
                {{0, -1}, {0, 0}, {1, 0}, {1, 1}},  // SShape
                {{0, -1}, {0, 0}, {0, 1}, {0, 2}},  // LineShape
                {{-1, 0}, {0, 0}, {1, 0}, {0, 1}},  // TShape
                {{-1, -1}, {0, -1}, {0, 0}, {0, 1}},// LShape
                {{1, -1}, {0, -1}, {0, 0}, {0, 1}}, // MirroredLShape
                {{0, 0}, {1, 0}, {0, 1}, {1, 1}}    // SquareShape
        };
    };


    class Tetromino {
    public:
        Tetromino();
        Tetromino(const Tetromino &other);
        Tetromino &operator=(const Tetromino &other);

        std::vector<Position> GetPosition() { return tetroPosition; }

        bool operator==(const Tetromino &other) const {
            return tetroShape == other.tetroShape && tetroPosition == other.tetroPosition;
        }
        bool operator!=(const Tetromino &other) const { return !(*this == other); }

        void SetShape(TetroShape s);
        void SetRandomShape();

        TetroShape GetShape() { return tetroShape; }
        void Rotate();
        void MoveDown();
        void MoveLeft();
        void MoveRight();

        int GetMinX();
        int GetMaxX();
        int GetMinY();
        int GetMaxY();

    private:
        TetroShape tetroShape;
        std::vector<Position> tetroPosition;
    };

}// namespace s21


#endif//SNAKE2_TETROMINO_H
