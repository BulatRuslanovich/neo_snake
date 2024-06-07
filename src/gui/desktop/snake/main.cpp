#include <QApplication>

#include "View.h"

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);
    s21::SnakeModel snakeModel;
    s21::SnakeController snakeController(&snakeModel);
    s21::TetrisModel tetrisModel;
    s21::TetrisController tetrisController(&tetrisModel);
    s21::View view(&snakeController, &tetrisController);
    view.show();
    return QApplication::exec();
}
