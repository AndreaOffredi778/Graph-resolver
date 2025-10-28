// classe ProblemSolution che fa l' override della funzione membro output della classe stessa per gestire l' output in base
// al problema dato

#include <iostream>
#include <fstream>
#include <sstream>
#include "header/ProblemSolution.h"
#include "header/ProblemSolver.h"

std::ostream &KruskalMSTSolution::output(std::ostream &os) const
{ // funzione che formatta stampa per soluzione problema kruskal
    os << "\nTotal Weight of MST: " << totalWeight << "\nEdges in the MST:\n";
    int edgeNum = 1;
    for (const auto &edge : mstEdges)
    {
        os << "Edge " << edgeNum++ << ": " << edge.first << " - " << edge.second << "\n";
    }
    return os;
}

std::ostream &DijkstraSolution::output(std::ostream &os) const
{ // funzione che formatta stampa per soluzione problema dijkstra
    const int INF = std::numeric_limits<int>::max();
    if (!(distance == INF))
    {
        os << "\nShortest path distance: " << distance << "\n";
        return os;
    }
    else
    {
        os << "\nShortest path doesn't exist between the given nodes\n";
    }
    return os;
}
