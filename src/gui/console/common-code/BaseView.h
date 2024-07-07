#ifndef SNAKE2_BASEVIEW_H
#define SNAKE2_BASEVIEW_H

#include <ncurses.h>
#include <chrono>
#include <cmath>
#include <string>
#include <thread>

#include "../../../brick_game/common-code/Constants.h"

namespace s21 {
    enum class Choose {
        SNAKE,
        TETRIS,
        MENU,
        EXIT
    };

    enum class ColorIndex {
        RED = 100,
        GREEN,
        CYAN,
        PURPLE,
        YELLOW,
        ORANGE,
        BLUE,
        GRAY
    };

    class BaseView {
    public:
        virtual void Start() = 0;

        static void DrawBox(int topLeftY, float topLeftX, int bottomRightY, float bottomRightX);
        static void GameFieldRendering(Choose currentGame, int lvl, int score, int record);
        static void GameResultRendering(bool inWin, int lvl, int score);
        static void PauseRendering(int level, int score);
        static void StartGameRendering();
        static PlayerAction GetAction();

        static Choose InitMenu();
        static void MenuRendering(std::size_t& selectedItem);
    };

}

#endif//SNAKE2_BASEVIEW_H
