#include "frontend_snake.h"

/** @file */

namespace s21 {

void SnakeView::initialization() {
  setlocale(LC_ALL, "");
  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);
}

void SnakeView::deinitialization() { endwin(); }

void print_corner(int left_x, int right_x, int up_y, int down_y) {
  mvaddch(left_x, up_y, ACS_ULCORNER);
  mvaddch(left_x, right_x, ACS_URCORNER);
  mvaddch(down_y, up_y, ACS_LLCORNER);
  mvaddch(down_y, right_x, ACS_LRCORNER);
}

void SnakeView::button_pause() {
  // while (getch() != ' ') {
  mvaddstr(12, 4, "Pause");
  refresh();
  // }
}

void SnakeView::button_start() {
  // while (getch() != '\n') {
  mvaddstr(10, 4, "Are you ready? -> Enter");
  refresh();
  // }
}

void SnakeView::print_info(const GameInfo_t &game_info) {
  mvprintw(2, 23, "Pause   space");
  mvprintw(3, 23, "Exit    q");
  mvprintw(4, 23, "Left   ←");
  mvprintw(5, 23, "Right  →");
  mvprintw(6, 23, "Up     ↑");
  mvprintw(7, 23, "Down   ↓");

  mvprintw(20, 23, "Maximum score");
  mvprintw(21, 23, "%d", game_info.high_score);

  mvprintw(18, 23, "Current score");
  mvprintw(19, 23, "%d", game_info.score);

  mvprintw(13, 23, "Current Level");
  mvprintw(14, 23, "%d", game_info.level);

  mvprintw(15, 23, "Current speed");
  mvprintw(16, 23, "%d", game_info.speed);
}

void SnakeView::print_game(const GameInfo_t &game_info) {
  clear();
  if (game_info.action_view == START_VIEW) {
    button_start();
    return;
  }
  print_corner(0, 22, 0, 21);

  for (int y = 0; y < static_cast<int>(game_info.field.size()); y++) {
    for (int x = 0; x < static_cast<int>(game_info.field[y].size()); x++) {
      if (game_info.field[y][x] == 1) {
        mvprintw(y + 1, (x + 1) * 2, "#");
      } else if (game_info.field[y][x] == 2) {
        mvprintw(y + 1, (x + 1) * 2, "*");
      } else {
        mvprintw(y + 1, (x + 1) * 2, " ");
      }
    }
  }

  print_info(game_info);

  if (game_info.action_view == PAUSE_VIEW) {
    button_pause();
    return;
  }
  if (game_info.action_view != START_VIEW ||
      game_info.action_view != PAUSE_VIEW) {
    time_game(game_info.speed);

    refresh();
  }
}

void SnakeView::time_game(int speed) {
  if (speed > 10) {
    speed = 10;
  }
  if (speed < 1) {
    speed = 1;
  }
  int delay = 1000 / speed;
  timeout(delay);
}

}  // namespace s21