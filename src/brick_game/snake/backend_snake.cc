#include "backend_snake.h"

/** @file */

namespace s21 {

SnakeGame::SnakeGame()
    : score(0),
      high_score(0),
      level(0),
      speed(0),
      snake_path(Up),
      action_view(START_VIEW),
      active_state(ADD_STATE) {
  srand(static_cast<unsigned int>(time(0)));
  load_file_score();
  field = std::vector<std::vector<int>>(20, std::vector<int>(10, 0));
  snake_body.push_back({16, 6});
  snake_body.push_back({17, 6});
  snake_body.push_back({18, 6});
  snake_body.push_back({19, 6});

  for (const auto& part_of_snake : snake_body) {
    field[part_of_snake.first][part_of_snake.second] = 1;
  }
  new_apple();
}

SnakeGame::~SnakeGame() {}

void SnakeGame::moveSnake() {
  while (!active_snake.empty()) {
    UserAction_t action = active_snake.front();
    active_snake.pop();
    switch (action) {
      case Left:
        if (snake_path != Right) snake_path = Left;
        break;
      case Right:
        if (snake_path != Left) snake_path = Right;
        break;
      case Up:
        if (snake_path != Down) snake_path = Up;
        break;
      case Down:
        if (snake_path != Up) snake_path = Down;
        break;
      default:
        break;
    }
  }

  int first_x = snake_body.front().second;
  int first_y = snake_body.front().first;
  int new_x = first_x;
  int new_y = first_y;

  if (snake_path == Up) new_y--;
  if (snake_path == Down) new_y++;
  if (snake_path == Left) new_x--;
  if (snake_path == Right) new_x++;

  if (colision(new_x, new_y)) {
    active_state = GAME_OVER;
    action_view = GAMEOVER_VIEW;
    return;
  }

  if (new_x == food.second && new_y == food.first) {
    snake_body.insert(snake_body.begin(), {new_y, new_x});
    field[new_y][new_x] = 1;
    score++;
    update_score();
    active_state = CREATE_APPLE;
  } else {
    snake_body.insert(snake_body.begin(), {new_y, new_x});
    field[new_y][new_x] = 1;
    auto last_segment = snake_body.back();
    snake_body.pop_back();
    field[last_segment.first][last_segment.second] = 0;
  }
}

int SnakeGame::colision(int new_x, int new_y) {
  for (const auto& part_of_snake : snake_body) {
    if (part_of_snake.first == new_y && part_of_snake.second == new_x) {
      return COLISION;
    }
  }
  if (new_y < 0 || new_y >= 20 || new_x < 0 || new_x >= 10) {
    return COLISION;
  } else {
    return NO_COLISION;
  }
}

void SnakeGame::new_apple() {
  int x, y;
  while (1) {
    x = rand() % 10;
    y = rand() % 20;
    if (field[y][x] == 0) break;
  }
  food = {y, x};
  field[y][x] = 2;
}

GameInfo_t SnakeGame::updateCurrentState() {
  return {field, score, high_score, level, speed, action_view};
}

void SnakeGame::userInput(UserAction_t action) {
  switch (action) {
    case Start:
      active_state = MOVE;
      action_view = MOVE_VIEW;

      break;
    case Pause:

      if (active_state == MOVE) {
        active_state = ADD_STATE;
        action_view = PAUSE_VIEW;
      } else if (active_state == ADD_STATE) {
        active_state = MOVE;
        action_view = MOVE_VIEW;
      }

      break;
    case Terminate:
      active_state = GAME_OVER;
      break;
    case Left:
    case Right:
    case Up:
    case Down:
      if (active_state == MOVE) {
        active_snake.push(action);
      }
      break;
    default:
      break;
  }
}

void SnakeGame::fsm() {
  switch (active_state) {
    case MOVE:
      action_view = MOVE_VIEW;
      moveSnake();
      break;
    case CREATE_APPLE:
      new_apple();
      active_state = MOVE;
      break;
    case GAME_OVER:
      action_view = GAMEOVER_VIEW;
      break;
    case ADD_STATE:
      break;
    default:
      break;
  }
}

void SnakeGame::update_score() {
  if (score / 5 > speed && speed <= 10) {
    level = speed = score / 5;
  }

  if (score > high_score) {
    high_score = score;
    save_file_score();
  }
}

void SnakeGame::load_file_score() {
  std::ifstream file("snake_score.txt");
  if (file.is_open()) {
    file >> high_score;
    file.close();
  } else {
    high_score = 0;
  }
}

void SnakeGame::save_file_score() {
  std::ofstream file("snake_score.txt");
  if (file.is_open()) {
    file << high_score;
    file.close();
  }
}

void SnakeGame::update_game() { fsm(); }

int SnakeGame::game_over() { return active_state == GAME_OVER; }

void SnakeGame::load_score() { load_file_score(); }

void SnakeGame::save_score() { save_file_score(); }

void SnakeGame::set_state(State new_state) { this->active_state = new_state; }

int SnakeGame::get_state() const { return active_state; }

int SnakeGame::get_score() { return score; }

void SnakeGame::set_score(int new_score) { score = new_score; }

void SnakeGame::up_score() { update_score(); }

void SnakeGame::set_high_score(int new_high_score) {
  high_score = new_high_score;
}

int SnakeGame::getSpeed() const { return speed; }

int SnakeGame::is_moveSnake() const { return snake_path; }

void SnakeGame::is_moveSnake2() { moveSnake(); }

}  // namespace s21
