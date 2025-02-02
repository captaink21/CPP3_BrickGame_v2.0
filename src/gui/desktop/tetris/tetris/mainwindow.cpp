#include "mainwindow.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  m_tetrisWidget = new TetrisWidget(this);
  setCentralWidget(m_tetrisWidget);
}

MainWindow::~MainWindow() {}
