#include <gtest/gtest.h>

#include <thread>

#include "../brick_game/snake/SnakeModel.h"

class SnakeGameTest : public ::testing::Test {
protected:
  s21::SnakeModel snakeModel;
  s21::SnakeData *snakeData{};
};

TEST_F(SnakeGameTest, MoveSnakeUp) {
  snakeModel.SetDefaultData();
  snakeData = &snakeModel.GetModelData();
  EXPECT_EQ(snakeData->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snakeData->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snakeData->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::UP);
  EXPECT_EQ(snakeData->direction, s21::Direction::Up);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snakeData->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, MoveSnakeLeft) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::LEFT);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::Left);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, MoveSnakeRight) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::RIGHT);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::Right);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, MoveSnakeAround) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::RIGHT);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::Right);
  snakeModel.UpdateModelData(s21::PlayerAction::DOWN);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::Down);
  snakeModel.UpdateModelData(s21::PlayerAction::LEFT);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::Left);
  snakeModel.UpdateModelData(s21::PlayerAction::UP);
  EXPECT_EQ(snake_game_data_->direction, s21::Direction::Up);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, AutoMovingUp) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, AutoMovingLeft) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::LEFT);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, AutoMovingRight) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::RIGHT);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, AutoMovingDown) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::RIGHT);
  snakeModel.UpdateModelData(s21::PlayerAction::DOWN);
  std::this_thread::sleep_for(std::chrono::milliseconds(510));
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, SetAndCancelPause) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::TAB);
  EXPECT_EQ(snake_game_data_->state, s21::State::PAUSE);
  snakeModel.UpdateModelData(s21::PlayerAction::TAB);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  snakeModel.UpdateModelData(s21::PlayerAction::ESC);
  EXPECT_EQ(snake_game_data_->state, s21::State::EXIT);
}

TEST_F(SnakeGameTest, GameOver) {
  snakeModel.SetDefaultData();
  s21::SnakeData *snake_game_data_ = &snakeModel.GetModelData();
  EXPECT_EQ(snake_game_data_->state, s21::State::START);
  snakeModel.UpdateModelData(s21::PlayerAction::SPACE);
  EXPECT_EQ(snake_game_data_->state, s21::State::INIT);
  snakeModel.UpdateModelData(s21::PlayerAction::DEFAULT);
  EXPECT_EQ(snake_game_data_->state, s21::State::MOVING);
  while (snake_game_data_->state != s21::State::GAME_OVER) {
    snakeModel.UpdateModelData(s21::PlayerAction::UP);
  }
}
