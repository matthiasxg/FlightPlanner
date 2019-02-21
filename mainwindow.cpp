/*
 * Author: Matthias Grill
 * Class: 5BHIF
 * Date: 18.02.2019
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <future>
#include <QCompleter>
#include <chrono>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();
}

void MainWindow::init()
{
    //Fonts
    QFont font("Helvetica", 14, QFont::Bold);
    ui->toLabel->setFont(font);
    ui->fromLabel->setFont(font);
    ui->airlineLabel->setFont(font);
    ui->pushButton->setFont(font);

    //Status Bar
    ui->statusBar->showMessage("Matthias Grill x 5BHIF");

    // Fill airport forms
    QStringList airportList;
    for (auto &airport : database.airports)
    {
        airportList << airport.name + " (" + airport.iata + ")";
    }
    QCompleter *aiportCompleter = new QCompleter(airportList, this);
    aiportCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->FromSearch->setCompleter(aiportCompleter);
    ui->ToSearch->setCompleter(aiportCompleter);

    // Fill airline forms
    QStringList airlineList;
    for (auto &airline : database.airlines)
    {
        airlineList << airline.name;
    }
    QCompleter *airlineCompleter = new QCompleter(airlineList, this);
    airlineCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    ui->AirlineSearch->setCompleter(airlineCompleter);
}

vector<vector<int>> MainWindow::getRoutes(vector<int> prev, int depth, int start, int end)
{
    vector<vector<int>> ret;

    if (depth == 0)
    {
        if (database.isConnected(start, end))
        {
            vector<int> newPrev = prev;
            newPrev.push_back(end);
            ret.push_back(newPrev);
        }
    }
    else
    {
        auto nbs = database.getNeighbours(start);
        vector<future<vector<vector<int>>>> futs;

        for (auto &airport : nbs)
        {
            if (std::find(prev.begin(), prev.end(), airport) != prev.end())
            {
                continue;
            }

            vector<int> newPrev = prev;
            newPrev.push_back(airport);

            if (depth == 4)
            {
                futs.push_back(std::async(launch::async, &MainWindow::getRoutes, this, newPrev, depth - 1, airport, end));
            }
            else
            {
                auto toConcat = getRoutes(newPrev, depth - 1, airport, end);
                if (toConcat.size() != 0)
                {
                    ret.insert(ret.end(), toConcat.begin(), toConcat.end());
                }
            }
        }

        for (auto &fut : futs)
        {
            auto toConcat = fut.get();
            ret.insert(ret.end(), toConcat.begin(), toConcat.end());
        }
    }
    return ret;
}

void MainWindow::on_pushButton_clicked()
{
    ui->flighttable->clear();
    ui->map->resetPic();

    QString departure = ui->FromSearch->text();
    QString destination = ui->ToSearch->text();
    QString airline = ui->AirlineSearch->text();

    departure = departure.left(departure.indexOf("(") - 1);
    destination = destination.left(destination.indexOf("(") - 1);

    int airport1 = database.getAirportId(departure);
    int airport2 = database.getAirportId(destination);
    int airlineId = database.getAirlineId(airline);

    //airport1 = 4908; // Vienna
    //airport2 = 3699; // Palm Spings

    int depth{0};
    vector<vector<int>> routes;
    do
    {
        routes = getRoutes({airport1}, depth, airport1, airport2);
        qDebug() << "Depth: " << depth;
        depth += 1;
    } while (routes.size() == 0 && depth <= 4);

    // Fill flight table
    vector<QString> flights;
    for (auto &vec : routes)
    {
        QString flight;
        for (int i{0}; i <= vec.size() - 1; i++)
        {
            if (i != 0)
            {
                flight += " -> ";
            }
            QString airportName = database.getAirportName(vec[i]);
            flight += airportName;
        }
        flights.push_back(flight);
    }
    sort(flights.begin(), flights.end());

    for (auto &flight : flights)
    {
        ui->flighttable->addItem(new QListWidgetItem(flight));
    }

    // Split all routes to the different colours
    auto newRoutes = splitRoutes(routes, airlineId);
    if (airlineId == -1)
    {
        ui->map->connectTheDots(get<2>(newRoutes), QColor{82, 82, 255});
    }
    else
    {
        ui->map->connectTheDots(get<0>(newRoutes), QColor{255, 82, 82});
        ui->map->connectTheDots(get<1>(newRoutes), QColor{82, 82, 255});
        ui->map->connectTheDots(get<2>(newRoutes), QColor{82, 82, 82});
    }
}

std::tuple<vector<tuple<int, int>>, vector<tuple<int, int>>, vector<tuple<int, int>>> MainWindow::splitRoutes(vector<vector<int>> routes, int airline)
{
    vector<tuple<int, int>> airlineRoutes;
    vector<tuple<int, int>> allianceRoutes;
    vector<tuple<int, int>> otherRoutes;

    int alliance = database.airlines[airline].alliance;

    for (auto &route : routes)
    {
        for (int i{0}; i <= route.size() - 2; i++)
        {
            if (database.isConnected(route[i], route[i + 1], airline))
            {
                airlineRoutes.push_back(make_tuple(route[i], route[i + 1]));
            }
            else if (database.isConnectedViaAlliance(route[i], route[i + 1], alliance))
            {
                allianceRoutes.push_back(make_tuple(route[i], route[i + 1]));
            }
            else
            {
                otherRoutes.push_back(make_tuple(route[i], route[i + 1]));
            }
        }
    }

    return std::make_tuple(airlineRoutes, allianceRoutes, otherRoutes);
}

void MainWindow::on_actionAbout_me_triggered()
{
    QMessageBox msg;
    msg.setText("<center>Name: Matthias Grill<br>"
                "Class: 5BHIF<br>"
                "Made with love & coffee hihi</center>");
    msg.exec();
}


MainWindow::~MainWindow()
{
    delete ui;
}
