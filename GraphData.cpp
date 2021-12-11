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
            float dist = stof(distString);

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
            pair<int, int> p(node1, node2);
            pair<int, int> p2(node2, node1);
            edges_[p] = dist;
            edges_[p2] = dist;
            //cout << "id1: " << node1 << ", id2: " << node2 << ", dist: " << dist << endl;
            cout << "id1: " << p.first << ", id2: " << p.second << ", dist: " << edges_[p] << endl;
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

// float GraphData::findDist(int node1, int node2) {
//     pair<int, int> primary(node1, node2);
//     pair<int, int> alternate(node2, node1);
//     float primary_dist_ = edges_[primary];
//     float alternate_dist_ = edges_[alternate];

//     if (primary_dist_ != 0 && alternate_dist_ == 0) {
//         return primary_dist_;
//     } else if (alternate_dist_ != 0) {
//         return alternate_dist_;
//     }
//     std::cout << "reached end" << endl;
//     return -1;
// }

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
            if (!visited[p1] || !visited[p2]) { //ensuring no lines are redrawn
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

                    //if (x >= width || y >= height) cout << "x: " << x << ", y: " << y << endl;
                } // for loop
                visited[p1] = true;
                visited[p2] = true;
            }  // if visited
            
            next_ = next_->next;
        }
        
    }
    
    return *vis;

}


pair<vector<int>, vector<Node*>> GraphData::shortestPath(vector<Node*> graph, int start_id) {
    vector<Node*> visited;
    vector<Node*> unvisited;
    vector<int> distances;
    vector<Node*> previous;

    for (Node* node : graph) {
        unvisited.push_back(node);
        distances.push_back(INT_MAX);
        previous.push_back(nullptr);
    }

    distances.at(start_id) = 0;
    int check_id = start_id;
    int delete_count = 0;
    while (unvisited.size() != 0) {
        Node* check_node = adj_.at(check_id);
        pair<int, int> p;
        std::cout << "starting: " << check_id <<  std::endl;
        int min_distance = INT_MAX;
        while (check_node != nullptr && check_node->next != nullptr) {
            check_node = check_node->next;
            //std::cout << check_node->id << std::endl;
            p = make_pair(check_id, check_node->id);
            if (find(visited.begin(), visited.end(), check_node) == visited.end()) {
                std::cout << "id1: " << check_id << ", id2: " << check_node->id << ", dist: " << edges_[p] << endl;
                //std::cout << "neighbor:"  << check_node->id << ", distance: " << edges_[p] << std::endl;
                // if (distances.at(check_node->id) > findDist(check_id, check_node->id)) {
                //     distances.at(check_node->id) = findDist(check_id, check_node->id);
                //     previous.at(check_node->id) = adj_.at(check_id);
                // }
                // if (findDist(check_id, check_node->id) < min_distance) {
                //     min_distance = findDist(check_id, check_node->id);
                //     check_id = check_node->id;
                // }    
                if (distances.at(check_node->id) > edges_[p]) {
                    distances.at(check_node->id) = edges_[p];
                    previous.at(check_node->id) = adj_.at(check_id);
                }
            }
        }
    
        //cout << "seg fault checker" << endl;
        //cout << check_node->id << endl;
        if (edges_[p] + distances.at(check_id) < min_distance) {
            min_distance = edges_[p];
            check_id = check_node->id;
        }   
        //cout << "check id " << check_id << endl;
        // for (Node* n : unvisited) {
        //     cout << "loop" << n->id << endl;
        // }
        // vector<Node*>::iterator iter;
        // iter = remove(unvisited.begin(), unvisited.end(), adj_.at(check_id));
        unvisited.erase(unvisited.begin() + check_id - delete_count);
        delete_count++;
        //unvisited.remove(unvisited.begin(), unvisited.end(), check_id);
        //cout << "size " << adj_.size() << endl;
        //cout << "vect " << adj_.at(check_id) << endl;
        //cout << " size " << unvisited.size() << endl;
        visited.push_back(adj_.at(check_id));
    }
    pair<vector<int>, vector<Node*>> result;
    result.first = distances;
    result.second = previous;
    return result;
}

// double GraphData::findDist(int node1, int node2) {
//     pair<double, double> primary(node1, node2);
//     pair<double, double> alternate(node2, node1);
//     double primary_dist_ = edges_[primary];
//     double alternate_dist_ = edges_[alternate];
//     if (primary_dist_ != 0) {
//         return primary_dist_;
//     } else if (alternate_dist_ != 0) {
//         return alternate_dist_;
//     }
//     return 0;
// }



vector<Node*> GraphData::getAdjacencyList() {
    return adj_;
}



