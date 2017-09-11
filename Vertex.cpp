#include "Vertex.hpp"
using namespace Melina;

Vertex::Vertex() {
    name = -1;
    degree = 0;
    neighbors.clear();
}

Vertex::Vertex(int name) : name(name) {
    degree = 0;
    neighbors.clear();
}

int Vertex::getName() const {
    return name;
}

void Vertex::setName(int name) {
    Vertex::name = name;
}

int Vertex::getDegree() const {
    return degree;
}

void Vertex::addDegree() {
    degree++;
}

vector<int> Vertex::getNeighbors() const {
    return neighbors;
}

bool Vertex::isNeighbor(int v) const {
    for(int i=0; i<degree; i++) {
        if(v == neighbors[i]) {
            return true;
        }
        else if(v < neighbors[i]) {
            return false;
        }
    }
    return false;
}

void Vertex::addNeighbor(int n) {
    neighbors.push_back(n);
    sort(neighbors.begin(), neighbors.end());
}

bool Vertex::operator<(const Vertex &rhs) const {
    return name < rhs.name;
}

bool Vertex::operator>(const Vertex &rhs) const {
    return rhs < *this;
}

bool Vertex::operator<=(const Vertex &rhs) const {
    return !(rhs < *this);
}

bool Vertex::operator>=(const Vertex &rhs) const {
    return !(*this < rhs);
}




