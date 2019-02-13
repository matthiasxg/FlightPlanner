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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void initComboBoxen();
    void fillTable(std::vector<vector<QTableWidgetItem*>>);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();

private:
    Ui::MainWindow *ui;
    DbManager database{"../static/AirlineRoutes.db"}; // Path to database file
    std::vector<QString> allAirlineNames;
    std::vector<QString> allAirportNames;

    QFont titleFont{"Helvetica", 18, QFont::Bold};
    QFont standardFont{"Helvetica", 18};
};

#endif // MAINWINDOW_H
