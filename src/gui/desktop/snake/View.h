#ifndef CPP3_BRICKGAME_V2_VIEW_H
#define CPP3_BRICKGAME_V2_VIEW_H

#include <QCoreApplication>
#include <QDebug>
#include <QKeyEvent>
#include <QLabel>
#include <QMainWindow>
#include <QPainter>
#include <QString>
#include <QTimer>
#include <QWidget>

#include "../../../controller/SnakeController.h"
#include "../../../controller/TetrisController.h"


QT_BEGIN_NAMESPACE
namespace Ui {
    class View;
}
QT_END_NAMESPACE

namespace s21 {
    enum class CurrentGame {
        NONE,
        SNAKE,
        TETRIS
    };

    class View : public QMainWindow {
        Q_OBJECT

    public:
        explicit View(SnakeController *snakeController, TetrisController *tetrisController, QWidget *parent = nullptr);
        ~View() override;

        const QColor Colors[8] = {
                QColor(147, 147, 147),
                QColor(255, 0, 0),
                QColor(103, 250, 0),
                QColor(5, 240, 250),
                QColor(250, 5, 249),
                QColor(250, 235, 5),
                QColor(250, 124, 5),
                QColor(5, 20, 250),
        };

    protected:
        void keyPressEvent(QKeyEvent *) override;
        void paintEvent(QPaintEvent *event) override;

    private slots:
        void closeGameClicked();
        void startTetrisBtnClicked();
        void startSnakeBtnClicked();
        void exitBtnClicked();
        void playBtnClicked();

    private:
        QTimer *timer{};
        CurrentGame currentGame;
        PlayerAction action;
        SnakeData *snakeData;
        TetrisData *tetrisData;
        SnakeController *snakeController;
        TetrisController *tetrisController;
        Ui::View *ui{};
        const QString appPath = QCoreApplication::applicationDirPath() + "/..";
        const QImage appleImage = QImage(appPath + "/src/img/apple.png");
        const QImage snakePartImage = QImage(appPath + "/src/img/body.png");
        const QImage snakeHeadDefault= QImage(appPath + "/src/img/head_default.png");

        static void StartWindowRendering(QLabel *label);
        static void PauseWindowRendering(QLabel *label);
        void ClearField();
        void GameOver(bool isWin, int lvl, int score);
        void UpdateAll();
        void UpdateSnakeModel();
        void UpdateTetrisModel();
        void TetrisRendering();
        void SnakeRendering();
        void SetupButtons();

    };
}// namespace s21

#endif//CPP3_BRICKGAME_V2_VIEW_H
