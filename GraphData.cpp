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
    cs225::PNG * vis = new cs225::PNG(12000, 10000);
    for (Node * val: adj_) {
        cs225::HSLAPixel pixel = cs225::HSLAPixel(0,1,0.5);
        cs225::HSLAPixel pixel2 = cs225::HSLAPixel(1,0,0);

        //creating 2 by 2 for each node for visualization
        cs225::HSLAPixel & curPixel = vis->getPixel(val->x -1, val->y - 1);
        curPixel = pixel;
        cs225::HSLAPixel & curPixel2 = vis->getPixel(val->x, val->y - 1);  
        curPixel2 = pixel2;
        cs225::HSLAPixel & curPixel3 = vis->getPixel(val->x - 1, val->y);  
        curPixel3 = pixel;
        cs225::HSLAPixel & curPixel4 = vis->getPixel(val->x, val->y);  
        curPixel4 = pixel2;
        cs225::HSLAPixel & curPixel5 = vis->getPixel(val->x + 1, val->y);  
        curPixel5 = pixel2;
        cs225::HSLAPixel & curPixel6 = vis->getPixel(val->x, val->y + 1);  
        curPixel6 = pixel2;
        cs225::HSLAPixel & curPixel7 = vis->getPixel(val->x + 1, val->y + 1);  
        curPixel7 = pixel;
        cs225::HSLAPixel & curPixel8 = vis->getPixel(val->x + 1, val->y - 1);  
        curPixel8 = pixel2;
        cs225::HSLAPixel & curPixel9 = vis->getPixel(val->x - 1, val->y + 1);  
        curPixel9 = pixel;
    }

    //drawLines(vis);
    for (Node * val: adj_) {
        Node * next_ = val->next;
        while (next_ != nullptr) {
           
            int x1 = val->x;
            int y1 = val->y;
            int x2 = next_->x;
            int y2 = next_->y;
            
            int dx = x2 - x1;
            int dy = y2 - y1;
            int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    
            float Xinc = dx / (float) steps;
            float Yinc = dy / (float) steps;

            float x = x1;
            float y = x2;

            for(int i = 0; i <= steps; i++) {
                cs225::HSLAPixel pixel2 = cs225::HSLAPixel(180,1,0.5);
                cs225::HSLAPixel & curPixel = vis->getPixel(round(x), round(y));
                curPixel = pixel2;

                x += Xinc;
                y += Yinc;
            
            }
            next_ = next_->next;
        }
        
    }

    return *vis;

}


void GraphData::drawLines(cs225::PNG * vis) {
    //map<int, int> visited;
    for (Node * val: adj_) {
        Node * next_ = val->next;
        std::cout<<"works"<<endl;
        int x1 = val->x;
        int y1 = val->y;
        int x2 = next_->x;
        int y2 = next_->y;


        int dx = x2 - x1;
        int dy = y2 - y1;
        int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
 
        float Xinc = dx / (float) steps;
        float Yinc = dy / (float) steps;

        float x = x1;
        float y = x2;

        for(int i = 0; i < steps; i++) {
            cs225::HSLAPixel pixel2 = cs225::HSLAPixel(180,1,0.5);
            cs225::HSLAPixel & curPixel = vis->getPixel(round(x), round(y));
            curPixel = pixel2;

            x += Xinc;
            y += Yinc;
            
        }

        // int m_new = 2 * (y2-y1);
        // int error = m_new - (x2 - x1);
        // for(int x = x1, y = y1; x <= x2; x++) {
        //     cs225::HSLAPixel pixel2 = cs225::HSLAPixel(180,1,0.5);
        //     cs225::HSLAPixel & curPixel = vis->getPixel(x, y);
        //     curPixel = pixel2;

        //     error+= m_new;
        //     if(error >= 0) {
        //         y++;
        //         error -= 2 * (x2 - x1);
        //     }
        // }


    }
}


// void GraphData::graph_visualizer() {

// }

pair<vector<int>, vector<int>> GraphData::shortestPath(vector<Node*> graph, int start_id) {
    vector<int> distance;
    distance.resize(numNodes_);
    vector<int> previous;
    previous.resize(numNodes_);
    vector<Node*> nodes;
    vector<int> unvisited;
    vector<int> visited;
    for (Node* vertex: graph) {
        distance.at(vertex->id) = INT_MAX;
        unvisited.at(vertex->id) = vertex->id;
        nodes.push_back(vertex);
    }
    distance.at(start_id) = 0;
    visited.push_back(start_id);
    unvisited.erase(unvisited.begin() + start_id);

    /*while (!queue.empty()) {
        int min_index = findMinVal(visited);
        int min_node = nodes.at(min_index);
        nodes.erase(nodes.begin() + min_index);
        Node* current_min = adj_[min_node];

    }*/
    vector<int> result1;
    vector<int> result2;
    return pair<vector<int>, vector<int>>(result1, result2);

}

int GraphData::findMinVal(vector<int> visited) {
    int min_distance = INT_MAX;
    int result_vertex;
    for (int val : visited) {
        Node* current_val = adj_[val];
        while (current_val != nullptr) {
            int edge_distance = edges_[std::pair<int, int>(val, current_val->id)];
            if (edge_distance < min_distance) {
                min_distance = edge_distance;
                result_vertex = current_val->id;
            }
        }
    }
    return min_distance;
}



/*if (find(unvisited.begin(), unvisited.end(), current_min) != unvisited.end()) {
                int temp = distance.at(min_node) + edges_[std::pair(current_min->id, min_node)];
                if (temp < distance.at(current_min)) {
                    distance.at(current_min) = temp;
                    previous.at(current_min) = min_node;
                    unvisited.erase(unvisited.begin() + current_min->id);
                    visited.at()
                }
            }*/

