#include "s21_tetris_back.h"

#include <ncurses.h>

#include "../../gui/cli/tetris/s21_tetris_front.h"

/** @file */

const char *checsomething() {
  static const char *msg = "ПППППОООООДДДДДКККЛЛЛЮЮЮЧЧАААЕЕЕТТТТСССЯЯЯ\n";
  return msg;
}

int random_figure(int min, int max) { return rand() % (max - min + 1) + min; }

void copy_matrix(int (*src)[5], int **dst, int rows, int cols) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      dst[i][j] = src[i][j];
    }
  }
}

void new_next_figure(GameInfo_t *game) {
  static int i_block[FIGURE_SIZE][FIGURE_SIZE] = {{0, 0, 0, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 1, 0, 0}};
  static int l_block[FIGURE_SIZE][FIGURE_SIZE] = {{0, 0, 0, 0, 0},
                                                  {0, 1, 1, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 0, 0, 0}};
  static int j_block[FIGURE_SIZE][FIGURE_SIZE] = {{0, 0, 0, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 1, 1, 0, 0},
                                                  {0, 0, 0, 0, 0}};
  static int o_block[FIGURE_SIZE][FIGURE_SIZE] = {{0, 0, 0, 0, 0},
                                                  {0, 1, 1, 0, 0},
                                                  {0, 1, 1, 0, 0},
                                                  {0, 0, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}};
  static int z_block[FIGURE_SIZE][FIGURE_SIZE] = {{0, 0, 0, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 1, 1, 0, 0},
                                                  {0, 1, 0, 0, 0},
                                                  {0, 0, 0, 0, 0}};
  static int t_block[FIGURE_SIZE][FIGURE_SIZE] = {{0, 0, 0, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 1, 1, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 0, 0, 0}};
  static int s_block[FIGURE_SIZE][FIGURE_SIZE] = {{0, 0, 0, 0, 0},
                                                  {0, 1, 0, 0, 0},
                                                  {0, 1, 1, 0, 0},
                                                  {0, 0, 1, 0, 0},
                                                  {0, 0, 0, 0, 0}};
  int l = random_figure(1, 7);
  switch (l) {
    case 1:
      copy_matrix(i_block, (int **)game->next, FIGURE_SIZE, FIGURE_SIZE);
      break;
    case 2:
      copy_matrix(l_block, (int **)game->next, FIGURE_SIZE, FIGURE_SIZE);
      break;
    case 3:
      copy_matrix(j_block, (int **)game->next, FIGURE_SIZE, FIGURE_SIZE);
      break;
    case 4:
      copy_matrix(o_block, (int **)game->next, FIGURE_SIZE, FIGURE_SIZE);
      break;
    case 5:
      copy_matrix(z_block, (int **)game->next, FIGURE_SIZE, FIGURE_SIZE);
      break;
    case 6:
      copy_matrix(t_block, (int **)game->next, FIGURE_SIZE, FIGURE_SIZE);
      break;
    case 7:
      copy_matrix(s_block, (int **)game->next, FIGURE_SIZE, FIGURE_SIZE);
      break;
  }
  // printf("Следующая фигура выбрана и установлена\n");
}

void allocation_next_figure(GameInfo_t *game) {
  game->next = (int **)calloc(sizeof(int *), FIGURE_SIZE);
  // if (!game->next) {
  //   fprintf(stderr, "Ошибка: не удалось выделить память для game->next\n");
  // }
  for (int i = 0; i < FIGURE_SIZE; i++) {
    game->next[i] = (int *)calloc(sizeof(int), FIGURE_SIZE);
    // if (!game->next[i]) {
    //   fprintf(stderr, "Ошибка: не удалось выделить память для
    //   game->next[%d]\n",
    //           i);
    // }
  }

  new_next_figure(game);
  // printf("Следующая фигура создана\n");
}

void free_next_figure(GameInfo_t *game) {
  if (game->next) {
    for (int i = 0; i < 5; i++) {
      if (game->next[i]) {
        free(game->next[i]);
      }
    }
    free(game->next);
  }
}

