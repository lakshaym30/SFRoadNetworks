# surajr4-lakshay3-cbhatia3-chiragm3

Instructions
======================
Summary of dataset: 
------------------


<p>Our dataset consists of San Francisco road networks. Each node will be classified by a node ID, longitude and latitude. The edges would be classified by an edge ID, starting node ID, ending node ID, and the distance between nodes. This distance would be converted to the weight of the edge and will be used in the graph algorithms. 
We can download the files for the dataset online and store them in a .txt on our individual machines. The data is already stored conveniently, therefore we can keep the data in this format. <p>


Files: 
------------------

1) GraphData.cpp/GraphData.h: File that contains the parsing of data, BFS algorithm, shortest path algorithm, and data visualization algorithm.
2) tests/test.cpp: File that contains all the testing for the different algorithms.

How to run algorithms:
----------------------
1)In main, set node file and edge file to send in to GraphData class. Set output image for data visualization algorithm in main.For shortest path algorithm, set target node id in main.
2)Run make in terminal to run BFS, shortest path, and data_visualization. The shortest path will be printed in terminal while the output image for the data visualization will be written


Test suites:
-------------


To run tests, run make tests in terminal. Will output results of test. 

Different tests Created:
1) Adjacency list tests using small datasets
2) Data visualization tests using small datasets
