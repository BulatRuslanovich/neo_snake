#include "TetrisConsoleView.h"
s21::TetrisConsoleView::TetrisConsoleView(s21::TetrisController *controller) : tetrisController(controller) {
    tetrisData = &tetrisController->GetModelData();
    action = PlayerAction::DEFAULT;
}
void s21::TetrisConsoleView::Start() {
    nodelay(stdscr, TRUE);
    tetrisController->SetModelDataDefault();
    tetrisData = &tetrisController->GetModelData();
    
    TetrisMainLoop();

    if (tetrisData->state == State::GAME_OVER ||
        tetrisData->state == State::EXIT) {
        GameResultRendering(false, tetrisData->lvl, tetrisData->score);
    }
}

void s21::TetrisConsoleView::TetrisMainLoop() {
    while (tetrisData->state != State::GAME_OVER &&
           tetrisData->state != State::EXIT) {
        if (tetrisData->isChanged) {
            Rendering();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        action = GetAction();
        ModelConnect();
    }
}

void s21::TetrisConsoleView::ModelConnect() {
    tetrisController->UpdateModelData(action);
    tetrisData = &tetrisController->GetModelData();
//    TetrisData tmp_data = tetrisController->GetModelData();
    action = PlayerAction::DEFAULT;
}

void s21::TetrisConsoleView::GameRendering() {
    clear();
    GameFieldRendering(Choose::TETRIS, tetrisData->lvl, tetrisData->score,
                       tetrisData->bestScore);

    for (const auto &item : tetrisData->projectionTetromino.GetPosition()) {
        attron(COLOR_PAIR(8));
        mvprintw(item.y, item.x + 1, ".");
        attroff(COLOR_PAIR(8));
    }

    for (const auto &item : tetrisData->currentTetromino.GetPosition()) {
        attron(COLOR_PAIR((short)tetrisData->currentTetromino.GetShape()));
        mvprintw(item.y, item.x + 1, ".");
        attroff(COLOR_PAIR((short)tetrisData->currentTetromino.GetShape()));
    }

    for (const auto &item : tetrisData->nextTetromino.GetPosition()) {
        attron(COLOR_PAIR((short)tetrisData->nextTetromino.GetShape()));
        mvprintw(item.y + 1, item.x + 11, ".");
        attroff(COLOR_PAIR((short)tetrisData->nextTetromino.GetShape()));
    }

    for (int i = 0; i < Properties::FIELD_HEIGHT; ++i) {
        for (int j = 0; j < Properties::FIELD_WIDTH; ++j) {
            attron(COLOR_PAIR(tetrisData->tetrisField[i][j].second));

            if (tetrisData->tetrisField[i][j].first) mvprintw(i + 1, j + 1, ".");

            attroff(COLOR_PAIR(tetrisData->tetrisField[i][j].second));
        }
    }
}

void s21::TetrisConsoleView::Rendering() {
    if (tetrisData->state == State::START) {
        StartGameRendering();
    } else if (tetrisData->state == State::PAUSE) {
        PauseRendering(tetrisData->lvl, tetrisData->score);
    } else {
        GameRendering();
    }
}
