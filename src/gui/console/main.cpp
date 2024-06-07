//
// Created by bulatruslanovich on 03/06/2024.
//

#include "common-code/ConsoleView.h"

int main() {
    s21::SnakeModel snakeModel;
    s21::SnakeController snakeController(&snakeModel);
    s21::TetrisModel tetrisModel;
    s21::TetrisController tetrisController(&tetrisModel);
    s21::ConsoleView view(&snakeController, &tetrisController);
    view.Start();
    return 0;
}
