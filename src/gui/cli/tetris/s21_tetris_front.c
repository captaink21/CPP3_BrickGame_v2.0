#include "s21_tetris_front.h"

#include "../../../brick_game/tetris/s21_tetris_back.h"

/** @file */

void print_corner(int left_x, int right_x, int up_y, int down_y) {
  mvaddch(left_x, up_y, ACS_ULCORNER);
  mvaddch(left_x, right_x, ACS_URCORNER);
  mvaddch(down_y, up_y, ACS_LLCORNER);
  mvaddch(down_y, right_x, ACS_LRCORNER);
}

void print_game(GameInfo_t* game, Figure* action_figure) {
  int sym = 0;
  for (int i = 1; i < POLE_HEIGHT - 1; i++) {
    for (int j = 1; j < POLE_WIDTH - 1; j++) {
      sym = 0;
      if (game->field[i][j] != 0) {
        sym = game->field[i][j];
      } else {
        int x = j - action_figure->x;
        int y = i - action_figure->y;
        if (x >= 0 && x <= 5 && y >= 0 && y < 5) {
          if (action_figure->figure[y][x] != 0) {
            sym = action_figure->figure[y][x];
          }
        }
      }

      if (sym == 0) {
        mvaddstr(i, j * 2, "  ");

      } else {
        mvaddstr(i, j * 2, "#");
      }
    }
  }

  print_corner(0, 22, 0, 21);
}

void print_newfigure(GameInfo_t* game) {
  for (int i = 1; i < 4; i++) {
    for (int j = 0; j < 5; j++) {
      if (game->next[i][j] != 0) {
        mvaddstr(i + 7, (j + 12) * 2, "#");

      } else {
        mvaddstr(i + 7, (j + 12) * 2, "  ");
      }
    }
  }
}

void print_info(GameInfo_t* game) {
  mvprintw(20, 23, "Maximum score");
  mvprintw(21, 23, "%d", game->high_score);

  mvprintw(18, 23, "Current score");
  mvprintw(19, 23, "%d", game->score);

  mvprintw(13, 23, "Current Level");
  mvprintw(14, 23, "%d", game->level);

  if (game->next != NULL) {
    mvprintw(5, 23, "New figure");
    print_newfigure(game);
  }
  mvprintw(1, 23, "Action  UP");
  mvprintw(2, 23, "Pause   space");
  mvprintw(3, 23, "Exit    q");
}

void button_pause() {
  while (getch() != ' ') {
    mvaddstr(12, 4, "Pause");
    refresh();
  }
}

void button_start() {
  while (getch() != '\n') {
    mvaddstr(10, 4, "Let's play tetris -> Enter");
    refresh();
  }
}
