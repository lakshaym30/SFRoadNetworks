#include "GraphData.h"

int main() {
    //GraphData gd("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    GraphData gd("datasets/SFnodes.txt", "datasets/SFedges.txt");

    //PNG image = gd.graphVisualizer();
    //image.writeToFile("SFGraph.png");
    pair<vector<int>, vector<int>> result = gd.shortestPath(44);
    //vector<bool> output = gd.BFS(0);
    //cout << output.size() << endl;
    return 0;
}
