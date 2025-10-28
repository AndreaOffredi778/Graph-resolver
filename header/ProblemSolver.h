#ifndef PROBLEMSOLVER_H
#define PROBLEMSOLVER_H
#include<iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm> 
#include "ProblemSolution.h"
#include "Graph.h"



class ProblemSolver{ //classe per definire la funzione membro solve

    public:
    virtual ~ProblemSolver()=default;
    virtual ProblemSolution * solve(const Graph &) = 0; //funzione virtuale pure che verrà ridefinita dalle classi astratte
     
 
};

class KruskalMSTSolver: public ProblemSolver{ //definisce soluzione per problema derivata di problemsolver
public:
    KruskalMSTSolver()=default; //costruttore default
    ProblemSolution * solve(const Graph& graph) override;
};


class DijkstraSolver: public ProblemSolver{ //definisce soluzione per problema derivata di problemsolver
public:

    DijkstraSolver(int src, int dest) : src(src), dest(dest) {} //costruttore che inizializza sorgente e destinazione

     ProblemSolution * solve(const Graph& graph) override;
     

private:
    int src, dest; //attributi per definire nodi della soluzione
 
};
#endif