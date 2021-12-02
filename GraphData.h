#pragma once

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Node {
    Node(int newId, double xcoord, double ycoord): id(newId), x(xcoord), y(ycoord), next(nullptr) {}
    int id;
    double x, y;
    Node* next; 
};

class GraphData {
    public:
    GraphData();
    GraphData(std::string data1, std::string data2);
    void insert(Node* newNode);
    double findDist(int node1, int node2);
    

    private:
    vector<Node*> adj_;

    map<int, pair<double, double> > nodes_;
    map<pair<int, int>, double> edges_;
};