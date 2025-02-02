#ifndef BACKEND_SNAKE_H
#define BACKEND_SNAKE_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <queue>
#include <utility>
#include <vector>

namespace s21 {

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

typedef enum {
  START,
  MOVE,
  CREATE_APPLE,
  GAME_OVER,
  GAME_PAUSED,
  ADD_STATE
} State;

typedef struct {
  std::vector<std::vector<int>> field;
  int score;
  int high_score;
  int level;
  int speed;

  int action_view;
} GameInfo_t;

typedef enum { MOVE_VIEW, START_VIEW, PAUSE_VIEW, GAMEOVER_VIEW } view_state;

typedef enum { NO_COLISION, COLISION } check_t;

class SnakeGame {
 private:
  std::vector<std::vector<int>> field;
  std::vector<std::pair<int, int>> snake_body;
  std::pair<int, int> food;
  int score;
  int high_score;
  int level;
  int speed;
  int snake_path;
  int action_view;

  State active_state;
  std::queue<UserAction_t> active_snake;

  void moveSnake();

  int colision(int new_x, int new_y);
  void new_apple();
  void fsm();
  void update_score();
  void save_file_score();
  void load_file_score();

 public:
  SnakeGame();
  ~SnakeGame();

  GameInfo_t updateCurrentState();
  void userInput(UserAction_t action);
  int game_over();
  void update_game();
  void load_score();
  void save_score();

  // для покрытия тестов
  int is_moveSnake() const;
  void is_moveSnake2();
  int get_score();
  int getSpeed() const;
  void set_state(State new_state);
  int get_state() const;
  void set_score(int new_score);
  void set_high_score(int new_high_score);
  void up_score();
};

}  // namespace s21

#endif  // BACKEND_SNAKE_H
