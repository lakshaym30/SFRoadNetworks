#include "GraphData.h"

int main() {
    GraphData gd("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");

    //cs225::PNG result = gd.graphVisualizer();
    //result.writeToFile("SFGraph.png");
    pair<vector<int>, vector<Node*>> result = gd.shortestPath(gd.getAdjacencyList(), 3);
    return 0;
}
