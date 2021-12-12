#include "GraphData.h"

int main() {
    //GraphData gd("datasets/smallDatasetNodes.txt", "datasets/smallDatasetEdges.txt");
    GraphData gd("datasets/SFnodes.txt", "datasets/SFedges.txt");

    PNG image = gd.graphVisualizer();
    image.writeToFile("SFGraph.png");
    pair<vector<int>, vector<int>> result = gd.shortestPath(gd.getAdjacencyList(), 44);

    return 0;
}
