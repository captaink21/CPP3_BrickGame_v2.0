#include <ncurses.h>

#include "brick_game/snake/backend_snake.h"
#include "gui/cli/snake/frontend_snake.h"

/** @file */

int main() {
  s21::SnakeGame model;
  s21::SnakeView view;

  view.initialization();

  while (1) {
    int ch = getch();
    switch (ch) {
      case '\n':
        model.userInput(s21::Start);
        break;
      case ' ':
        model.userInput(s21::Pause);
        break;
      case 'q':
        model.userInput(s21::Terminate);
        break;
      case KEY_LEFT:
        model.userInput(s21::Left);
        break;
      case KEY_RIGHT:
        model.userInput(s21::Right);
        break;
      case KEY_UP:
        model.userInput(s21::Up);
        break;
      case KEY_DOWN:
        model.userInput(s21::Down);
        break;
      default:
        break;
    }

    model.update_game();

    s21::GameInfo_t info = model.updateCurrentState();

    view.print_game(info);

    if (model.game_over()) break;
  }

  view.deinitialization();

  std::cout << "You score: " << model.updateCurrentState().score << std::endl;
  std::cout << "High score: " << model.updateCurrentState().high_score
            << std::endl;
  return 0;
}