void create_field(GameInfo_t *game) {
  game->field = (int **)calloc(sizeof(int *), POLE_HEIGHT);
  // if (!game->field) {
  //   printf("Ошибка: не удалось выделить память для game->field\n");
  // }
  for (int i = 0; i < POLE_HEIGHT; i++) {
    game->field[i] = (int *)calloc(sizeof(int), POLE_WIDTH);
    // if (!game->field[i]) {
    //   printf("Ошибка: не удалось выделить память для game->field[\n");
    // }
  }
  // printf("Поле игры создано\n");
}

void free_field(GameInfo_t *game) {
  if (game->field) {
    for (int i = 0; i < POLE_HEIGHT; i++) {
      if (game->field[i]) {
        free(game->field[i]);
      }
    }
    free(game->field);
  }
}

void score(GameInfo_t *game) {
  FILE *result = fopen("score.txt", "r");

  if (result == NULL)

  {
    result = fopen("score.txt", "w");
    if (result != NULL) fprintf(result, "%d", game->score);
    fclose(result);
  } else {
    int record = 0;
    fscanf(result, "%d", &record);

    fclose(result);

    if (record < game->high_score) {
      result = fopen("score.txt", "w");
      fprintf(result, "%d", game->high_score);
      fclose(result);
    }
    if (record < game->score) {
      result = fopen("score.txt", "w");
      fprintf(result, "%d", game->score);
      fclose(result);
    }
    if (game->high_score < game->score) {
      game->high_score = game->score;
    }
  }
}

void delete_score() {
  FILE *result = fopen("score.txt", "w");
  int zero = 0;
  fprintf(result, "%d", zero);
  fclose(result);
}

GameInfo_t *new_game() {
  // printf("Начало new_game\n");
  GameInfo_t *game = (GameInfo_t *)calloc(sizeof(GameInfo_t), 1);
  // if (!game) {
  //   printf("Ошибка: не удалось выделить память для game\n");
  // }
  // printf("Игра создана2\n");
  create_field(game);
  // printf("Поле создано\n");
  allocation_next_figure(game);
  // printf("Следующая фигура выделена\n");
  game->score = 0;
  game->level = 1;
  game->speed = 1;
  game->pause = 0;

  FILE *file = fopen("score.txt", "r");
  if (file) {
    // printf("Корректировка на открытие score.txt\n");
    fscanf(file, "%d", &(game->high_score));
    fclose(file);
    // printf("Файл score.txt прочитан и закрыт\n");
  } else {
    // printf("Файл score.txt не найден\n");
    game->high_score = 0;
  }
  // }

  return game;
}

void free_game(GameInfo_t *game) {
  free_field(game);
  free_next_figure(game);
  free(game);
}

void move_down(Figure *action_figure) { action_figure->y++; }

void move_up(Figure *action_figure) { action_figure->y--; }

void move_left(Figure *action_figure) { action_figure->x--; }

void move_right(Figure *action_figure) { action_figure->x++; }

int colision(Figure *action_figure, GameInfo_t *game) {
  int error = 0;
  for (int i = 0; i < FIGURE_SIZE && error == 0; i++) {
    for (int j = 0; j < FIGURE_SIZE && error == 0; j++) {
      if (action_figure->figure[i][j] != 0) {
        int x = action_figure->x + j;
        int y = action_figure->y + i;

        if (x < 1 || x >= 11 || y < 0 || y >= 21) {
          error = 1;
        } else if (game->field[y][x] != 0) {
          error = 1;
        }
      }
    }
  }
  return error;
}

void field_figure(Figure *action_figure, GameInfo_t *game) {
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      if (action_figure->figure[i][j] != 0) {
        int x = action_figure->x + j;
        int y = action_figure->y + i;
        game->field[y][x] = action_figure->figure[i][j];
      }
    }
  }
}

