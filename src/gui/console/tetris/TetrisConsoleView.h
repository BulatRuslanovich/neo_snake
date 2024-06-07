#ifndef SNAKE2_TETRISCONSOLEVIEW_H
#define SNAKE2_TETRISCONSOLEVIEW_H

#include "../../../controller/TetrisController.h"
#include "../common-code/BaseView.h"

namespace s21 {
    class TetrisConsoleView : public BaseView {
    public:
        explicit TetrisConsoleView(TetrisController *controller = nullptr);
        void Start() override;

    private:
        PlayerAction action;

        TetrisController *tetrisController;
        TetrisData *tetrisData;

        void TetrisMainLoop();
        void ModelConnect();
        void GameRendering();
        void Rendering();
    };
}




#endif//SNAKE2_TETRISCONSOLEVIEW_H
