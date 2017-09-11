#include "Graph.hpp"
using namespace Melina;


Graph* Graph::g = NULL;

Graph::Graph() {
    nVertex = 0;
    nEdges = 0;
    node.clear();
}

Graph::Graph(int nVertex, int nEdges) : nVertex(nVertex), nEdges(nEdges) {}

int Graph::getNVertex() const {
    return nVertex;
}

void Graph::setNVertex(int n) {
    nVertex = n;
}

int Graph::getNEdges() {
    return nEdges;
}

void Graph::setNEdges(int n) {
    nEdges = n;
}

const Vertex &Graph::getNode(int n) {
    return node[n];
}

void Graph::addNode(Vertex n) {
    node.push_back(n);
}
