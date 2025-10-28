// classe ProblemSlver implementa gli algoritmi per la soluzione dei problemi resi disponibili
// minimum spanning tree problem --> Kruskal
// single-pair shortest path problem --> dijkstra
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <functional>
#include <queue>
#include "header/ProblemSolution.h"
#include "header/ProblemSolver.h"
#include "header/Graph.h"

ProblemSolution *KruskalMSTSolver::solve(const Graph &graph)
{ // override della funzione solve per implementare algoritmo di kruskal
    int vertices = graph.getNumVertices();
    Edge edges = graph.getEdges();

    std::sort(edges.begin(), edges.end()); // ordina in ordine non decrescente i vertici con i loro relativi pesi

    std::vector<int> parent(vertices); // vector inizializzato con i vertici del grafo
    for (int i = 0; i < vertices; ++i)
    {
        parent[i] = i; // tiene traccia del parent di ciascun vertice
    }
    std::function<int(int)> find = [&parent, &find](int u) { // funzione find che gestisce la ricerca del vertice e fa il return
        if (u != parent[u])
        {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    };

    auto unionSets = [&parent, &find](int u, int v) { // funzione unionset che unisce due insiemi u e v dei vertici
        int setU = find(u);
        int setV = find(v);
        parent[setU] = setV; // unisce insieme u e v
    };

    int totalWeight = 0;
    std::vector<std::pair<int, int>> mstEdges;

    for (const auto &edge : edges)
    { // scorrimento for-range dei bordi
        int weight = edge.second;
        int u = edge.first.first;
        int v = edge.first.second;

        if (find(u) != find(v))
        { // se i vertici sono diversi insieme aggiunge il loro peso nella soluzione e i vertici nel vector mstedges
            totalWeight += weight;
            mstEdges.push_back({u, v});
            unionSets(u, v); // unisce insieme
        }
    }

    return new KruskalMSTSolution(totalWeight, mstEdges); // return della soluzione dati il peso del cammino e il cammino stesso
}

ProblemSolution *DijkstraSolver::solve(const Graph &graph)
{ // override della funzione solve per implementare algoritmo di dijkstra

    const int INF = std::numeric_limits<int>::max(); // costante rappresenta infinito (ovvero quando il peso di quella distanza tra vertici non è definita)

    int vertices = graph.getNumVertices();
    std::vector<std::vector<std::pair<int, int>>> adjList(vertices); // lista di adiacenza

    for (const auto &edge : graph.getEdges())
    { // iterazione della lista
        int u = edge.first.first;
        int v = edge.first.second;
        int weight = edge.second;
        adjList[u].push_back({v, weight}); // aggiunta vertice v
        adjList[v].push_back({u, weight}); // aggiunta vertice u
    }

    std::vector<int> dist(vertices, INF); // inizializza le distanze a infinito
    dist[DijkstraSolver::src] = 0;        // ditanza tra sorgente e se stessa a 0

    // definita queue con priorità per definire la distanza minore
    using pii = std::pair<int, int>;
    std::priority_queue<pii, std::vector<pii>, std::greater<pii>> pq;
    pq.push({0, src}); // aggiunta la sorgente alla queue

    while (!pq.empty())
    {                            // se la queue non è vuota
        int u = pq.top().second; // u è vertice con ditanza minore
        pq.pop();                // toglie da queue

        if (u == dest)
        { // se u è la destinazione allora ecco la soluzione
            return new DijkstraSolution(dist[u]);
        }

        // vicini di u per trovare percorso più corto nel caso esista
        for (const auto &neighbor : adjList[u])
        {
            int v = neighbor.first;
            int weight = neighbor.second;

            // se la distanza è definita (diversa da infinito) e la distanza di u più peso e minore di v (ovvero c'è
            // un percorso con peso minore) viene sostituito il vertice della soluzione
            if (dist[u] != INF && dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return new DijkstraSolution(INF); // se non raggiungibile allora stampa infinito
}
