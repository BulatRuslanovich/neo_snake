#include "View.h"
#include "ui_View.h"

namespace s21 {
    View::View(SnakeController *snakeController, TetrisController *tetrisController, QWidget *parent) : QMainWindow(parent), ui(new Ui::View), currentGame(CurrentGame::NONE), action(PlayerAction::DEFAULT), snakeData(nullptr), tetrisData(nullptr), snakeController(snakeController), tetrisController(tetrisController) {
        ui->setupUi(this);
        move(700, 300);
        setWindowTitle("BrickGame");
        ui->stackedWidget->setCurrentIndex(0);
        tetrisController->SetModelDataDefault();
        tetrisData = &tetrisController->GetModelData();
        snakeController->SetModelDataDefault();
        snakeData = &snakeController->GetModelData();
        timer = new QTimer(this);


        SetupButtons();
        connect(timer, &QTimer::timeout, this, &View::UpdateAll);
    }

    View::~View() {
        if (timer != nullptr) {
            delete timer;
        }

        delete ui;
    }

    void View::keyPressEvent(QKeyEvent *event) {
        int key = event->key();

        switch (key) {
            case Qt::Key_Left:
                action = PlayerAction::LEFT;
                break;
            case Qt::Key_Right:
                action = PlayerAction::RIGHT;
                break;
            case Qt::Key_Up:
                action = PlayerAction::UP;
                break;
            case Qt::Key_Down:
                action = PlayerAction::DOWN;
                break;
            case Qt::Key_Tab:
                action = PlayerAction::TAB;
                break;
            case Qt::Key_Enter:
                action = PlayerAction::ENTER;
                break;
            case Qt::Key_Space:
                action = PlayerAction::SPACE;
                break;
            case Qt::Key_Escape:
                action = PlayerAction::ESC;
                break;
            default:
                break;
        }
    }

    void View::paintEvent(QPaintEvent *event) {
        QWidget::paintEvent(event);
        if (currentGame == CurrentGame::SNAKE) {
            if (snakeData->state != State::GAME_OVER && snakeData->state != State::EXIT) {
                if (snakeData->state == State::START) {
                    StartWindowRendering(ui->SnakeInfoLabel);
                } else if (snakeData->state == State::PAUSE) {
                    PauseWindowRendering(ui->SnakeInfoLabel);
                } else {
                    ui->SnakeInfoLabel->setText("");
                    SnakeRendering();
                }
            } else {
                ClearField();
                GameOver(snakeData->isWin, snakeData->bestScore, snakeData->currentScore);
            }
        } else if (currentGame == CurrentGame::TETRIS) {
            if (tetrisData->state != State::GAME_OVER && tetrisData->state != State::EXIT) {
                if (tetrisData->state == State::START) {
                    StartWindowRendering(ui->TetrisInfoLabel);
                } else if (tetrisData->state == State::PAUSE) {
                    PauseWindowRendering(ui->TetrisInfoLabel);
                } else {
                    ui->TetrisInfoLabel->setText("");
                    TetrisRendering();
                }
            } else {
                ClearField();
                GameOver(false, tetrisData->bestScore, tetrisData->score);
            }
        }
    }

    void View::StartWindowRendering(QLabel *label) {
        label->setText("Press space to start");
        label->setStyleSheet("border: none;");
    }

    void View::PauseWindowRendering(QLabel *label) {
        label->setText(
                "Game on pause.<br> Press Tab to continue<br> or Esc to exit"
                );
    }

    void View::ClearField() {
        QPainter painter(this);
        painter.eraseRect(rect());
        painter.end();
    }

    void View::UpdateAll() {
        if (currentGame == CurrentGame::SNAKE) {
            UpdateSnakeModel();
        } else if (currentGame == CurrentGame::TETRIS) {
            UpdateTetrisModel();
        }

        repaint();
    }

    void View::UpdateSnakeModel() {
        snakeController->UpdateModelData(action);
        snakeData = &snakeController->GetModelData();
        action = PlayerAction::DEFAULT;
        ui->score_snake->setText(QString::number(snakeData->currentScore));
        ui->lvl_snake->setText(QString::number(snakeData->lvl));
        ui->bestScore_snake->setText(QString::number(snakeData->bestScore));

        if (snakeData->state == State::GAME_OVER || snakeData->state == State::EXIT) {
            timer->stop();
        }
    }

    void View::UpdateTetrisModel() {
        tetrisController->UpdateModelData(action);
        tetrisData = &tetrisController->GetModelData();
        action = PlayerAction::DEFAULT;
        ui->score_tetris->setText(QString::number(tetrisData->score));
        ui->lvl_tetris->setText(QString::number(tetrisData->lvl));
        ui->bestScore_tetris->setText(QString::number(tetrisData->bestScore));

        if (tetrisData->state == State::GAME_OVER || tetrisData->state == State::EXIT) {
            timer->stop();
        }
    }