int line_full(int i, GameInfo_t *game) {
  int sum = 0;
  int line = 0;
  for (int j = 1; j < 11; j++) {
    if (game->field[i][j] != 0) {
      sum = sum + 1;
    }
  }
  if (sum == 10) line = 1;
  return line;
}

void down_line(int i, GameInfo_t *game) {
  if (i == 1) {
    for (int j = 1; j < 11; j++) {
      game->field[i][j] = 0;
    }
  } else {
    for (int c = i; c > 1; c--) {
      for (int j = 1; j < 11; j++) {
        game->field[c][j] = game->field[c - 1][j];
      }
    }
  }
}

int throw_line(GameInfo_t *game) {
  int sum = 0;
  for (int i = 1; i < 21; i++) {
    for (; line_full(i, game);) {
      down_line(i, game);
      sum++;
    }
  }
  if (sum == 1) {
    sum = 100;
  } else if (sum == 2) {
    sum = 300;
  } else if (sum == 3) {
    sum = 700;
  } else if (sum == 4) {
    sum = 1500;
  }
  return sum;
}

void restart(GameInfo_t *game) {
  for (int i = 0; i < POLE_HEIGHT; i++) {
    for (int j = 1; j < 11; j++) {
      game->field[i][j] = 0;
    }
  }
  score(game);
  game->score = 0;
  game->level = 1;
  game->speed = 1;
  game->pause = 0;
}

Figure *create_figure() {
  Figure *block = (Figure *)calloc(sizeof(Figure), 1);
  // printf("create_figure1/3\n");
  // if (!block) {
  //   fprintf(stderr, "Ошибка: не удалось выделить память для block\n");
  // }

  block->figure = (int **)calloc(sizeof(int *), FIGURE_SIZE);
  // printf("create_figure2/3\n");
  // if (!block->figure) {
  //   fprintf(stderr, "Ошибка: не удалось выделить память для
  //   block->figure\n"); free(block);
  // }

  for (int i = 0; i < FIGURE_SIZE; i++) {
    block->figure[i] = (int *)calloc(sizeof(int), FIGURE_SIZE);
    // if (!block->figure[i]) {
    //   fprintf(stderr,
    //           "Ошибка: не удалось выделить память для block->figure[%d]\n",
    //           i);
    // }
  }
  // printf("create_figure3/3\n");
  return block;
}

void free_figure(Figure *block) {
  if (block && block->figure) {
    for (int i = 0; i < FIGURE_SIZE; i++) {
      if (block->figure[i]) {
        free(block->figure[i]);
      }
    }
    free(block->figure);
    free(block);
  }
}

void figure_on_field(Figure *action_figure, GameInfo_t *game) {
  action_figure->y = 0;
  action_figure->x = 3;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      action_figure->figure[i][j] = game->next[i][j];
    }
  }
}

Figure *transpose_figure(Figure *action_figure) {
  Figure *transpose_figure = create_figure();
  transpose_figure->x = action_figure->x;
  transpose_figure->y = action_figure->y;
  for (int i = 0; i < FIGURE_SIZE; i++) {
    for (int j = 0; j < FIGURE_SIZE; j++) {
      transpose_figure->figure[i][j] = (action_figure->figure[j][4 - i]);
    }
  }
  return transpose_figure;
}

void user_input(UserAction_t action, Figure *action_figure, GameInfo_t *game,
                State *state) {
  switch (action) {
    case Right:
      move_right(action_figure);
      if (colision(action_figure, game)) {
        move_left(action_figure);
      }
      break;
    case Left:
      move_left(action_figure);
      if (colision(action_figure, game)) {
        move_right(action_figure);
      }
      break;
    case Down:

      move_down(action_figure);

      if (colision(action_figure, game)) {
        move_up(action_figure);
      }
      break;
    case Terminate:
      *state = GAMEOVER;
      break;
    case Action: {
      Figure *transpose = transpose_figure(action_figure);
      if (colision(transpose, game)) {
        free_figure(transpose);
      } else {
        for (int i = 0; i < FIGURE_SIZE; i++) {
          for (int j = 0; j < FIGURE_SIZE; j++) {
            action_figure->figure[i][j] = transpose->figure[i][j];
          }
        }
        free_figure(transpose);
      }
      break;
    }
    case Pause:
      if (*state == PAUSE) {
        *state = MOVING;
      } else
        *state = PAUSE;
      break;
    default:

      *state = SHIFTING;

      break;
  }
}

