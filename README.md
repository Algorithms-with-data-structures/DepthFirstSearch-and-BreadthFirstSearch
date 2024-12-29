# Depth-First and Breadth-First Search (C++)

## Overview
This program implements **Depth-First Search (DFS)** and **Breadth-First Search (BFS)** algorithms for graph traversal in C++. It allows users to load a graph from a file, traverse the graph using DFS or BFS, and display the graph's adjacency matrix. Both search algorithms find paths between a start node and a destination node, measuring the cost (number of edges) and the time taken for the search.

### Depth-First Search (DFS)
DFS is an algorithm used to explore all the nodes of a graph by going as deep as possible into a branch before backtracking. It uses a stack to keep track of nodes to visit next.

### Breadth-First Search (BFS)
BFS explores all neighbors of a node before moving to the next level of nodes. It uses a queue to ensure nodes are processed in a first-in-first-out (FIFO) order.

### Graph Representation
The graph is represented as an adjacency matrix loaded from a file. The file specifies the number of nodes, the number of edges, and the edges themselves (including weights, which are assumed to be 1).

---

## Features
1. Load a graph from a file.
2. Perform **Depth-First Search (DFS)**.
3. Perform **Breadth-First Search (BFS)**.
4. Display the graph's adjacency matrix.

---

## File Format for Graph Input
The program reads the graph structure from a text file. The file format is as follows:

```
<number_of_nodes>
<number_of_edges>
<node1> <node2> <weight>
<node1> <node2> <weight>
...
```

### Example File (`graph.txt`):
```
8
10
1 2 1
1 8 1
3 4 1
3 7 1
3 8 1
4 5 1
4 7 1
5 6 1
5 7 1
6 7 1
```
This file specifies a graph with 8 nodes, 10 edges, and connections between nodes as shown.

---

## How to Use

### Compilation and Execution
1. **Compile the code**:
   ```bash
   g++ -o graph_search graph_search.cpp
   ```

2. **Run the program**:
   ```bash
   ./graph_search
   ```

### Menu Options
When you run the program, you will be presented with the following menu:

```
Depth and Breadth Search - Options:
1) Load graph from file
2) Depth-First Search from node s to d
3) Breadth-First Search from node s to d
4) Display adjacency matrix
5) Exit
```

#### 1) Load Graph from File
- Ensure your graph input file (e.g., `graph.txt`) is correctly formatted and placed in the same directory as the executable.
- Edit the filename in the code (default: `graphBig.txt`) if needed.

#### 2) Depth-First Search
- Specify the start node and the destination node.
- The program will display the path, cost (number of edges), and search time.

#### 3) Breadth-First Search
- Specify the start node and the destination node.
- The program will display the path, cost, and search time.

#### 4) Display Adjacency Matrix
- View the adjacency matrix representation of the graph.

#### 5) Exit
- Exit the program.

---

## Example Usage
### Input File (`graph.txt`):
```
8
10
1 2 1
1 8 1
3 4 1
3 7 1
3 8 1
4 5 1
4 7 1
5 6 1
5 7 1
6 7 1
```

### Program Run:
```
Depth and Breadth Search - Options:
1) Load graph from file
2) Depth-First Search from node s to d
3) Breadth-First Search from node s to d
4) Display adjacency matrix
5) Exit

Choice: 1
Graph successfully loaded from 'graph.txt'.

Choice: 2
Start node: 1
Destination node: 7
Path: 1 8 3 7
Cost: 3
Search Time: 10µs.

Choice: 3
Start node: 1
Destination node: 7
Path: 1 8 3 7
Cost: 3
Search Time: 8µs.

Choice: 4
Nodes:
1 2 3 4 5 6 7 8

Matrix:
1 0 0 0 0 0 0 1
0 1 0 0 0 0 0 0
0 0 1 1 0 0 1 1
0 0 1 1 1 0 1 0
0 0 0 1 1 1 1 0
0 0 0 0 1 1 1 0
0 0 1 1 1 1 1 0
1 0 1 0 0 0 0 1

Choice: 5
Exiting...
```

---

## Notes
- The program assumes undirected graphs with symmetric adjacency matrices.
- Error handling is included for invalid file formats and invalid node indices.
- Search time is measured in microseconds for performance evaluation.

