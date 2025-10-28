# Graph Problem Solver Application

![C++](https://img.shields.io/badge/language-C++-blue) ![License](https://img.shields.io/badge/license-MIT-green)

A C++ application to solve graph problems, including **Minimum Spanning Tree** and **Single-Pair Shortest Path**, using Kruskal’s and Dijkstra’s algorithms.

---

## Table of Contents

- [Directory Structure](#directory-structure)  
- [Available Problem Solutions](#available-problem-solutions)  
- [Application Workflow](#application-workflow)  
- [Class Descriptions](#class-descriptions)  
- [Implementation Choices](#implementation-choices)  
- [Usage](#usage)  

---

## Directory Structure

├── instances # .txt files containing graph descriptions

├── header # header files for class definitions

├── main.cpp # main file, compiles into executable

├── Menu.cpp # implementation of the Menu class

├── Graph.cpp # implementation of the Graph class

├── ProblemSolver.cpp# implementation of the ProblemSolver class

├── ProblemSolution.cpp # implementation of the ProblemSolution class


## Available Problem Solutions

- **Minimum Spanning Tree (MST):**  
  Implemented using **Kruskal's algorithm**. Sorts edges by weight and adds them to the MST if they do not form a cycle.  

- **Single-Pair Shortest Path (SPSP):**  
  Implemented using **Dijkstra's algorithm**. Computes the shortest path between two nodes defined by the user (source and destination).  

---

## Application Workflow

1. `main.cpp` creates a `Menu` object to interact with the user.  
2. When importing a graph, a `Graph` object is initialized. Users can iterate over problems or print graph edges.  
3. To solve a problem, a `ProblemSolver` pointer is initialized based on the user’s selection.  
4. The `ProblemSolver` pointer is used to generate a `ProblemSolution` object that prints the problem solution.  

---

## Class Descriptions

### Graph

- **Represents:** Simple undirected weighted graph  
- **Members:**  
  - `vertices` → list of vertices  
  - `edges` → vector of edges `(u, v, weight)`  
- **Methods:**  
  - `bool importGraph(const std::string &filename)` → imports a graph from a file  
  - `void printGraph() const` → prints a formatted list of edges  
  - `int getNumVertices() const` → returns the number of vertices  
  - `const Edge &getEdges() const` → returns edges  
  - `bool isEmpty() const` → checks if the graph is empty  

### ProblemSolver (Abstract)

- **Represents:** Generic problem solver  
- **Members:** None  
- **Methods:**  
  - `virtual solve(const Graph &graph)` → pure virtual function to solve a problem  

### KruskalMSTSolver

- **Inherits:** `ProblemSolver`  
- **Represents:** MST solver using Kruskal's algorithm  
- **Methods:**  
  - `solve(const Graph &graph)` → implements Kruskal's algorithm  

### DijkstraSolver

- **Inherits:** `ProblemSolver`  
- **Represents:** Single-pair shortest path solver using Dijkstra's algorithm  
- **Methods:**  
  - `solve(const Graph &graph)` → implements Dijkstra's algorithm  

### ProblemSolution (Abstract)

- **Represents:** Solution of a graph problem  
- **Members:** None  
- **Methods:**  
  - `virtual void printSolution(std::ostream &os) const` → pure virtual function to print solution  

### KruskalMSTSolution

- **Inherits:** `ProblemSolution`  
- **Represents:** MST solution printer  
- **Methods:**  
  - `printSolution(std::ostream &os) const` → prints MST solution  

### DijkstraSolution

- **Inherits:** `ProblemSolution`  
- **Represents:** Single-pair shortest path solution printer  
- **Methods:**  
  - `printSolution(std::ostream &os) const` → prints shortest path solution  

### Menu

- **Represents:** User interface for problem selection  
- **Methods:** Provides interaction with the user to select problems and import graphs  

---

## Implementation Choices

- Graph represented using a **vector of edges**: `(u, v, weight)`  
- Chosen algorithms:  
  - **Kruskal** for MST  
  - **Dijkstra** for shortest path  

---

## Usage

1. Compile the project:

```bash
g++ main.cpp Graph.cpp Menu.cpp ProblemSolver.cpp ProblemSolution.cpp -o GraphSolver
Run the executable:

bash
Copia codice
./GraphSolver
Use the Menu to import graphs, select problems, and print solutions.
