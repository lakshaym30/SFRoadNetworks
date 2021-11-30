#include "GraphData.h"

GraphData::GraphData() {}

GraphData::GraphData(string data1, string data2) {
    ifstream ifsNode(data1);
    string nodeID, xString, yString;

    if (ifsNode.is_open()) {
        //while (getLine(nodeData, txt)) { cout << txt << endl; }
        while (ifsNode >> nodeID >> xString >> yString) {
            int id = stoi(nodeID);
            double x = stod(xString);
            double y = stod(yString);
            nodes_[id] = make_pair(x, y);
            //if (id == 42) cout << xString << endl;
        }
    }

    //cout << nodes_[42].first << endl;
    
    ifstream ifsEdge(data2);
    string rubbish, id1, id2, distString;

    if (ifsEdge.is_open()) {
        while (ifsEdge >> rubbish >> id1 >> id2 >> distString) {
            int node1 = stoi(id1);
            int node2 = stoi(id2);
            double dist = stod(distString);
            pair<double, double> p(node1, node2);
            edges_[p] = dist;
        }
    }
    // pair<double, double> i(472, 473);
    // cout << edges_[i] << endl;
}

double GraphData::findDist(int node1, int node2) {
    pair<double, double> primary(node1, node2);
    pair<double, double> alternate(node2, node1);
    double primary_dist_ = edges_[primary];
    double alternate_dist_ = edges_[alternate];
    if (primary_dist_ != 0) {
        return primary_dist_;
    } else if (alternate_dist_ != 0) {
        return alternate_dist_;
    }
    return 0;
}