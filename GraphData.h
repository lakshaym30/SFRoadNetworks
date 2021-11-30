#pragma once

#include <map>
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;
class GraphData {
    public:
    GraphData();
    GraphData(std::string data1, std::string data2);
    double findDist(int node1, int node2);

    private:
    map<int, pair<double, double> > nodes_;
    map<pair<int, int>, double> edges_;
};