#include "SnakeConsoleView.h"

//!
s21::SnakeConsoleView::SnakeConsoleView(s21::SnakeController *controller) : action(PlayerAction::DEFAULT), snakeData(), snakeController(controller) {}

//!
void s21::SnakeConsoleView::Start() {
    nodelay(stdscr, TRUE);
    snakeController->SetModelDataDefault();
    snakeData = &snakeController->GetModelData();
    SnakeMainLoop();

    if (snakeData->state == State::GAME_OVER || snakeData->state == State::EXIT) {
        GameResultRendering(snakeData->isWin, snakeData->lvl, snakeData->currentScore);
    }
}

//!
void s21::SnakeConsoleView::Rendering() {
    if (snakeData->state == State::START) {
        StartGameRendering();
    } else if (snakeData->state == State::PAUSE) {
        PauseRendering(snakeData->lvl, snakeData->currentScore);
    } else {
        GameRendering();
    }
}

//!
void s21::SnakeConsoleView::SnakeMainLoop() {
    while (snakeData->state != State::GAME_OVER && snakeData->state != State::EXIT) {
        if (snakeData->isChanged) {
            Rendering();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        action = GetAction();
        ModelConnect();
    }
}

//!
void s21::SnakeConsoleView::ModelConnect() {
    snakeController->UpdateModelData(action);
    snakeData = &snakeController->GetModelData();
    action = PlayerAction::DEFAULT;
}

void s21::SnakeConsoleView::GameRendering() {
    clear();
    attron(COLOR_PAIR(1));
    mvprintw(snakeData->applePosition.y + 1, snakeData->applePosition.x + 1, "%c", ACS_PI);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    for (const auto& i : snakeData->snakePosition) {
        mvprintw(i.y + 1, i.x + 1, "%c", 'S');
    }
    attroff(COLOR_PAIR(2));


    GameFieldRendering(Choose::SNAKE, snakeData->lvl, snakeData->currentScore,
                       snakeData->bestScore);
    refresh();
}
