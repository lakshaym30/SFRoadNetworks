#include "GraphData.h"

int main() {
    GraphData gd("datasets/SFnodes.txt", "datasets/SFedges.txt");
    gd.shortestPath(1, 2);
    return 0;
}
