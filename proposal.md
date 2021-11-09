Leading Question: 
</br>
Is it possible to determine and analyze road paths and patterns in California using a road network datasets?
</br>

Dataset: http://snap.stanford.edu/data/roadNet-CA.html 
</br>
Our dataset consists of the road network of California.
</br>
We can download the files for the dataset online, store them individually on our own machines, and convert the files into either a CSV file in order to process them. 
In order to process the data, there is only one text file that we have to preprocess which is stored in a .txt file. We will convert this into a CSV file in order to understand the data in a more ordered manner.
In order to parse this, we will write a Python function to convert the .txt file to .csv.
</br>

Graph Algorithms:
The algorithms we plan to implement for our dataset will be a graph traversal, namely breadth-first-search, as well as graph algorithms such as cycle detection and shortest path functions. 
For the breadth first search algorithm, we require the data of the node we are looking for as the input. 
It will then output the location of the node or the node itself. Our target Big O should be O (|V + E| ) where V is the number of vertices/nodes and E is the number of edges in the graph. 
For our cycle detection algorithm, no input is required. Our algorithm will traverse the graph and return the number of cycles that are present in the graph. 
This number will represent the interconnectedness of California roads. Similarly to BFS, our target Big O should be O (|V + E|). 
Our shortest path algorithm will input the two nodes we are developing the shortest path for. 
It will then output a vector of the edges required to construct the shortest, most efficient path between the nodes. Our target Big O will be O (|V + E| * log |V|). 
</br>

Timeline:	
After the first week, our team hopes to have acquired the dataset and found a logical method to process it. 
By the mid-project check in, we hope to have our traversal algorithms as well as at least one of our graph algorithms implemented. 
A week before the final project is due, we hope to have our code base completed.
At this point, we plan on beginning to create our final project report, as well as planning out our final presentation. 
</br>

