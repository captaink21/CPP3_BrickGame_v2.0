
#include "./brick_game/tetris/s21_tetris_back.h"
#include "./gui/cli/tetris/s21_tetris_front.h"

/** @file */

int main() {
  int ch = getch();
  UserAction_t player;
  player = Start;

  GameInfo_t* create_tetris = NULL;

  State state;
  state = START;

  Figure* action_figure;

  srand(time(NULL));

  initscr();
  curs_set(0);
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  timeout(0);
  scrollok(stdscr, TRUE);

  create_tetris = new_game();
  action_figure = create_figure();

  button_start();

  while (ch != 'q') {
    ch = getch();
    switch (ch) {
      case ' ':
        player = Pause;
        break;

      case KEY_UP:
        player = Action;
        break;
      case KEY_DOWN:
        player = Down;
        break;
      case KEY_LEFT:
        player = Left;
        break;
      case KEY_RIGHT:
        player = Right;
        break;

      default:
        player = Up;
        break;
    }

    sigact(create_tetris, action_figure, player, &state);
    if (state != PAUSE) {
      print_game(create_tetris, action_figure);
      print_info(create_tetris);

      refresh();
    } else
      button_pause();

    if (state != SHIFTING && player != Right && player != Left &&
        player != Down && player != Action)
      delay_output(500 / (create_tetris->level + 1));
    else if (state != ATTACHING)
      delay_output(1);
    else
      delay_output(40);

    // usleep(250000 / create_tetris->level + 1);
  }
  score(create_tetris);
  free_figure(action_figure);
  free_game(create_tetris);
  endwin();
  return 0;
}
