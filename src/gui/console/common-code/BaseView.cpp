#include "BaseView.h"
#include <vector>

void s21::BaseView::DrawBox(int topLeftY, float topLeftX, int bottomRightY, float bottomRightX) {
    bottomRightX *= 2;
    topLeftX *= 2;

    for (int i = topLeftY; i <= bottomRightY; ++i) {
        mvaddch(i, topLeftX, ACS_VLINE);
        mvaddch(i, bottomRightX, ACS_VLINE);
    }

    for (int i = (int)topLeftX; i <= (int)bottomRightX; ++i) {
        mvaddch(topLeftY, i, ACS_HLINE);
        mvaddch(bottomRightY, i, ACS_HLINE);
    }

    mvaddch(topLeftY, topLeftX, ACS_ULCORNER);
    mvaddch(topLeftY, bottomRightX, ACS_URCORNER);
    mvaddch(bottomRightY, topLeftX, ACS_LLCORNER);
    mvaddch(bottomRightY, bottomRightX, ACS_LRCORNER);
}

void s21::BaseView::GameFieldRendering(s21::Choose currentGame, int lvl, int score, int record) {
    DrawBox(0, 0, Properties::WINDOW_HEIGHT, Properties::WINDOW_WIDTH);
    DrawBox(0, 0, Properties::FIELD_HEIGHT + 1, Properties::FIELD_WIDTH + 0.5);

    mvaddch(0, (Properties::FIELD_WIDTH + 0.5) * 2, ACS_TTEE);
    mvaddch(Properties::FIELD_HEIGHT + 1, (Properties::FIELD_WIDTH + 0.5) * 2, ACS_BTEE);

    int sidePanelHeight = 1;

    if (currentGame == Choose::TETRIS) {
        sidePanelHeight = Properties::SIDE_PANEL_HEIGHT;
        DrawBox(1, Properties::FIELD_WIDTH + 2, sidePanelHeight, Properties::WINDOW_WIDTH - 1);
        mvprintw(1, (Properties::FIELD_WIDTH + 3) * 2, "Next");
        sidePanelHeight++;
    }

    DrawBox(sidePanelHeight, Properties::FIELD_WIDTH + 2, sidePanelHeight + 2,
            Properties::WINDOW_WIDTH - 1);
    mvprintw(sidePanelHeight, (Properties::FIELD_WIDTH + 3) * 2, "Level");
    mvprintw(sidePanelHeight + 1, (Properties::FIELD_WIDTH + 3) * 2, "%d", lvl);

    sidePanelHeight += 3;

    DrawBox(sidePanelHeight, Properties::FIELD_WIDTH + 2, sidePanelHeight + 2,
            Properties::WINDOW_WIDTH - 1);
    mvprintw(sidePanelHeight, (Properties::FIELD_WIDTH + 3) * 2, "Score");
    mvprintw(sidePanelHeight + 1, (Properties::FIELD_WIDTH + 3) * 2, "%d", score);

    sidePanelHeight += 3;

    DrawBox(sidePanelHeight, Properties::FIELD_WIDTH + 2, sidePanelHeight + 2, Properties::WINDOW_WIDTH - 1);
    mvprintw(sidePanelHeight, (Properties::FIELD_WIDTH + 3) * 2, "Record");
    mvprintw(sidePanelHeight + 1, (Properties::FIELD_WIDTH + 3) * 2, "%d", record);
}

