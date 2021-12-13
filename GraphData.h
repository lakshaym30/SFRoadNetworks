#pragma once

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <queue>
#include <math.h>
#include <cmath>
#include <list>
#include <float.h>
#include <stdexcept>

#include "cs225/HSLAPixel.h"
#include "cs225/PNG.h"

using namespace std;
using namespace cs225;

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
    vector<bool> BFS(int id);
    PNG graphVisualizer();
    pair<vector<int>, vector<int>> shortestPath(int start_id);
    bool checkVisited(Node* check, vector<Node*> visited);


    private:
    long numNodes_;
    map<int, pair<double, double> > nodes_;
    map<pair<int, int>, double> edges_;
    vector<Node*> adj_;

    HSLAPixel RED = HSLAPixel(0, 1, 0.5);
    HSLAPixel BLACK = HSLAPixel(0, 1, 0);
    HSLAPixel BLUE = HSLAPixel(240, 1, 0.5);
    HSLAPixel GREEN = HSLAPixel(120, 1, 0.5);
    HSLAPixel ORANGE = HSLAPixel(39, 1, 0.5);
};
