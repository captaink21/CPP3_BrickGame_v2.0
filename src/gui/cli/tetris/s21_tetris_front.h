#ifndef S21_TETRIS_FRONT_H
#define S21_TETRIS_FRONT_H
#include <locale.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <wchar.h>

#include "../../../brick_game/tetris/s21_tetris_back.h"

#define POLE_WIDTH 12
#define POLE_HEIGHT 22
#define FIGURE_SIZE 5

void button_pause();
void button_start();
void print_game(GameInfo_t* game, Figure* action_figure);
void print_info(GameInfo_t* game);

void print_corner(int left_x, int right_x, int up_y, int down_y);

#endif