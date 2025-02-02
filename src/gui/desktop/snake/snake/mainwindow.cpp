#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  m_snakeWidget = new SnakeWidget(this);
  setCentralWidget(m_snakeWidget);
}

MainWindow::~MainWindow() {}
