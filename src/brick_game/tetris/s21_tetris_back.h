#ifndef S21_TETRIS_BACK_H
#define S21_TETRIS_BACK_H

#ifdef __cplusplus
extern "C" {
#endif

#include <locale.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#define POLE_WIDTH 12
#define POLE_HEIGHT 22
#define FIGURE_SIZE 5

typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int** field;
  int** next;
  int score;
  int high_score;
  int level;
  int speed;
  int pause;
} GameInfo_t;

typedef enum {
  START,
  SPAWN,
  MOVING,
  SHIFTING,
  ATTACHING,
  GAMEOVER,
  PAUSE
} State;

typedef struct Figure {
  int x;
  int y;
  int** figure;
} Figure;

typedef struct Time {
  int tick;
  int step_time;
} Time;

int random_figure(int min, int max);
void new_next_figure(GameInfo_t* game);
void allocation_next_figure(GameInfo_t* game);
void free_next_figure(GameInfo_t* game);
void create_field(GameInfo_t* game);
void free_field(GameInfo_t* game);
GameInfo_t* new_game();
void free_game(GameInfo_t* game);
void move_down(Figure* action_figure);
void move_up(Figure* action_figure);
void move_left(Figure* action_figure);
void move_right(Figure* action_figure);
int colision(Figure* action_figure, GameInfo_t* game);
void field_figure(Figure* action_figure, GameInfo_t* game);
int line_full(int i, GameInfo_t* game);
void down_line(int i, GameInfo_t* game);
int throw_line(GameInfo_t* game);
Figure* create_figure();
void free_figure(Figure* figure);
void figure_on_field(Figure* action_figure, GameInfo_t* game);
Figure* transpose_figure(Figure* action_figure);
void user_input(UserAction_t action, Figure* action_figure, GameInfo_t* game,
                State* state);
void table_level(GameInfo_t* game);

void score(GameInfo_t* game);
void level_monitoring(GameInfo_t* game);
void sigact(GameInfo_t* game, Figure* action_figure, UserAction_t action,
            State* state);

void copy_matrix(int (*src)[5], int** dst, int rows, int cols);

void delete_score();
void restart(GameInfo_t* game);

typedef struct game_params {
  GameInfo_t* game;
  Figure* action_figure;

  UserAction_t action;
  State* state;
} params_t;

void state_start(params_t* prms);
void state_spawn(params_t* prms);
void state_moving(params_t* prms);
void state_shifting(params_t* prms);
void state_attaching(params_t* prms);
void state_gameover(params_t* prms);
void state_pause(params_t* prms);

const char* checsomething();

#ifdef __cplusplus
}
#endif

#endif
