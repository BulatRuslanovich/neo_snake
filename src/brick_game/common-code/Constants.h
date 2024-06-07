#ifndef CPP3_BRICKGAME_V2_0_2_CONSTANTS_H
#define CPP3_BRICKGAME_V2_0_2_CONSTANTS_H
#include <string>

namespace s21 {
    namespace Properties {
        static std::string FILE_NAME = "SnakeScore.txt";
        constexpr int MAX_SNAKE_LENGTH = 200;
        constexpr int FIELD_WIDTH = 10;
        constexpr int FIELD_HEIGHT = 20;
        constexpr int WIN_SCORE = 200;
        constexpr int DOT_SIZE = 30;
        constexpr int SIDE_PANEL_HEIGHT = 5;
        constexpr int WINDOW_WIDTH = 30;
        constexpr int WINDOW_HEIGHT = 21;
        static constexpr int INTERVALS_MS[] = {500, 420, 340, 260, 230,
                                             200, 180, 160, 140, 125};
    }// namespace Properties

    enum class State {
        START,
        INIT,
        MOVING,
        COLLIDE,
        PAUSE,
        EXIT,
        GAME_OVER
    };

    enum class PlayerAction {
        DEFAULT = 0,
        LEFT,
        RIGHT,
        DOWN,
        UP,
        SPACE,
        ENTER,
        ESC,
        TAB
    };

    struct Position {
        Position() : x(0), y(0) {}
        Position(int x, int y) : x(x), y(y) {}

        bool operator==(const Position &other) const {
            return (x == other.x && y == other.y);
        }

        int x;
        int y;
    };
}// namespace s21


#endif// CPP3_BRICKGAME_V2_0_2_CONSTANTS_H
