#include "GraphData.h"

int main() {
    GraphData gd("datasets/SFnodes.txt", "datasets/SFedges.txt");

    cs225::PNG result = gd.graphVisualizer();
    result.writeToFile("SFGraph.png");
    gd.shortestPath(1, 2);
    return 0;
}
