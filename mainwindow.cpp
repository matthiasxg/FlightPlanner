#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initComboBoxen();
}

void MainWindow::initComboBoxen() {
    allAirlineNames = database.getAllAirlineNames();
    allAirportNames = database.getAllAirportNames();

    // Set departure and destination airport comboboxen
    for (auto &airport : allAirportNames) {
        ui->comboDeparture->addItem(airport);
        ui->comboDestination->addItem(airport);
    }

    // Airlines
    for (auto &airline : allAirlineNames) {
        ui->comboAirline->addItem(airline);
    }

    // Set font
    ui->labelAirline->setFont(titleFont);
    ui->labelDeparture->setFont(titleFont);
    ui->labelDestination->setFont(titleFont);

    ui->comboAirline->setFont(standardFont);
    ui->comboDeparture->setFont(standardFont);
    ui->comboDestination->setFont(standardFont);
    ui->searchButton->setFont(standardFont);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    // Button clicked
}
