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
            double y = stod(yString); //check accuracy (printf?)

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

            double x2 = nodes_[node2].first;
            double y2 = nodes_[node2].second;

            Node* curr = adj_[node1];
            while (curr->next != nullptr) curr = curr->next;
            curr->next = new Node(node2, x2, y2);

            
            curr = adj_[node2];
            while (curr->next != nullptr) curr = curr->next;
            curr->next = new Node(node1, x1, y1);

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

cs225::PNG GraphData::graphVisualizer() {
    cs225::PNG * vis = new cs225::PNG(12000, 12000);

    cs225::HSLAPixel & curPixel = vis->getPixel(0, 0);
    curPixel = GREEN;

    for (Node * val : adj_) {
        //creating 3 by 3 for each node for visualization
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                cs225::HSLAPixel & curPixel = vis->getPixel(val->x + i, 12000 - val->y + j);
                if (j % 2 == 0) curPixel = BLUE;
                else curPixel = RED;
            }
        }
    }

    for (Node * val: adj_) {
        Node * next_ = val->next;
        while (next_ != nullptr) {
            int x1 = val->x;
            int y1 = 12000 - val->y;
            int x2 = next_->x;
            int y2 = 12000 - next_->y;

            int dx = x2 - x1;
            int dy = y2 - y1;

            // int step = abs(dy) > abs(dx);
            // if (step) {
            //     swap(x1, x2);
            //     swap(y1, y2);
            // } 

            // if (x1 > x2) {
            //     swap(x1, x2);
            //     swap(y1, y2);
            //     //cout << "invalid index" << endl;
            //     //next_ = next_->next;
            //     //continue;
            // }           

            int x = x1;
            int y = y1;
            int step = 2 * dy - dx;
            
            // int x_1 = x1;
            // int x_2 = x2;
            // int y_sect = y1;
            // int gradient = (int) (dy / dx);
            // if (dx == 0) gradient = 1;

            // if (step) {
            //     for (int x = x_1; x <= x_2; x++) {
            //         cs225::HSLAPixel & curPixel = vis->getPixel(y_sect, x);
            //         curPixel = BLACK;
            //         cs225::HSLAPixel & curPixel2 = vis->getPixel(y_sect - 1, x);
            //         curPixel2 = BLACK;
            //         y_sect += gradient;
            //     }
            // } else {
            //     for (int x = x_1; x <= x_2; x++) {
            //         cs225::HSLAPixel & curPixel = vis->getPixel(x, y_sect);
            //         curPixel = BLACK;
            //         cs225::HSLAPixel & curPixel2 = vis->getPixel(x, y_sect - 1);
            //         curPixel2 = BLACK;
            //         y_sect += gradient;
            //     }
            // }

            while (x < x2) {
                cs225::HSLAPixel & curPixel = vis->getPixel(x, y);
                curPixel = BLACK;

                if (step >= 0) {
                    y++;
                    step += (2 * dy) - (2 * dx);
                } else {
                    step += 2 * dy;
                }
                x++;
            }

            next_ = next_->next;
        }
        
    }
    
    return *vis;

}

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

/*
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
*/