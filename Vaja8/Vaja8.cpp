// DEPTH AND BREADTH SEARCH

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>
#include <climits>
#include <chrono>
using namespace std;

struct Node {
    int predecessor;
    int status; // 0 - unexplored, 1 - being explored, 2 - fully explored
    int distance;
    int index;
    int name;
};

std::stack<Node*> nodeStack;
vector<Node*> queue;
string fileName = "graphBig.txt";

void showMenu() {
    cout << endl;
    cout << "Depth and Breadth Search - Options:" << endl;
    cout << "1) Load graph from file" << endl;
    cout << "2) Depth-First Search from node s to d" << endl;
    cout << "3) Breadth-First Search from node s to d" << endl;
    cout << "4) Display adjacency matrix" << endl;
    cout << "5) Exit" << endl;
    cout << endl;
    cout << "Choice: ";
}

int numberOfNodes;

int** loadGraph(vector<Node*>& nodes) {
    int numberOfEdges;

    ifstream file(fileName);

    // Check if the file was successfully opened
    if (!file.is_open()) {
        cerr << "Error: Unable to open file '" << fileName <<  "'. Please check if the file exists and is accessible." << endl;
        return nullptr;
    }

    // Try reading the first two integers (number of nodes and edges)
    if (!(file >> numberOfNodes >> numberOfEdges)) {
        cerr << "Error: Failed to read graph metadata (number of nodes and edges) from '" << fileName << "'. Ensure the file format is correct." << endl;
        return nullptr;
    }

    for (int i = 0; i < numberOfNodes; i++) {
        Node* newNode = new Node();
        newNode->index = i;
        newNode->name = i + 1;
        newNode->status = 0;
        nodes.push_back(newNode);
    }

    int** adjacencyMatrix = new int* [numberOfNodes];
    for (int i = 0; i < numberOfNodes; i++) {
        adjacencyMatrix[i] = new int[numberOfNodes]();
    }

    int node1, node2, cost;
    while (file >> node1 >> node2 >> cost) {
        if (node1 <= 0 || node2 <= 0 || node1 > numberOfNodes || node2 > numberOfNodes) {
            cerr << "Error: Invalid node indices in '" << fileName << "'. Ensure all nodes are within the range 1 to " << numberOfNodes << "." << endl;
            return nullptr;
        }
        adjacencyMatrix[node1 - 1][node2 - 1] = 1;
        adjacencyMatrix[node2 - 1][node1 - 1] = 1; // Mark nodes as neighbors
    }

    if (file.bad()) {
        cerr << "Error: An I/O error occurred while reading '" << fileName << "'" << endl;
        return nullptr;
    }

    cout << "Graph successfully loaded from '" << fileName << "'" << endl;
    return adjacencyMatrix;
}


void displayPath(vector<Node*> nodes, int* adjacencyMatrix[], Node* startNode, Node* currentNode) {
    if (startNode->name == currentNode->name)
        cout << "Path: " << currentNode->name << " ";
    else {
        if (currentNode->predecessor == -1)
            cout << "No path exists between " << startNode->name << " and " << currentNode->name << "!" << endl;
        else {
            displayPath(nodes, adjacencyMatrix, startNode, nodes[currentNode->predecessor]);
            cout << currentNode->name << " ";
        }
    }
}

void depthFirstSearch(vector<Node*> nodes, int* adjacencyMatrix[], int start, int destination) {
    bool exists = false;

    for (auto& node : nodes) {
        if (node->name == start) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        cout << "Node " << start << " does not exist!" << endl << endl;
        return;
    }

    exists = false;
    for (auto& node : nodes) {
        if (node->name == destination) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        cout << "Node " << destination << " does not exist!" << endl << endl;
        return;
    }

    for (auto& node : nodes) {
        if (node->name != start) {
            node->status = 0;
            node->distance = INT_MAX;
            node->predecessor = -1;
        }
    }

    nodes[start - 1]->status = 1;
    nodes[start - 1]->distance = 0;
    nodes[start - 1]->predecessor = -1;
    nodeStack.push(nodes[start - 1]);

    auto startTime = std::chrono::steady_clock::now();

    while (!nodeStack.empty()) {
        Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (currentNode->name == destination) {
            auto endTime = std::chrono::steady_clock::now();
            cout << endl;
            displayPath(nodes, adjacencyMatrix, nodes[start - 1], currentNode);
            cout << endl;
            cout << "Cost: " << currentNode->distance << endl;
            cout << "Search Time: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "μs." << endl;
            cout << endl;
            return;
        }

        for (int i = 0; i < nodes.size(); i++) {
            if (adjacencyMatrix[currentNode->index][i] == 1) {
                if (nodes[i]->status == 0) {
                    nodes[i]->status = 1;
                    nodes[i]->distance = currentNode->distance + 1;
                    nodes[i]->predecessor = currentNode->index;
                    nodeStack.push(nodes[i]);
                }
            }
        }

        currentNode->status = 2;
    }
}

