#ifndef MENU_H
#define MENU_H

#include <string>
#include "Graph.h"
#include "ProblemSolution.h"
#include "ProblemSolver.h"

class Menu
{
public:
    // funzione membro
    void start();

private:
    // attributi classe menu
    Graph graph;                         // grafo
    std::string problemType;             // tipo di problema che verrà chiesto in input
    ProblemSolver *solver = nullptr;     // serve per iterare la soluzione
    ProblemSolution *solution = nullptr; // serve per immagazinare la soluzione
    std::string filename;                // nome file

    // funzioni membro private della classe menu
    void displayMenu();

    void handleChoice(int choice);

    void selectProblem();

    void exportProblem();

    inline void setFileName(std::string f) { filename = "instances/" + f + ".txt"; } // il filename viene formattato tramite l' aggiunta della cartella in
    // cui i file sono memorizzati e l' estensione txt, cosi in input bisogna solo inserire l' effettivo nome del file
};

#endif