    void View::TetrisRendering() {
        int shift = 1 * Properties::DOT_SIZE; //shift can be const and static
        QPainter painter(this);


        painter.setBrush(QColor(10, 30, 40));
        painter.setPen(QColor(0, 0, 0));

        painter.setBrush(Colors[0]);
        for (const auto &item : tetrisData->projectionTetromino.GetPosition()) {
            painter.drawRect((item.x) * Properties::DOT_SIZE + shift,
                             (item.y - 1) * Properties::DOT_SIZE + shift,
                             Properties::DOT_SIZE - 1,
                             Properties::DOT_SIZE - 1);
        }

        painter.setBrush(QColor(148, 195, 76));

        for (const auto &item : tetrisData->currentTetromino.GetPosition()) {
            painter.setBrush(Colors[(int) tetrisData->currentTetromino.GetShape()]);
            painter.drawRect(item.x * Properties::DOT_SIZE + shift,
                             (item.y - 1) * Properties::DOT_SIZE + shift,
                             Properties::DOT_SIZE - 1,
                             Properties::DOT_SIZE - 1);
        }

        for (const auto &item : tetrisData->nextTetromino.GetPosition()) {
            painter.setBrush(Colors[(int) tetrisData->nextTetromino.GetShape()]);
            painter.drawRect((item.x + 8) * Properties::DOT_SIZE + shift * 2,
                             (item.y + 2) * Properties::DOT_SIZE + shift * 2,
                             Properties::DOT_SIZE - 1,
                             Properties::DOT_SIZE - 1);
        }

        for (int i = 0; i < Properties::FIELD_HEIGHT; ++i) {
            for (int j = 0; j < Properties::FIELD_WIDTH; ++j) {
                if (tetrisData->tetrisField[i][j].first) {
                    painter.setBrush(Colors[(int) tetrisData->tetrisField[i][j].second]);
                    painter.drawRect(j * Properties::DOT_SIZE + shift,
                                     i * Properties::DOT_SIZE + shift,
                                     Properties::DOT_SIZE - 1,
                                     Properties::DOT_SIZE - 1);
                }
            }
        }
        painter.end();
    }

    void View::SnakeRendering() {
        int shift = 1 * Properties::DOT_SIZE;
        QPainter qp(this);

        QImage apple(appleImage);

        QRectF appleRect(snakeData->applePosition.x * Properties::DOT_SIZE + shift,
                         snakeData->applePosition.y * Properties::DOT_SIZE + shift,
                         Properties::DOT_SIZE, Properties::DOT_SIZE);
        QImage head(snakeHeadDefault);
        QImage body(snakePartImage);

        QRectF head_rect(snakeData->snakePosition[0].x * Properties::DOT_SIZE + shift,
                         snakeData->snakePosition[0].y * Properties::DOT_SIZE + shift,
                         Properties::DOT_SIZE, Properties::DOT_SIZE);

        QTransform transform;
        int rot = 0;
        if (snakeData->direction == Direction::Down) {
            rot = 180;
        } else if (snakeData->direction != Direction::Up) {
            rot = (snakeData->direction == Direction::Left ? -90 : 90);
        }

        head = head.transformed(transform.rotate(rot));

        qp.drawImage(appleRect, apple);

        for (std::size_t i = 0; i < snakeData->snakePosition.size(); ++i) {
            if (i == 0) {
                qp.drawImage(head_rect, head);
            } else {
                QRectF body_rect(snakeData->snakePosition[i].x * Properties::DOT_SIZE + shift,
                       snakeData->snakePosition[i].y * Properties::DOT_SIZE + shift,
                       Properties::DOT_SIZE - 1, Properties::DOT_SIZE - 1);
                qp.drawImage(body_rect, body);
            }
        }
        qp.end();
    }

    void View::GameOver(bool isWin, int bestScore, int score) {
        timer->stop();
        ui->stackedWidget->setCurrentIndex(2);

        if (isWin) {
            ui->gameStatus->setText("YOU WON!");
        } else {
            ui->gameStatus->setText("GAME OVER!");
        }

        ui->score_end->setText(QString::number(score));
        ui->bestScore_end->setText(QString::number(bestScore));
    }
    void View::playBtnClicked() {
        if (currentGame == CurrentGame::TETRIS) {
            tetrisController->SetModelDataDefault();
            tetrisData = &tetrisController->GetModelData();
            ui->stackedWidget->setCurrentIndex(1);
            timer->start(10);
        } else if (currentGame == CurrentGame::SNAKE) {
            snakeController->SetModelDataDefault();
            snakeData = &snakeController->GetModelData();
            ui->stackedWidget->setCurrentIndex(3);
            timer->start(10);
        } else if (currentGame == CurrentGame::NONE) {
            ui->stackedWidget->setCurrentIndex(0);
        }
    }

    void View::closeGameClicked() {
        currentGame = CurrentGame::NONE;
        ui->stackedWidget->setCurrentIndex(0);
    }

    void View::startTetrisBtnClicked() {
        currentGame = CurrentGame::TETRIS;
        tetrisController->SetModelDataDefault();
        tetrisData = &tetrisController->GetModelData();
        ui->stackedWidget->setCurrentIndex(1);
        timer->start(10);
    }

    void View::startSnakeBtnClicked() {
        currentGame = CurrentGame::SNAKE;
        snakeController->SetModelDataDefault();
        snakeData = &snakeController->GetModelData();
        ui->stackedWidget->setCurrentIndex(3);
        timer->start(10);
    }
    void View::exitBtnClicked() {
        close();
    }
    void View::SetupButtons() {
        connect(ui->again, SIGNAL(clicked()), this, SLOT(playBtnClicked()));
        connect(ui->snakeBtn, SIGNAL(clicked()), this, SLOT(startSnakeBtnClicked()));
        connect(ui->tetrisBtn, SIGNAL(clicked()), this, SLOT(startTetrisBtnClicked()));
        connect(ui->exitBtn, SIGNAL(clicked()), this, SLOT(exitBtnClicked()));
        connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(closeGameClicked()));
    }
}// namespace s21
