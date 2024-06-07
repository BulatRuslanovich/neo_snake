#include "ConsoleView.h"

s21::ConsoleView::ConsoleView(s21::SnakeController *snakeController, s21::TetrisController *tetrisController) : snakeConsoleView(snakeController), tetrisConsoleView(tetrisController) {}

void s21::ConsoleView::Start() {
    setlocale(LC_ALL, "");
    InitNcurses();
    MainLoop();
}

void s21::ConsoleView::InitNcurses() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);

    start_color();
    InitColors();
}

void s21::ConsoleView::MainLoop() {
    Choose ch = InitMenu();

    while (ch != Choose::EXIT) {
        if (ch == Choose::SNAKE) {
            snakeConsoleView.Start();
        } else if (ch == Choose::TETRIS) {
            tetrisConsoleView.Start();
        }

        ch = InitMenu();
    }

    curs_set(1);
    endwin();
}

void s21::ConsoleView::InitColors() {
    init_color((short)ColorIndex::RED, 1000, 0, 0);
    init_color((short)ColorIndex::GREEN, 0, 1000, 0);
    init_color((short)ColorIndex::CYAN, 0, 1000, 1000);
    init_color((short)ColorIndex::PURPLE, 1000, 0, 1000);
    init_color((short)ColorIndex::YELLOW, 1000, 1000, 0);
    init_color((short)ColorIndex::ORANGE, 1000, 500, 0);
    init_color((short)ColorIndex::BLUE, 0, 0, 1000);
    init_color((short)ColorIndex::GRAY, 500, 500, 500);

    init_pair(1, (short)ColorIndex::RED, (short)ColorIndex::RED);
    init_pair(2, (short)ColorIndex::GREEN,(short)ColorIndex::GREEN);
    init_pair(3, (short)ColorIndex::CYAN, (short)ColorIndex::CYAN);
    init_pair(4, (short)ColorIndex::PURPLE,(short)ColorIndex::PURPLE);
    init_pair(5, (short)ColorIndex::YELLOW,(short)ColorIndex::YELLOW);
    init_pair(6, (short)ColorIndex::ORANGE,(short)ColorIndex::ORANGE);
    init_pair(7, (short)ColorIndex::BLUE, (short)ColorIndex::BLUE);
    init_pair(8, (short)ColorIndex::GRAY, (short)ColorIndex::GRAY);
}
