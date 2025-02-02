#include <gtest/gtest.h>

#include <cstdio>
#include <iostream>

#include "brick_game/snake/backend_snake.h"
#include "gui/cli/snake/frontend_snake.h"

/** @file */

namespace s21 {
TEST(Constructor, Score) {
  auto test = SnakeGame();
  EXPECT_EQ(test.get_score(), 0);
}

TEST(Constructor, speed) {
  auto test = SnakeGame();
  EXPECT_EQ(test.getSpeed(), 0);
}

TEST(Score, changelevel) {
  auto test = SnakeGame();
  test.set_high_score(5);
  test.set_score(10);
  test.up_score();
  EXPECT_EQ(test.get_score(), 10);
}

TEST(Userinput, add) {
  SnakeGame test;
  test.userInput(Start);
  EXPECT_EQ(test.get_state(), MOVE);
  test.userInput(Pause);
  EXPECT_EQ(test.get_state(), ADD_STATE);
  test.userInput(Pause);
  EXPECT_EQ(test.get_state(), MOVE);
  test.userInput(Terminate);
  test.updateCurrentState();
  EXPECT_EQ(test.get_state(), GAME_OVER);
}

TEST(MoveSnake, turn) {
  SnakeGame test;
  test.set_state(MOVE);
  test.userInput(Up);
  EXPECT_EQ(test.is_moveSnake(), Up);
  test.userInput(Left);
  test.is_moveSnake2();
  EXPECT_EQ(test.is_moveSnake(), Left);
  test.userInput(Down);
  test.is_moveSnake2();
  EXPECT_EQ(test.is_moveSnake(), Down);
  test.userInput(Right);
  test.is_moveSnake2();
  EXPECT_EQ(test.is_moveSnake(), Right);
}

TEST(Fsm, state) {
  auto test = SnakeGame();
  test.update_game();
  test.set_state(MOVE);
  test.update_game();
  test.set_state(CREATE_APPLE);
  test.update_game();
  test.set_state(GAME_OVER);
  test.update_game();
  test.game_over();
  test.load_score();
  test.save_score();
  EXPECT_EQ(test.get_score(), 0);
}

}  // namespace s21
