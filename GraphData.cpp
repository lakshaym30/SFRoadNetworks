#include "GraphData.h"
#include <list>

GraphData::GraphData() {}

GraphData::GraphData(string data1, string data2) {
    cs225::HSLAPixel pixel;
    ifstream ifsNode(data1);
    string nodeID, xString, yString;

    if (ifsNode.is_open()) {
        while (ifsNode >> nodeID >> xString >> yString) {
            int id = stoi(nodeID);
            double x = stod(xString);
            double y = stod(yString);

            //inserting into adj list
            Node* n = new Node(id, x, y);
            adj_.push_back(n);
            numNodes_++;

            //node map implementation
            nodes_[id] = make_pair(x, y);
        }
    }

    
    ifstream ifsEdge(data2);
    string rubbish, id1, id2, distString;

    if (ifsEdge.is_open()) {
        while (ifsEdge >> rubbish >> id1 >> id2 >> distString) {
            int node1 = stoi(id1);
            int node2 = stoi(id2);
            double dist = stod(distString);

            //creating edges between nodes
            double x1 = nodes_[node1].first;
            double y1 = nodes_[node1].second;
            Node* curr = adj_[node1];
            while (curr->next != nullptr) curr = curr->next;
            curr->next = new Node(node1, x1, y1);

            double x2 = nodes_[node2].first;
            double y2 = nodes_[node2].second;
            curr = adj_[node2];
            while (curr->next != nullptr) curr = curr->next;
            curr->next = new Node(node2, x2, y2);

            //edge map implementation
            pair<double, double> p(node1, node2);
            edges_[p] = dist;
        }
    }

}

void GraphData::insert(Node* newNode) {
    newNode = nullptr;
}

void GraphData::BFS(int id) {
    vector<bool> visited;
    for (int i = 0; i < numNodes_; i++) visited.push_back(false);

    queue<int> queue;
    visited.at(id) = true;
    queue.push(id);

    while (!queue.empty()) {
        id = queue.front();
        queue.pop();

        Node* curr = adj_[id];
        while (curr != nullptr) {
            if (visited.at(curr->id) == false) {
                visited.at(curr->id) = true;
                queue.push(curr->id);
            }
        }
    }
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



// void GraphData::graph_visualizer() {

// }

// int GraphData::printPath(int parent[], int initial, int final) {
//     static int depth = 0;
//     if (parent[initial] == -1) {
//         cout << initial << " to " << final << endl;
//         return depth;
//     }

//     printPath(parent, parent[initial], final);
//     depth++;

//     if (initial < numNodes_) {
//         cout << initial << " ";
//     }
//     return depth;
//

int GraphData::shortestPath(int node1, int node2) {
    int capacity = 2 * numNodes_;
    bool *traversed = new bool[capacity];
    int *parent = new int[2 * capacity];

    for (int i = 0; i < 2 * capacity; i++){
        parent[i] = -1;
        traversed[i] = false;
    }
    queue<int> queue;

    traversed[node1] = true;
    queue.push(node1);



    while (queue.empty() == false) {
        int first = queue.front();
        if (first == node2) {
            return printPath(parent, first, node2);
        }
        queue.pop();

        Node* list = adj_[first];
        int count = 0;
    }


    return 0;
}
