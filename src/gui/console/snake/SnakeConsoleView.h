#ifndef SNAKE2_SNAKECONSOLEVIEW_H
#define SNAKE2_SNAKECONSOLEVIEW_H

#include "../../../controller/SnakeController.h"
#include "../common-code/BaseView.h"

namespace s21 {
class SnakeConsoleView : public BaseView {
public:
    explicit SnakeConsoleView(SnakeController *controller);
    ~SnakeConsoleView() = default;

    void Start() override;

private:
    void Rendering();
    void SnakeMainLoop();
    void ModelConnect();
    void GameRendering();

    PlayerAction action{};
    SnakeData *snakeData;
    SnakeController *snakeController;
};


}


#endif//SNAKE2_SNAKECONSOLEVIEW_H
