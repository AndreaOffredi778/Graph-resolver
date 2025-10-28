// classe menu gestisce l' interazione con l' utente e ne gestisce le sue scelte

#include <iostream>
#include <fstream>
#include <sstream>
#include "header/Menu.h"
#include "header/ProblemSolution.h"
#include "header/ProblemSolver.h"

void Menu::start()
{ // funzione che permette di eseguire il menu gestendo la parte di selzione dell' operazione voluta dall' utente
    std::cout << "start of the program\n";
    int choice;

    
    do
    { // appena l' utente inserisce 5 il programma interrompe esecuzione
    //controllo su input evitando errori in caso di inserimento di lettere
     if (std::cin.fail()) {
            std::cin.clear(); // Ripristina lo stato di std::cin
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Pulisce il buffer di input
            std::cerr << "Invalid input.\n";
            continue; // Ripete il ciclo per chiedere di nuovo l'input
        }
        displayMenu();
        std::cin >> choice;
        handleChoice(choice);
    } while (choice != 5 && (choice>=1||choice<5));
}

void Menu::displayMenu()
{ // stampa formattata per mostrare all' utente le possibili opzioni dell' applicazione
    std::cout << "\nMenu:\n";
    std::cout << "1. Import a graph\n";
    std::cout << "2. Select the problem to resolve\n";
    std::cout << "3. Print the problem solution\n";
    std::cout << "4. Import the solution to file\n";
    std::cout << "5. Exit\n";
    std::cout << "Select an option: ";
    std::cout.flush();
}

void Menu::handleChoice(int choice)
{ // gestione tramite switch-case della scelta dell' utente
    std::string dir = "instances/";

    switch (choice)
    {
    case 1: // inserimento nome grafo
        std::cout << "\nInsert graph name: ";
        std::cin >> filename;
        setFileName(filename);
        if (graph.importGraph(filename))
        {
            std::cout << "\nSuccessfull import of the graph!!\n";        // stampa di successo dell' importazione
            std::cout << "\nwant to see the arches of the graph? y/n\n"; // chiede se vuola la stampa del grafo
            std::string stampgraph;
            std::cin >> stampgraph;
            if (stampgraph == "y")
            {
                graph.printgraph();
            }
            if (solution != nullptr)
            { // questo serve per evitare di stampare la soluzione di un grafo precedentemente importato.
              // dunque ogni volta che viene importato un nuovo grafo, se presente la soluzione viene eliminata
                delete solution;
                solution = nullptr;
            }
        }
        else
        {
            std::cerr << "\nError on importing file.\n"; // nel caso l' importazione non va a buon fine
        }
        break;
    case 2: // gestione per selezionare il problema
        if (!graph.isEmpty())
        {
            selectProblem();
        }
        else
            std::cout << "\nNeed to import a graph.\n"; // se vuoto chiede di importare un grafo prima
        break;
    case 3:
        if (!graph.isEmpty() && solution != nullptr)
        { // stampa della soluzione del problema del grafo
            solution->output(std::cout);
        }
        else
        {
            std::cout << "\nNeed to import a problem.\n"; // se vuoto chiede di selezionare un problema prima
        }

        break;
    case 4:
        exportProblem(); // esportazione problema corrente nel file
        break;
    case 5:
        std::cout << "\nExit from the program, bye!!\n"; // uscita programma
        break;
    default:
        std::cout << "\nNot a valid option, retry.\n";
    }
}

void Menu::selectProblem()
{ // funzione che gestisce la selezione del problema
    std::cout << "\nSelect the problem to resolve:\n";
    std::cout << "1. Minimum spanning tree problem (Kruskal)\n";
    std::cout << "2. Single-pair shortest path problem (Dijkstra)\n";
    std::cout << "Select an option: ";
    std::cout.flush();
    int problemChoice;

    std::cin >> problemChoice;

    switch (problemChoice)
    { // gestione scelta tramite switch-case
    case 1:
        problemType = "Kruskal";
        solver = new KruskalMSTSolver(); // viene salvata la soluzione del problema di kruskal
        break;
    case 2:
        problemType = "Dijkstra";
        int src, dest; // essendo che dijkstra chiede la coppia di nodi sorgente, destinazione vengono chiesti in output
        std::cout << "\nSelect a source node: ";
        std::cin >> src;
        std::cout << "\nSelect a destination node: ";
        std::cin >> dest;
        solver = new DijkstraSolver(src, dest); // viene salvata la soluzione del problema di dijkstra
        break;
    default:
        std::cout << "\nOption not valid, retry.\n";
        return;
    }
    std::cout << "\nProblem selected: " << problemType << "\n";
    solution = solver->solve(graph); // risoluzione grafo usando la funzione mebro solve della classe problemsolver
}

void Menu::exportProblem()
{ // esportare problema selezionato su file
    if (graph.isEmpty())
    {
        std::cout << "\nNeed to import a graph.\n"; // se non c'è il grafo viene richiesto
        return;
    }

    if (problemType.empty())
    {
        std::cout << "\nNeed to import a problem.\n"; // se non c'è il problema viene richiesto
        return;
    }

    std::string nametxt; // serve per chiedere il nome del file su cui esportare la soluzione

    std::cout << "\nInsert the name of the file for exporting the solution: \n";
    std::cin >> nametxt;

    nametxt = "instances/" + nametxt + ".txt";

    std::ofstream file(nametxt, std::ios_base::app); // scrittura su file in modalità append usando il metodo app della classe ios_base

    // formattazione dell' output su file
    file << "Problem: " << problemType << "\n";
    file << "Graph: " << filename << "\n";

    if (file.is_open())
    {
        solution->output(file);
        file.close();
    }
    else
    {
        std::cerr << "\nUnable to open file: " << nametxt << std::endl;
    }
    file.close();
    std::cout << "\nProblem successfull loaded into the file.\n";
}
