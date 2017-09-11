#ifndef CLIQUECOVER_VERTICE_HPP
#define CLIQUECOVER_VERTICE_HPP

#include <algorithm>
#include <vector>
using namespace std;

namespace Melina {


    class Vertex {

    private:
        int name;
        int degree;
        vector<int> neighbors;

    public:
        Vertex();

        Vertex(int name);

        int getName() const;

        void setName(int name);

        int getDegree() const;

        void addDegree();

        vector<int> getNeighbors() const;

        void addNeighbor(int n);

        bool isNeighbor(int v) const;

        bool operator<(const Vertex &rhs) const;

        bool operator>(const Vertex &rhs) const;

        bool operator<=(const Vertex &rhs) const;

        bool operator>=(const Vertex &rhs) const;

    };

}

#endif //CLIQUECOVER_VERTICE_HPP
