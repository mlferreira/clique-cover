#ifndef CLIQUECOVER_GRAFO_HPP
#define CLIQUECOVER_GRAFO_HPP


#include <vector>
#include "Vertex.hpp"
using namespace std;

namespace Melina {
    class Graph {

    private:
        int nVertex;
        int nEdges;
        vector<Vertex> node;

    public:
        Graph();

        Graph(int nVertex, int nEdges);

        int getNVertex() const;

        void setNVertex(int nVertex);

        int getNEdges();

        void setNEdges(int n);

        const Vertex &getNode(int n);

        void addNode(Vertex n);


        static Graph *g;

    };

}


#endif //CLIQUECOVER_GRAFO_HPP
