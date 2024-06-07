#ifndef SNAKE2_CONSOLEVIEW_H
#define SNAKE2_CONSOLEVIEW_H

#include "../snake/SnakeConsoleView.h"
#include "../tetris/TetrisConsoleView.h"
#include "BaseView.h"

namespace s21 {
class ConsoleView : public BaseView {
public:
    explicit ConsoleView(SnakeController *snakeController = nullptr, TetrisController *tetrisController = nullptr);
    ~ConsoleView() = default;

    void Start() override;
protected:
    static void InitNcurses();

private:
    void MainLoop();

    SnakeConsoleView snakeConsoleView;
    TetrisConsoleView tetrisConsoleView;
    static void InitColors();
};
}



#endif//SNAKE2_CONSOLEVIEW_H
