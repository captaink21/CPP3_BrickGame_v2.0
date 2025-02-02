#ifndef FRONTEND_SNAKE_H_
#define FRONTEND_SNAKE_H_

#include <locale.h>
#include <ncurses.h>

#include <iostream>

#include "../../../brick_game/snake/backend_snake.h"

namespace s21 {

class SnakeView {
 public:
  void print_game(const GameInfo_t &game_info);
  void initialization();
  void deinitialization();
  void time_game(int speed);
  void print_info(const GameInfo_t &game_info);
  void button_pause();
  void button_start();
};

}  // namespace s21

#endif  // FRONTEND_SNAKE_H_