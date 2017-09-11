#ifndef SOLUTION_HPP
#define SOLUTION_HPP


#include <vector>
#include <map>
#include <cstdlib>
#include <algorithm>
#include "Graph.hpp"
#include "Clique.hpp"
using namespace std;

namespace Melina {

    class Solution {

    private:
        Graph *graph;

        vector<Clique> cliquecover;
        int sizeCliqueCover;
        long evaluation;
        int smallestClique;

        int nToRemove[10] = {1, 1, 1, 1, 1, 1, 2, 2, 2, 3};
        long oldEvaluation;
        map<int, int> fromClique;
        map<int, int> toClique;


    public:
        Solution(Graph *);

        Clique getClique(int);

        int getSizeCliqueCover() const;

        int createRandomNeighbour();

        long getEvaluation() const;

        void setEvaluation();

        bool addToClique(int v, int c);

        void addChange(Clique, int);

        void acceptChanges();

        void reverseChanges();

    };

}

#endif //SOLUTION_HPP
