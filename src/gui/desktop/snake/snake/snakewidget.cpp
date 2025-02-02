#include "snakewidget.h"

#include <QKeyEvent>
#include <QPainter>

SnakeWidget::SnakeWidget(QWidget *parent)
    : QWidget(parent), m_game(new s21::SnakeGame), m_timer(new QTimer(this)) {
  setFixedSize(350, 400);
  setGameSpeed(0);
  connect(m_timer, &QTimer::timeout, this, &SnakeWidget::updateGame);
  setFocusPolicy(Qt::StrongFocus);

  m_timer->start();
}

SnakeWidget::~SnakeWidget() {
  delete m_game;
  delete m_timer;
}

void SnakeWidget::setGameSpeed(int speed) {
  int interval = 0;
  if (speed < 1) {
    interval = 200;
  } else if (speed > 10) {
    interval = 20;
  } else
    interval = 200 / speed;

  m_timer->setInterval(interval);
}

void SnakeWidget::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event);

  QPainter painter(this);
  const auto gameInfo = m_game->updateCurrentState();

  for (int y = 0; y < static_cast<int>(gameInfo.field.size()); ++y) {
    for (int x = 0; x < static_cast<int>(gameInfo.field[y].size()); ++x) {
      if (gameInfo.field[y][x] == 1) {
        painter.setBrush(Qt::black);
      } else if (gameInfo.field[y][x] == 2) {
        painter.setBrush(Qt::red);
      } else {
        painter.setBrush(Qt::white);
      }
      painter.drawRect(x * 20, y * 20, 20, 20);
    }
  }

  painter.setPen(Qt::black);
  painter.setFont(QFont("Arial", 13));
  int textX = 220;
  int textY = 20;
  int lineHeight = 30;

  painter.drawText(textX, textY, "Score: " + QString::number(gameInfo.score));
  painter.drawText(textX, textY + lineHeight,
                   "High Score: " + QString::number(gameInfo.high_score));
  painter.drawText(textX, textY + 2 * lineHeight,
                   "Level: " + QString::number(gameInfo.level));
  painter.drawText(textX, textY + 3 * lineHeight,
                   "Speed: " + QString::number(gameInfo.speed));

  int commandsY = textY + 5 * lineHeight;
  painter.drawText(textX, commandsY, "Commands:");
  painter.drawText(textX, commandsY + lineHeight, "Left: ←");
  painter.drawText(textX, commandsY + 2 * lineHeight, "Right: →");
  painter.drawText(textX, commandsY + 3 * lineHeight, "Up: ↑");
  painter.drawText(textX, commandsY + 4 * lineHeight, "Down: ↓");
  painter.drawText(textX, commandsY + 5 * lineHeight, "Pause: Space");
  painter.drawText(textX, commandsY + 6 * lineHeight, "Start: Enter");
  painter.drawText(textX, commandsY + 7 * lineHeight, "Quit: Q");

  if (gameInfo.action_view == s21::START_VIEW) {
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 20, QFont::Bold));
    painter.drawText(10, 200, "Press Enter to Start");
  }

  if (gameInfo.action_view == s21::PAUSE_VIEW) {
    painter.setPen(Qt::red);
    painter.setFont(QFont("Arial", 20, QFont::Black));
    painter.drawText(20, 200, "Paused. Press");
    painter.drawText(20, 250, "Space to Resume");
  }

  if (gameInfo.action_view == s21::GAMEOVER_VIEW) {
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 30, QFont::Bold));
    painter.drawText(20, 200, "Game Over");
    painter.drawText(20, 230, "Score: " + QString::number(gameInfo.score));
  }
}

void SnakeWidget::keyPressEvent(QKeyEvent *event) {
  switch (event->key()) {
    case Qt::Key_Left:
      m_game->userInput(s21::Left);
      break;
    case Qt::Key_Right:
      m_game->userInput(s21::Right);
      break;
    case Qt::Key_Up:
      m_game->userInput(s21::Up);
      break;
    case Qt::Key_Down:
      m_game->userInput(s21::Down);
      break;
    case Qt::Key_Space:
      m_game->userInput(s21::Pause);
      break;
    case Qt::Key_Return:
    case Qt::Key_Enter:
      m_game->userInput(s21::Start);
      break;
    case Qt::Key_Q:
      m_game->userInput(s21::Terminate);
      break;
    default:
      QWidget::keyPressEvent(event);
  }
}

void SnakeWidget::updateGame() {
  m_game->update_game();
  if (m_game->game_over()) {
    m_timer->stop();
  } else {
    setGameSpeed(m_game->getSpeed());
  }
  update();
}