void table_level(GameInfo_t *game) {
  if (game->score >= 0 && 600 > game->score) game->level = 1;
  if (game->score >= 600 && 1200 > game->score) game->level = 2;
  if (game->score >= 1200 && 1800 > game->score) game->level = 3;
  if (game->score >= 1800 && 2400 > game->score) game->level = 4;
  if (game->score >= 2400 && 3000 > game->score) game->level = 5;
  if (game->score >= 3000 && 3600 > game->score) game->level = 6;
  if (game->score >= 3600 && 4200 > game->score) game->level = 7;
  if (game->score >= 4200 && 4800 > game->score) game->level = 8;
  if (game->score >= 4800 && 5400 > game->score) game->level = 9;
  if (game->score >= 5400) game->level = 10;
  game->speed = game->level;
}

typedef void (*action_fsm)(params_t *prms);

void sigact(GameInfo_t *game, Figure *action_figure, UserAction_t action,
            State *state) {
  params_t prms;
  action_fsm act = NULL;
  prms.game = game;
  prms.action_figure = action_figure;

  prms.action = action;
  prms.state = state;

  action_fsm fsm_table[7][7] = {
      //{START, SPAWN, MOVING, SHIFTING, ATTACHING, GAMEOVER},
      {state_start, NULL, state_start, NULL, NULL, NULL, NULL},         // START
      {state_spawn, NULL, NULL, state_spawn, NULL, NULL, state_spawn},  // SPAWN
      {state_moving, NULL, NULL, state_moving, NULL, state_moving,
       NULL},  // MOVING
      {state_shifting, NULL, NULL, state_shifting, NULL, state_shifting,
       NULL},  // SHIFTING
      {state_attaching, NULL, state_attaching, NULL, NULL, NULL,
       NULL},  // ATTACHING
      {state_gameover, state_gameover, NULL, NULL, NULL, NULL,
       NULL},                                                        // GAMEOVER
      {state_pause, state_gameover, NULL, NULL, NULL, NULL, NULL}};  // PAUSE

  act = fsm_table[*state][0];

  if (act) act(&prms);
}

void state_start(params_t *prms) { *(prms->state) = SPAWN; }

void state_spawn(params_t *prms) {
  figure_on_field(prms->action_figure, prms->game);
  allocation_next_figure(prms->game);
  if (colision(prms->action_figure, prms->game)) {
    *(prms->state) = GAMEOVER;
  } else {
    *(prms->state) = MOVING;
  }
}

void state_moving(params_t *prms) {
  user_input(prms->action, prms->action_figure, prms->game, prms->state);
  table_level(prms->game);
  if (colision(prms->action_figure, prms->game)) {
    move_up(prms->action_figure);
    *(prms->state) = ATTACHING;
  }
}

void state_shifting(params_t *prms) {
  if (colision(prms->action_figure, prms->game)) {
    *(prms->state) = ATTACHING;
  } else {
    move_down(prms->action_figure);
    *(prms->state) = MOVING;
  }
}

void state_attaching(params_t *prms) {
  field_figure(prms->action_figure, prms->game);
  prms->game->score += throw_line(prms->game);
  if (prms->game->score > prms->game->high_score) {
    prms->game->high_score = prms->game->score;
  }
  *(prms->state) = SPAWN;
}

void state_gameover(params_t *prms) {
  restart(prms->game);
  *(prms->state) = START;
}

void state_pause(params_t *prms) {
  if (*(prms->state) != PAUSE)
    *prms->state = PAUSE;
  else
    *prms->state = MOVING;
}