void breadthFirstSearch(vector<Node*> nodes, int* adjacencyMatrix[], int start, int destination) {
    bool exists = false;

    for (auto& node : nodes) {
        if (node->name == start) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        cout << "Node " << start << " does not exist!" << endl << endl;
        return;
    }

    exists = false;
    for (auto& node : nodes) {
        if (node->name == destination) {
            exists = true;
            break;
        }
    }
    if (!exists) {
        cout << "Node " << destination << " does not exist!" << endl << endl;
        return;
    }

    for (auto& node : nodes) {
        if (node->name != start) {
            node->status = 0;
            node->distance = INT_MAX;
            node->predecessor = -1;
        }
    }

    nodes[start - 1]->status = 1;
    nodes[start - 1]->distance = 0;
    nodes[start - 1]->predecessor = -1;
    queue.push_back(nodes[start - 1]);

    auto startTime = std::chrono::steady_clock::now();

    while (!queue.empty()) {
        Node* currentNode = queue.front();
        queue.erase(queue.begin());

        if (currentNode->name == destination) {
            auto endTime = std::chrono::steady_clock::now();
            cout << endl;
            displayPath(nodes, adjacencyMatrix, nodes[start - 1], currentNode);
            cout << endl;
            cout << "Cost: " << currentNode->distance << endl;
            cout << "Search Time: " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "μs." << endl;
            cout << endl;
            return;
        }

        for (int i = 0; i < nodes.size(); i++) {
            if (adjacencyMatrix[currentNode->index][i] == 1) {
                if (nodes[i]->status == 0) {
                    nodes[i]->status = 1;
                    nodes[i]->distance = currentNode->distance + 1;
                    nodes[i]->predecessor = currentNode->index;
                    queue.push_back(nodes[i]);
                }
            }
        }

        currentNode->status = 2;
    }
}

void displayAdjacencyMatrix(vector<Node*> nodes, int* adjacencyMatrix[]) {
    cout << "Nodes:" << endl;
    for (auto& node : nodes) {
        cout << node->name << " ";
    }
    cout << endl;
    cout << "\nMatrix:" << endl;
    for (int i = 0; i < nodes.size(); i++) {
        cout << nodes[i]->name << " ";
        for (int j = 0; j < nodes.size(); j++) {
            cout << adjacencyMatrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    int destination, start;
    vector<Node*> nodes;
    int** adjacencyMatrix = new int* [numberOfNodes];

    int choice;
    bool isRunning = true;

    do {
        showMenu();
        cin >> choice;
        system("cls");
        switch (choice) {
        case 1:
            adjacencyMatrix = loadGraph(nodes);
            break;
        case 2:
            cout << "Start node: ";
            cin >> start;
            cout << "Destination node: ";
            cin >> destination;
            depthFirstSearch(nodes, adjacencyMatrix, start, destination);
            break;
        case 3:
            cout << "Start node: ";
            cin >> start;
            cout << "Destination node: ";
            cin >> destination;
            breadthFirstSearch(nodes, adjacencyMatrix, start, destination);
            break;
        case 4:
            displayAdjacencyMatrix(nodes, adjacencyMatrix);
            break;
        case 5:
            isRunning = false;
            break;
        default:
            cout << "ERROR! Invalid choice." << endl;
            break;
        }
    } while (isRunning);

    return 0;
}