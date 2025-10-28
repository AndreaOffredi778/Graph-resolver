#ifndef PROBLEMSOLUTION_H
#define PROBLEMSOLUTION_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class ProblemSolution
{ // definizione classe ProblemSolution per stampa soluzione
public:
    virtual ~ProblemSolution() = default;
    virtual std::ostream &output(std::ostream &os) const = 0; // funzione virtuale che verrà overridata dalle classi derivate
};

std::ostream &operator<<(std::ostream &os, const ProblemSolution &solution); // gestione per operatore <<

// definizione classe derivata per gestione diretta del problema di kruskal
class KruskalMSTSolution : public ProblemSolution
{
public:
    KruskalMSTSolution(int totalWeight, const std::vector<std::pair<int, int>> &mstEdges) // costruttore che definisce peso soluzione
                                                                                          // e gli archi del cammino minimo
        : totalWeight(totalWeight), mstEdges(mstEdges)
    {
    }

    std::ostream &output(std::ostream &os) const override; // override output

private:
    int totalWeight;
    std::vector<std::pair<int, int>> mstEdges;
};

// definizione classe derivata per gestione diretta del problema di dikjstra
class DijkstraSolution : public ProblemSolution
{
public:
    DijkstraSolution(int distance) : distance(distance) {} // costruttore che definisce la distanza della soluzione

    std::ostream &output(std::ostream &os) const override; // override output
private:
    int distance;
};

#endif
