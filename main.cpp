#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <string>
#include "Clique.hpp"
#include "Graph.hpp"
#include "Solution.hpp"
using namespace std;
using namespace Melina;



//#define LAHC

#define MAX_ITERATIONS 50000
#define MAX_TIME 600.0

#ifdef LAHC // Late Acceptance Hill Climbing
    #define TAM_LISTA 20
#else // Simulated Annealing
    #define TEMP_INICIAL 10.0
    #define ALFA 0.9999                 // cooling rate
    #define E 0.00001                  // threshold
    #define REHEATING 1.0
    #define RND01 ( (double)rand() / ( ((double)RAND_MAX)+1.0) )
#endif



void readGraph(char *fileName, Graph *G);
void printSolution(char *, string, Graph, Solution, double, int);


int main(int argc, char *argv[]) {

    srand((unsigned int) time(NULL));
    clock_t begin, end;
    int i=1, delta;
    double time_s = 0.0;
    double oldTime = 0.0;
    string solFile;
    Graph G;


    if(argc == 1){
        cout << "Arquivo de entrada nao informado." << endl;
        return 0;
    }
    else if (argc == 2) {
        solFile = "CliqueCover_" + to_string(MAX_ITERATIONS) + ".txt";
    }
    else if (argc == 3) {
        solFile = argv[2];
    }


    readGraph(argv[1], &G);
    Graph::g = &G;


    Solution solution(&G);
    ofstream saida(solFile,fstream::out);
    //cout << "\nMelhor solucao (iteracao " << 0 << "): " << solution.getEvaluation() << " - Cliques: " << solution.getSizeCliqueCover() << endl;
    #ifdef LAHC // Late Acceptance Hill Climbing
        saida << "LATE ACCEPTANCE HILL CLIMBING - SOLUCAO ENCONTRADA PARA O PROBLEMA " << argv[1] << endl
              << " \nTamanho da Lista: " << TAM_LISTA
              << " \nMaximo iteracoes: " << MAX_ITERATIONS << "\nMaximo tempo: " << MAX_TIME << "s (" << MAX_TIME/60.0 << "min)" << endl;
    #else // Simulated Annealing
        saida << "SIMULATED ANNEALING - SOLUCAO ENCONTRADA PARA O PROBLEMA " << argv[1] << endl
                  << " \nTemperatura inicial: " << TEMP_INICIAL << " \nAlfa: " << ALFA << " \nThreshold: " << E << " \nReheating: " << REHEATING
                  << " \nMaximo iteracoes: " << MAX_ITERATIONS << "\nMaximo tempo: " << MAX_TIME << "s (" << MAX_TIME/60.0 << "min)" << endl;
    #endif
    saida << "\n" << 0 << " " << solution.getEvaluation() << " " << solution.getSizeCliqueCover();



    #ifdef LAHC // Late Acceptance Hill Climbing
        int L[TAM_LISTA];
        for(int i=0; i<TAM_LISTA; i++) {
            L[i] = solution.getEvaluation();
        }
    #else // Simulated Annealing
        double temperature = TEMP_INICIAL;
    #endif



    begin = clock();


    while ((i <= MAX_ITERATIONS) && (time_s < MAX_TIME) && (solution.getSizeCliqueCover()>1)) {

        delta = solution.createRandomNeighbour();

        #ifdef LAHC // Late Acceptance Hill Climbing
            if (solution.getEvaluation() >= L[i%TAM_LISTA] || delta >= 0) {
                solution.acceptChanges();
            }
            else {
                solution.reverseChanges();
            }

            if(solution.getEvaluation() >= L[i%TAM_LISTA]) {
                L[i%TAM_LISTA] = solution.getEvaluation();
            }
        #else // Simulated Annealing

            // debug do RND01
//            if((time_s-oldTime > 1.0)) {
//                cout << endl << M_E << " " << RND01 << " " << delta << " " << temperature << " " << (pow(M_E, (delta / (temperature)))) << endl << endl;
//                oldTime = time_s;
//            }

            if (delta >= 0) {
                solution.acceptChanges();
            }
            else if (RND01 < (pow(M_E, ((double)delta) / temperature))) {
                solution.acceptChanges();
            }
            else {
                solution.reverseChanges();
            }
        #endif


        end = clock();
        time_s = double(end - begin) / CLOCKS_PER_SEC;


//        if((time_s-oldTime > 0.5)) {
//            cout << "\nMelhor solucao (iteracao " << i << "): " << solution.getEvaluation() << " - Cliques: " << solution.getSizeCliqueCover() << endl;
//             oldTime = time_s;
//        }


//        if(i%100 == 0) {
//            cout << "\nMelhor solucao (iteracao " << i << "): " << solution.getEvaluation() << " - Cliques: " << solution.getSizeCliqueCover() << endl;
//            saida << "\n" << i << " " << solution.getEvaluation() << " " << solution.getSizeCliqueCover();
//        }





        #ifdef LAHC // Late Acceptance Hill Climbing

        #else // Simulated Annealing

                if(temperature < E) {
                    temperature = REHEATING;
                    cout << "\nMelhor solucao (iteracao " << i << "): " << solution.getEvaluation() << " - Cliques: " << solution.getSizeCliqueCover() << endl;
                    saida << "\n" << i << " " << solution.getEvaluation() << " " << solution.getSizeCliqueCover();
                }
                else {
                    temperature = ALFA * temperature;
                }
        #endif

        i++;

    }

    solution.setEvaluation();

    saida.close();

    //printSolution(argv[1], solFile, G, solution, time_s, i);

    return 0;
}

