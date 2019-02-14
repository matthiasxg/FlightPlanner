#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    initComboBoxen();

    database.fillGraph(gr);

    /* How to insert in table
    vector<vector<QTableWidgetItem*>> z;
    vector<QTableWidgetItem*> v;

    for (int i{0}; i < 100; i++){
        v.clear();
        for (int j = 0; j < 4; j++) {
            v.push_back(new QTableWidgetItem(tr("%1").arg(i+j)));
        }
        z.push_back(v);
    }

    fillTable(z);
    */
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

void MainWindow::fillTable(std::vector<vector<QTableWidgetItem*>> table){
    ui->flightTable->setRowCount(table.size());
    for (int i{0}; i < table.size(); i++) {
        for (int j{0}; j < table.at(i).size(); j++) {
            ui->flightTable->setItem(i, j, table.at(i).at(j));
        }
    }

    ui->flightTable->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    QString departure = ui->comboDeparture->currentText();
    QString destination = ui->comboDestination->currentText();
    QString airline = ui->comboAirline->currentText();

    int airport1 = database.getAirportId(departure);
    int airport2 = database.getAirportId(destination);

    if (airport1 != airport2 && database.hasARoute(airport1) && database.hasARoute(airport2)) {
        auto result = gr.calculate(airport1, airport2);
    } else {
        qDebug() << "not found";
    }

}

