cmake_minimum_required(VERSION 3.27)
project(CPP3_BrickGame_v2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/home/bulatruslanovich/Desktop/Apps/Qt/6.5.3/gcc_64")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS PrintSupport REQUIRED)

include_directories(src/brick_game/snake)
include_directories(src/brick_game/tetris)
include_directories(src/brick_game/common-code)
include_directories(src/controller)
include_directories(src/gui/console)
include_directories(src/gui/desktop)
include_directories(src/gui/console/common-code)
include_directories(src/gui/console/snake)
include_directories(src/gui/console/tetris)

add_executable(consoleBrickGame
        src/brick_game/snake/SnakeModel.cpp
        src/brick_game/snake/SnakeModel.h
        src/brick_game/tetris/TetrisModel.cpp
        src/brick_game/tetris/TetrisModel.h
        src/brick_game/tetris/Tetromino.h
        src/brick_game/tetris/Tetromino.cpp
        src/controller/SnakeController.h
        src/controller/TetrisController.h
        src/gui/console/snake/SnakeConsoleView.h
        src/gui/console/snake/SnakeConsoleView.cpp
        src/gui/console/common-code/ConsoleView.cpp
        src/gui/console/common-code/ConsoleView.h
        src/gui/console/main.cpp
        src/gui/console/common-code/BaseView.cpp
        src/gui/console/common-code/BaseView.h
        src/brick_game/common-code/Constants.h
        src/gui/console/tetris/TetrisConsoleView.cpp
        src/brick_game/common-code/SaveScoreManager.h
)

target_link_libraries(consoleBrickGame ncurses)

add_executable(desktopBrickGame
        src/brick_game/snake/SnakeModel.cpp
        src/brick_game/snake/SnakeModel.h
        src/controller/SnakeController.h
        src/brick_game/tetris/TetrisModel.h
        src/brick_game/tetris/TetrisModel.cpp
        src/brick_game/tetris/Tetromino.h
        src/brick_game/tetris/Tetromino.cpp
        src/controller/TetrisController.h
        src/brick_game/common-code/Constants.h
        src/brick_game/common-code/SaveScoreManager.h
        src/gui/desktop/snake/main.cpp
        src/gui/desktop/snake/View.h
        src/gui/desktop/snake/View.cpp
)


target_link_libraries(desktopBrickGame PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(desktopBrickGame PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(desktopBrickGame)
endif()