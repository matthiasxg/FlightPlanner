/*
 * Name: Grill Matthias
 * Class: 5BHIF
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
#include "addroutedialog.h"

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
  void initGUI();
  ~MainWindow();

private slots:
  void on_pushButton_clicked();

  void on_actionAdd_route_triggered();

  void on_actionAbout_me_triggered();

private:
  Ui::MainWindow *ui;
  AddRouteDialog addRouteDialog;
  DbManager database = DbManager::getInstance();

  QFont font{"Helvetica", 16, QFont::Bold};

  void fillFlightTable(vector<vector<int>> routes);
  std::tuple<vector<tuple<int, int>>, vector<tuple<int, int>>, vector<tuple<int, int>>> splitRoutes(vector<vector<int>> routes, int airline);
};

#endif // MAINWINDOW_H
