#ifndef SNAKEWIDGET_H
#define SNAKEWIDGET_H

#include <QTimer>
#include <QWidget>

#include "../../../../brick_game/snake/backend_snake.h"

class SnakeWidget : public QWidget {
  Q_OBJECT

 public:
  SnakeWidget(QWidget *parent = nullptr);
  ~SnakeWidget();
  void setGameSpeed(int speed);

 protected:
  void paintEvent(QPaintEvent *event) override;
  void keyPressEvent(QKeyEvent *event) override;

 private slots:
  void updateGame();

 private:
  s21::SnakeGame *m_game;
  QTimer *m_timer;
};

#endif  // SNAKEWIDGET_H
