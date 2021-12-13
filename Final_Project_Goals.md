Goals
======================
 
Dataset: 
---------
<p> https://www.cs.utah.edu/~lifeifei/SpatialDataset.html<p>
<p>Our dataset consists of San Francisco road networks. Each node will be classified by a node ID, longitude and latitude. The edges would be classified by an edge ID, starting node ID, ending node ID, and the distance between nodes. This distance would be converted to the weight of the edge and will be used in the graph algorithms. We can download the files for the dataset online and store them in a .txt on our individual machines. The data is already stored conveniently, therefore we can keep the data in this format. 
  
The node file is converted into a map of id linking to the coordinates of the node. The edge file is converted to a map of a pair of the node ID’s to the distance between the nodes. This is converted into an adjacency list represented by a vector of node’s, which is an object holding the ID, coordinates, and the next node connected to the node. We keep these files in the datasets folder of our project.
 <p>
 
Graph Algorithms:
-----------------
<p>The algorithms we plan to implement for our dataset will be a graph traversal, namely breadth-first-search, as well as graph algorithms such as Dijkstra's shortest path and a data visualization algorithm. <p>
<p>Breadth First Search is a traversing algorithm in which we start at a starting node and traverse a graph by layer, using the neighbor nodes which are connected to our starting node. We essentially will move horizontally and visit all the nodes in the current layer, then move to the next layer till we find the node we are searching for. For the algorithm, we require the ID’s of the starting node of our graph and the node we are searching for. It Our target Big O should be O(|V + E| ) where V is the number of vertices/nodes and E is the number of edges in the graph. The algorithm will iterate until we find the node we search for. It will ultimately return a vector of booleans representing that if every node has been traversed or not.<p>
<p>The first algorithm will be Dijkstra’s algorithm which will be used to find the shortest path between two nodes. The function will take in a node ID to search for. The algorithm will construct an array of nodes to traverse through in order to complete the shortest path and return that as an output. This will let us see what the shortest path is for reaching a node in the road network. Since you are iterating through the vectors and edges to see what the smallest possible path is, the Big O of the algorithm is O (V+E).<p>
<p>The second algorithm will be the data visualization which will graph the nodes and edges along on a Longitude vs Latitude graph. First, using the CS 225 PNG and HSLA classes, we will iterate through the list of nodes and plot them. Then, we will connect the nodes on the scatterplot using Bresenham's line algorithm. This graph will show the density of the nodes in specific locations, as well as which nodes are connected to each other. Finally, it will return the PNG file that was created, and this file will be written to a file in main to display the results. The Big O of this algorithm will be O (V+E). <p>

Final Deliverables:	
---------
1) Complete parsing of files into correct objects
2) Complete BFS iteration 
3) Complete shortest path algorithm and data visualization algorithm(Along with PNG)
4) Create extensive test suites for algorithms using smaller dataset as well as large dataset

Timeline:	
---------
After the first week, our team hopes to have acquired the dataset and found a logical method to process it. By the mid-project check in, we hope to have our traversal algorithms as well as at least one of our graph algorithms implemented. A week before the final project is due, we hope to have our code base completed. At this point, we plan on beginning to create our final project report, as well as planning out our final presentation.
