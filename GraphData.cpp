#include "GraphData.h"

GraphData::GraphData() {}

GraphData::GraphData(string data1, string data2) {
    HSLAPixel pixel;
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

PNG GraphData::graphVisualizer() {
    const int width = 12000;
    const int height = 12000;
    PNG* vis = new PNG(width, height);

    //creating point on png for every node
    for (Node* val : adj_) {
        //creating 3 by 3 for each node for visualization
        for (int i = -1; i < 2; i++) {
            for (int j = -1; j < 2; j++) {
                HSLAPixel & curPixel = vis->getPixel(val->x + i, height - val->y + j);
                if (j % 2 == 0) curPixel = BLUE; //switching colors for fun
                else curPixel = RED; 
            }
        }
    }

    map<pair<int, int>, bool> visited;
    //drawing edges between appropriate nodes with connections
    for (Node* val : adj_) {
        Node* next_ = val->next;
        pair<int, int> p1 = make_pair(val->id, next_->id);
        pair<int, int> p2 = make_pair(next_->id, val->id);

        while (next_ != nullptr) {     
            if (!visited[p1] && !visited[p2]) { //ensuring no lines are redrawn
                double x1 = val->x;
                double y1 = height - val->y; //12000 - val bc in png 0, 0 in top left corner when should be in bottom left
                double x2 = next_->x;
                double y2 = height - next_->y;

                double dx = x2 - x1;
                double dy = y2 - y1;

                //Bresenham's line algo   
                //requires that first point is in bottom left and second is top right
                //so we need to swap the x and y values appropriately so algo doesnt break
                bool steep = abs(dy) > abs(dx);
                if (steep) {
                    swap(x1, y1);
                    swap(x2, y2);
                }

                if (x1 > x2) {
                    swap(x1, x2);
                    swap(y1, y2);
                }

                dx = x2 - x1;
                dy = abs(y2 - y1);

                double err = dx / 2.0;
                int y_inc = (y1 < y2) ? 1 : -1;
                int y = (int) y1;

                int x_max = (int) x2;
                for (int x = (int) x1; x <= x_max; x++) {  
                    //using alternate x or y with respect to stepp
                    if (steep) {
                        HSLAPixel & curPixel = vis->getPixel(y, x);
                        curPixel = BLACK;
                    } else {
                        HSLAPixel & curPixel = vis->getPixel(x, y);
                        curPixel = BLACK;
                    }

                    err -= dy;
                    if (err < 0) {
                        y += y_inc;
                        err += dx;
                    }

                    if (x >= width || y >= height) {
                        cout << "x: " << x << ", y: " << y << endl;
                    }
                } // for x
                visited[p1] = true;
                visited[p2] = true;
            }  // if visited
            
            next_ = next_->next;
        }
        
    }
    
    return *vis;

}

/*
pair<vector<int>, vector<Node*>> GraphData::shortestPath(vector<Node*> graph, int start_id) {
    vector<int> distance;
    distance.resize(numNodes_);
    vector<Node*> previous;
    previous.resize(numNodes_);
    vector<Node*> nodes; //priority queue
    vector<Node*> visited;
    visited.resize(numNodes_);
    for (Node* vertex: graph) {
        distance.at(vertex->id) = INT_MAX;
        previous.at(vertex->id) = nullptr;
        nodes.push_back(vertex);
    }
    distance.at(start_id) = 0;
    visited.push_back(nodes.at(start_id));
    vector<Node*> neighbors;


   while (nodes.size() != 0) {
       neighbors.clear();
        std::cout << "Nodes size: " << nodes.size() << std::endl;
       Node* checkNode = visited.at(visited.size() - 1);
       Node* current_check = adj_.at(checkNode->id);
       while (current_check->next != nullptr) {
           current_check = current_check->next;
           if (std::find(visited.begin(), visited.end(), current_check) == visited.end()) {
               double temporary_distance = distance.at(checkNode->id) + findDist(checkNode->id, current_check->id);
                if (temporary_distance < distance.at(current_check->id)) {
                    distance.at(current_check->id) = temporary_distance;
                    previous.at(current_check->id) = checkNode;
                    neighbors.push_back(current_check); 
                }
           } 
       }
        int nextID = findSmallerNeighbor(checkNode, neighbors);
        visited.push_back(nodes.at(nextID));
        nodes.erase(nodes.begin() + checkNode->id);
    }

    pair<vector<int>, vector<Node*>> result;
    result.first = distance;
    result.second = previous;
    return result;

}

int GraphData::findSmallerNeighbor(Node* checkNode, vector<Node*> neighbors) {
    double smallestWeight = DBL_MAX;
    int result_node;
    for (Node* val : neighbors) {
        double weight = findDist(checkNode->id, val->id);
        if (weight < smallestWeight) {
            smallestWeight = weight;
            result_node = val->id;
        }
    }
    return result_node; 
}

int GraphData::findMinVal(Node* checkNode, vector<Node*> visited) {
    double min_distance = DBL_MAX;
    int result_vertex;
    Node* current_val = adj_.at(checkNode->id);
    while (current_val->next != nullptr) {
        current_val = current_val->next;
        if (std::find(visited.begin(), visited.end(), current_val) == visited.end()) {
            double edge_distance = findDist(checkNode->id, current_val->id);
            std::cout << checkNode->id << ", " << current_val->id << ", " << edge_distance << std::endl;
            if (edge_distance < min_distance) {
                min_distance = edge_distance;
                result_vertex = current_val->id;
            }
        }
    }
    std::cout << result_vertex << std::endl;
    return result_vertex;
}

vector<Node*> GraphData::getAdjacencyList() {
    return adj_;
}
*/


