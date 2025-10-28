#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>

typedef std::vector<std::pair<std::pair<int, int>, int>> Edge; // definito un tipo per gestire gli spigoli di un grafo, sono rappresntati da coppia
                                                               // vertici e il loro peso. es. (u,v,5)

class Graph
{
public:
     Graph() : vertices(0) {}; // definito costruttore di default
    ~Graph(){};        // definito destructor

    // funzioni membro
    bool importGraph(const std::string &filename);
    void printgraph() const;
    int getNumVertices() const;
    const Edge &getEdges() const;
    bool isEmpty() const;

private:
    Edge edges;   // edges rappresenta il vettore degli archi di un grafo
    int vertices; // indica i vertici di un grafo
};

#endif // GRAPH_H