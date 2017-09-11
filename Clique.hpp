#ifndef CLIQUECOVER_CLIQUE_HPP
#define CLIQUECOVER_CLIQUE_HPP


#include <algorithm>
#include <vector>
#include <set>
#include "Vertex.hpp"
#include "Graph.hpp"

using namespace std;

namespace Melina {

    class Clique {

    private:
        Graph *graph;

        int size;
        set<int> clique;

    public:
        Clique(Graph *G);

        Clique(int v, Graph *G);

        int getSize() const;

        set<int> getClique();

        bool addToClique(int v);

        bool checkClique(int v);

        int removeFromClique();

        int removeFromClique(int n);


        //int findM(vector<int> v);

    };

}


#endif //CLIQUECOVER_CLIQUE_HPP
