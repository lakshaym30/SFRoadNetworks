#include "GraphData.h"

int main() {
    GraphData gd("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    //GraphData gd("datasets/SFnodes.txt", "datasets/SFedges.txt");

    //PNG result = gd.graphVisualizer();
    //result.writeToFile("SFGraph.png");
    pair<vector<int>, vector<int>> result = gd.shortestPath(gd.getAdjacencyList(), 0);
    for (int i : result.second) {
        cout << i << endl;
    }
    return 0;
}
