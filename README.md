# surajr4-lakshay3-cbhatia3-chiragm3

Instructions
======================
Summary of dataset: 
------------------


<p>Our dataset consists of San Francisco road networks. Each node will be classified by a node ID, longitude and latitude. The edges would be classified by an edge ID, starting node ID, ending node ID, and the distance between nodes. This distance would be converted to the weight of the edge and will be used in the graph algorithms. 
We can download the files for the dataset online and store them in a .txt on our individual machines. The data is already stored conveniently, therefore we can keep the data in this format. <p>


Files: 
------------------

1) datasets/smallDatasetEdges.txt: File that contains all edges for the small dataset that we created.
2) datasets/smallDatasetNodes.txt: File that contains all nodes for the small dataset that we created.
3) datasets/SFedges.txt: File that contains all edges for our large dataset.
4) datasets/SFnodes.txt: File that contains all nodes for our large dataset.
5) GraphData.cpp/GraphData.h: File that contains the parsing of data, BFS algorithm, shortest path algorithm, and data visualization algorithm.
6) tests/test.cpp: File that contains all the testing for the different algorithms.

How to run algorithms:
----------------------
1)In main, set node file and edge file to send in to GraphData class. Set output image for data visualization algorithm in main.For shortest path algorithm, set target node id in main.
2)Run make in terminal to run BFS, shortest path, and data_visualization. The shortest path will be printed in terminal while the output image for the data visualization will be written


Test suites:
------------
To run tests, run make tests in terminal. Will output results of test. 

Different tests Created:
1) Data visualization tests using small datasets
    > Checked nodes at center, border, and edges to check if correct pixel is drawn.
2) Shortest Path Algorithm using small datasets
    > Traced algorithm on small dataset and checked if expected values matched values in vectors produced by the shortest path algoritm.
3) Shortest Path Algorithm using big datasets
    > Traced algorithm starting from random nodes and checked if expected values matched values in vectors produced by the shortest path algorithm.
4) BFS
    > Checked if all values in the graph were visited for both the small and big datsets.

