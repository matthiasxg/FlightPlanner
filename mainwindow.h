/*
 * Author: Matthias Grill
 * Class: 5BHIF
 * Date: 18.02.2019
 */


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFont>
#include "dbmanager.h"
#include <QMessageBox>
#include <vector>
#include <QTableWidgetItem>
#include <memory>

using namespace std;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  void init();
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_actionAbout_me_triggered();

private:
  Ui::MainWindow *ui;
  DbManager database = DbManager::getInstance();

  vector<vector<int>> getRoutes(vector<int> prev, int depth, int start, int end);
  vector<vector<int>> removeWrongAirlines(vector<vector<int>> routes, int airline);
  std::tuple<vector<tuple<int, int>>, vector<tuple<int, int>>, vector<tuple<int, int>>> splitRoutes(vector<vector<int>> routes, int airline);
};

#endif // MAINWINDOW_H
