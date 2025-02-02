#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "snakewidget.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private:
  SnakeWidget *m_snakeWidget;
};
#endif  // MAINWINDOW_H
