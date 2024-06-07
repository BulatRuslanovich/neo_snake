//
// Created by bulatruslanovich on 03/06/2024.
//

#ifndef SNAKE2_TETRISCONTROLLER_H
#define SNAKE2_TETRISCONTROLLER_H

#include "../brick_game/tetris/TetrisModel.h"

namespace s21 {
    class TetrisController {
    public:
        explicit TetrisController(TetrisModel *model) : model(model) {}
        ~TetrisController() = default;
        
        void UpdateModelData(PlayerAction action = PlayerAction::UP) {
            model->UpdateModelData(action);
        }
        
        void SetModelDataDefault() {
            model->SetDefaultData();
        }
        
        TetrisData &GetModelData() {
            return model->GetModelData();
        }
        
    private:
        TetrisModel *model;
    };
}// namespace s21

#endif//SNAKE2_TETRISCONTROLLER_H
