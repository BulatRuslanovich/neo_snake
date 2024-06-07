#ifndef SNAKE2_SNAKECONTROLLER_H
#define SNAKE2_SNAKECONTROLLER_H

#include "../brick_game/snake/SnakeModel.h"

namespace s21 {
    class SnakeController {
    public:
        explicit SnakeController(SnakeModel *model) : model(model) {}
        ~SnakeController() = default;

        void UpdateModelData(PlayerAction action = PlayerAction::UP) {
            model->UpdateModelData(action);
        }

        void SetModelDataDefault() {
            model->SetDefaultData();
        }

        SnakeData &GetModelData() {
            return model->GetModelData();
        }

    private:
        SnakeModel *model;
    };
}// namespace s21

#endif//SNAKE2_SNAKECONTROLLER_H
