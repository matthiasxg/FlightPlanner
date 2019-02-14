#include "graph.h"
#include <utility>
#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <QMessageBox>

using namespace std;
Graph::Graph()
{
    kanten = new map<int, vector<int>*>();
}

void Graph::addKante(int v1, int v2)
{
    if(kanten->count(v1) == 0){
        kanten->insert(make_pair(v1, new vector<int>()));
    }
    if(kanten->count(v2) == 0){
        kanten->insert(make_pair(v2, new vector<int>()));
    }
    kanten->at(v1)->push_back(v2);
    kanten->at(v2)->push_back(v1);

}


vector<int>* Graph::calculate(int start, int ziel)
{
    map<int, int> distances;
    map<int, int> prev;
    prev[start] = -1;
    for(auto it = kanten->begin(); it != kanten->end(); ++it){
        distances[it->first] = 1000;
    }
    distances[start] = 0;
    queue<pair<int,int>> pq;
    pq.push(make_pair(start, 0));
    while(!pq.empty()){
        auto minNode = pq.front();
        pq.pop();
        cout << kanten->at(77) << endl;
        auto neighbours = kanten->at(minNode.first);
        cout << "5" << endl;
        for(auto &neighbour : *neighbours){
            int newWeight = distances[minNode.first] + 1;
            if(newWeight < distances[neighbour]){
                distances[neighbour] = newWeight;
                pq.push(make_pair(neighbour, newWeight));
                prev[neighbour] = minNode.first;
            }
        }
    }
    vector<int>* result = new vector<int>();
    int tmp = ziel;
    while(prev[tmp] != -1){
        result->push_back(tmp);
        tmp = prev[tmp];
    }
    return result;
}
