#include <iostream>
#include <algorithm>
#include "Clique.hpp"
using namespace Melina;

Clique::Clique(Graph *G) {
    graph = G;
    size = 0;
}

Clique::Clique(int v, Graph *G) {
    graph = G;
    size = 1;
    clique.insert(v);
}

int Clique::getSize() const {
    return size;
}

set<int> Clique::getClique() {
    return clique;
}

bool Clique::addToClique(int v) {

    auto it = clique.find(v);

    //ja esta no clique
    if(it != clique.end()) {
        return false;
    }

    for(it=clique.begin(); it!=clique.end(); ++it) {
        if(!graph->getNode(*it).isNeighbor(v)) {
            return false;
        }
    }

    clique.insert(v);
    size++;
    return true;

}

bool Clique::checkClique(int v) {

    auto it = clique.find(v);

    //ja esta no clique
    if(it != clique.end()) {
        return true;
    }

    return false;
}

int Clique::removeFromClique() {
    auto it = clique.begin();
    int v = *it;
    clique.erase(v);
    size--;
    return v;
}

int Clique::removeFromClique(int n) {

    for(auto it=clique.begin(); it!=clique.end(); ++it) {
        if(graph->getNode(*it).getName() == n) {
            clique.erase(*it);
            size--;
            return 0;
        }
    }

    return -1;
}