void readGraph(char *fileName, Graph *G) {
    int x, y;
    char t;

    vector<Vertex> nodes;

    ifstream file(fileName);

    if(!file.is_open()) {
        cout << "Erro ao abrir o arquivo de leitura." << endl;
        return;
    }

    file >> t >> t >> t >> t >> t;
    file >> x >> y;

    G->setNVertex(x);
    G->setNEdges(y);

    //inicializa
    for(int i=0; i<G->getNVertex(); i++) {
        Vertex v(i);
        nodes.push_back(v);
    }

    //leitura das arestas
    for(int i=0; i<G->getNEdges(); i++) {

        file >> t >> x >> y;

        nodes[x-1].addDegree();
        nodes[x-1].addNeighbor(y-1);

        nodes[y-1].addDegree();
        nodes[y-1].addNeighbor(x-1);

    }

    //
    for(int i=0; i<G->getNVertex(); i++) {
        G->addNode(nodes[i]);
    }

    file.close();
}

void printSolution(char entrada[], string saida, Graph g, Solution sol, double time, int i) {
    ofstream file(saida,fstream::out);

    if(!file) {
        cout << "Erro ao abrir o arquivo de saida" << endl;
        return;
    }


        file << "\n\n\n\nAvaliacao final: " << sol.getEvaluation() << " (Cliques: " << sol.getSizeCliqueCover() << ")"
             << " \nTotal iteracoes: " << i << "\nTotal tempo: " << time << "s (" << time/60.0 << "min)" << endl;


    //cout << endl << endl;
    //cout << "Avaliacao: " << sol.getEvaluation() << " - Cliques: " << sol.getSizeCliqueCover() << " (" << time << "s)" << endl;
    file << "Avaliacao: " << sol.getEvaluation() << " - Cliques: " << sol.getSizeCliqueCover() << " (" << time << "s)" << endl << endl;

    for(int i=1; i<=sol.getSizeCliqueCover(); i++) {
        file << "Clique " << i << "(" << sol.getClique(i-1).getSize() << "): ";
        cout << "Clique " << i << "(" << sol.getClique(i-1).getSize() << "): ";

        for(int j=0; j<sol.getClique(i-1).getSize(); j++) {
        //    file << sol.getClique(i-1).getClique(j)+1 << " ";
        //    cout << sol.getClique(i-1).getClique(j)+1 << " ";
        }
        file << "\n\n";
        cout << endl << endl;
    }

    file.close();
}


