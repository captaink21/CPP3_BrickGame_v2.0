#ifndef TETRIS_WINDOW_H
#define TETRIS_WINDOW_H

#include <QTimer>
#include <QWidget>

#include "../../../../brick_game/tetris/s21_tetris_back.h"

class TetrisWidget : public QWidget {
  Q_OBJECT

 public:
  TetrisWidget(QWidget *parent = nullptr);
  void setGameSpeed(int speed);
  ~TetrisWidget();

  State state;
  UserAction_t player;

 protected:
  void keyPressEvent(QKeyEvent *event) override;
  void paintEvent(QPaintEvent *event) override;

 private slots:
  void updateGame();

 private:
  GameInfo_t *create_tetris;

  Figure *action_figure;
  Time time;
  QTimer *m_timer;
};

#endif  // TETRIS_WINDOW_H
