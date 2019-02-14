#pragma once

#include <vector>
#include <utility>
#include <map>
#include <list>
#include <QString>
#include <QMessageBox>
#include <vector>
#include <QTableWidgetItem>
#include <memory>

using namespace std;

class Graph {
public:
    Graph();
    map<int, vector<int>*> *kanten;
    void addKante(int v1, int v2);
    vector<int>* calculate(int start, int ziel);
};