void s21::BaseView::GameResultRendering(bool isWin, int lvl, int score) {
    clear();
    DrawBox(0, 0, Properties::WINDOW_HEIGHT, Properties::WINDOW_WIDTH);

    if (isWin) {
        mvprintw(2, Properties::WINDOW_WIDTH - 4, "YOU WIN!");
    } else {
        mvprintw(2, Properties::WINDOW_WIDTH - 5, "GAME OVER!");
    }

    mvprintw(4, Properties::WINDOW_WIDTH - 7, "Your score: %d", score);
    mvprintw(6, Properties::WINDOW_WIDTH - 7, "Your level: %d", lvl);
    mvprintw(8, Properties::WINDOW_WIDTH - 6, "Press any key");
    mvprintw(9, Properties::WINDOW_WIDTH - 5, "to continue");
    nodelay(stdscr, FALSE);
    getch();
}
void s21::BaseView::PauseRendering(int level, int score) {
    clear();
    DrawBox(0, 0, Properties::WINDOW_HEIGHT, Properties::WINDOW_WIDTH);

    mvprintw(5, Properties::WINDOW_WIDTH - 10, "The game is on pause");
    mvprintw(8, Properties::WINDOW_WIDTH - 7, "Your score:  %d", score);
    mvprintw(10, Properties::WINDOW_WIDTH - 7, "Your level:  %d", level);

    mvprintw(12, Properties::WINDOW_WIDTH - 10, "Press Tab to continue");
    mvprintw(13, Properties::WINDOW_WIDTH - 7, "or Esc to exit");
    nodelay(stdscr, FALSE);
}
void s21::BaseView::StartGameRendering() {
    clear();
    DrawBox(0, 0, Properties::WINDOW_HEIGHT, Properties::WINDOW_WIDTH);
    mvprintw(9, Properties::WINDOW_WIDTH - 6, "Press space");
    mvprintw(10, Properties::WINDOW_WIDTH - 7, "to start game");
    mvprintw(11, Properties::WINDOW_WIDTH - 7, "Or Esc to exit");
    nodelay(stdscr, FALSE);
}

s21::PlayerAction s21::BaseView::GetAction() {
    PlayerAction action = PlayerAction::DEFAULT;
    int key = getch();
    switch (key) {
        case KEY_LEFT:
            action = PlayerAction::LEFT;
            break;
        case KEY_RIGHT:
            action = PlayerAction::RIGHT;
            break;
        case KEY_UP:
            action = PlayerAction::UP;
            break;
        case KEY_DOWN:
            action = PlayerAction::DOWN;
            break;
        case 13:
            action = PlayerAction::ENTER;
            break;
        case 9:
            action = PlayerAction::TAB;
            break;
        case 32:
            action = PlayerAction::SPACE;
            break;
        case 27:
            action = PlayerAction::ESC;
            break;
        default:
            break;
    }

    nodelay(stdscr, TRUE);
    return action;
}

s21::Choose s21::BaseView::InitMenu() {
    Choose result = Choose::MENU;
    std::size_t selectedItem = 0;

    MenuRendering(selectedItem);

    int ch;
    nodelay(stdscr, FALSE);
    while ((ch = getch()) != '\n') {
        if (ch == KEY_UP) {
            selectedItem = (selectedItem == 0) ? (selectedItem) : (selectedItem - 1);
        } else if (ch == KEY_DOWN) {
            selectedItem = (selectedItem == 2) ? (selectedItem) : (selectedItem + 1);
        }

        MenuRendering(selectedItem);
    }

    if (selectedItem == 0) {
        result = Choose::SNAKE;
    } else if (selectedItem == 1) {
        result = Choose::TETRIS;
    } else if (selectedItem == 2) {
        result = Choose::EXIT;
    }

    return result;
}

void s21::BaseView::MenuRendering(size_t &selectedItem) {
    clear();

    int startY = 10;
    int startX = Properties::WINDOW_WIDTH;

    DrawBox(0, 0, Properties::WINDOW_HEIGHT, Properties::WINDOW_WIDTH);
    mvprintw(startY - 4, startX - 4, "Game Menu");

    std::vector<std::string> choices = {"Snake", "Tetris", "Exit"};

    for (int i = 0; i < choices.size(); ++i) {
        if (i == selectedItem) {
            attron(A_REVERSE);
            mvprintw(++startY + i, startX - (int)choices[i].length() / 2, "%s", choices[i].c_str());
            attroff(A_REVERSE);
        } else {
            mvprintw(++startY + i, startX - (int)choices[i].length() / 2, "%s", choices[i].c_str());
        }
    }

    refresh();
}
