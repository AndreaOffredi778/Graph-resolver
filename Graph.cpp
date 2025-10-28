/*La classe Graph gestisce le operazione di importazione del grafo da file e le operazioni affine al grafo*/

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using std::cin;
using std::cout;
using std::string;
using std::vector;
#include "header/Graph.h"

bool Graph::importGraph(const std::string &fileName) // metodo che legge da file per importare il grafo dato il nome del file stesso
{
    
    std::ifstream file(fileName); // legge il file
    if (!file.is_open())
    {
        std::cerr << "File opening is incorrect!!!" << std::endl; // gestione per quando il file non è presente
        return false;
    }

     edges.clear(); //pulisce nel caso ci siano elementi presenti non voluti
    vertices = 0;

    string fileNameIn, temp; // sequenza di letture da file per i diversi attributi del grafo: vertici, peso
    file >> temp >> fileNameIn;
    file >> temp >> temp;
    file >> temp >> vertices;
    edges.resize(vertices);
    int edge1, edge2, weight;
    if (!(file >> edge1 >> edge2 >> weight)) {
            std::cerr << "Format error!!!\n";
            return false;
        }

    while (file >> edge1 >> edge2 >> weight) // lettura righe degli edge e pesi del grafo
    {
        if(edge1!=edge2 && weight!=0)
        edges.push_back({{edge1, edge2}, weight}); // inserimento valori nel vettore edges
    }
    file.close();
    return true;
}

int Graph::getNumVertices() const // ritorna il numero di vertici del grafo
{
    return vertices;
}

const Edge &Graph::getEdges() const // ritorna la coppia spigolo
{
    return edges;
}

bool Graph::isEmpty() const // ritorna in caso il grafo sia vuoto (vector vuoto)
{
    return edges.empty();
}

void Graph::printgraph() const // stampa formattata del grafo
{
    for (size_t i = 0; i < edges.size(); ++i) {
        int u = edges[i].first.first;
        int v = edges[i].first.second;
        int weight = edges[i].second;
         if (u!=v)
        std::cout << "Edge " << i-vertices << ": u " << u << " - v " << v << " Weight " << weight << "\n";
    }
   
}
