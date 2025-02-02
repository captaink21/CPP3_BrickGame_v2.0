#include "tetriswidget.h"

#include <QDebug>
#include <QKeyEvent>
#include <QPainter>

TetrisWidget::TetrisWidget(QWidget *parent)
    : QWidget(parent), m_timer(new QTimer(this)) {
  setFixedSize(360, 440);

  player = Start;

  state = START;

  create_tetris = new_game();
  if (!create_tetris) {
    return;
  }

  action_figure = create_figure();

  setGameSpeed(create_tetris->speed);
  connect(m_timer, &QTimer::timeout, this, &TetrisWidget::updateGame);
  setFocusPolicy(Qt::StrongFocus);

  m_timer->start();
}

void TetrisWidget::setGameSpeed(int speed) {
  int interval = 0;
  if (speed < 1) {
    interval = 200;
  } else if (speed > 10) {
    interval = 20;
  } else {
    interval = 200 / speed;
  }
  m_timer->setInterval(interval);
}

TetrisWidget::~TetrisWidget() {
  delete m_timer;
  free_figure(action_figure);
  free_game(create_tetris);
}

void TetrisWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  const auto *gameInfo = create_tetris;

  for (int y = 0; y < POLE_HEIGHT; ++y) {
    for (int x = 0; x < POLE_WIDTH; ++x) {
      if (gameInfo->field[y][x] != 0) {
        painter.setBrush(Qt::black);
      } else {
        painter.setBrush(Qt::white);
      }
      painter.drawRect(x * 20, y * 20, 20, 20);
    }
  }

  for (int x = 0; x < POLE_WIDTH; ++x) {
    painter.setBrush(Qt::black);
    painter.drawRect(x * 20, 0, 20, 20);
    painter.drawRect(x * 20, (POLE_HEIGHT - 1) * 20, 20, 20);
  }
  for (int y = 0; y < POLE_HEIGHT; ++y) {
    painter.setBrush(Qt::black);
    painter.drawRect(0, y * 20, 20, 20);
    painter.drawRect((POLE_WIDTH - 1) * 20, y * 20, 20, 20);
  }

  for (int i = 0; i < FIGURE_SIZE; ++i) {
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      if (action_figure->figure[i][j] != 0) {
        painter.setBrush(Qt::red);
        painter.drawRect((action_figure->x + j) * 20,
                         (action_figure->y + i) * 20, 20, 20);
      }
    }
  }

  int previewX = 240;
  int previewY = 150;
  int blockSize = 20;

  painter.setBrush(Qt::blue);
  for (int i = 0; i < FIGURE_SIZE; ++i) {
    for (int j = 0; j < FIGURE_SIZE; ++j) {
      if (create_tetris->next[i][j] != 0) {
        painter.drawRect(previewX + j * blockSize, previewY + i * blockSize,
                         blockSize, blockSize);
      }
    }
  }

  painter.setPen(Qt::black);
  painter.setFont(QFont("Arial", 13));
  int textX = 250;
  int textY = 20;
  int lineHeight = 30;

  painter.drawText(textX, textY,
                   "Score: " + QString::number(create_tetris->score));
  painter.drawText(textX, textY + lineHeight,
                   "High Score: " + QString::number(create_tetris->high_score));
  painter.drawText(textX, textY + 2 * lineHeight,
                   "Level: " + QString::number(create_tetris->level));
  painter.drawText(textX, textY + 3 * lineHeight,
                   "Speed: " + QString::number(create_tetris->speed));

  int commandsY = textY + 5 * lineHeight;

  painter.drawText(textX, commandsY + 5 * lineHeight, "Action: UP");
  painter.drawText(textX, commandsY + 6 * lineHeight, "Pause:  Space");
  painter.drawText(textX, commandsY + 7 * lineHeight, "Quit:   Q");

  if (state == START) {
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.drawText(10, 200, "Press Enter to Start");
  }

  if (state == PAUSE) {
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 20, QFont::Black));
    painter.drawText(20, 200, "Paused. Press");
    painter.drawText(20, 250, "Space to Resume");
  }

  if (state == GAMEOVER) {
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    painter.drawText(20, 200, "Game Over");
    painter.drawText(20, 230,
                     "Score: " + QString::number(create_tetris->score));
  }
}

void TetrisWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Space:
      player = Pause;
      break;
    case Qt::Key_Up:
      player = Action;
      break;
    case Qt::Key_Down:
      player = Down;
      break;
    case Qt::Key_Left:
      player = Left;
      break;
    case Qt::Key_Right:
      player = Right;
      break;
    case Qt::Key_Q:
      player = Terminate;
      break;
    default:
      player = Up;
      break;
  }
}

void TetrisWidget::updateGame() {
  sigact(create_tetris, action_figure, player, &state);

  player = Up;

  if (state == GAMEOVER) {
    m_timer->stop();
  } else {
    setGameSpeed(create_tetris->speed);
  }

  update();
}
