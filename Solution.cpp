#include <vector>
#include <iostream>
#include <algorithm>
#include "Solution.hpp"
using namespace std;
using namespace Melina;


Solution::Solution(Graph *G) {
    graph = G;
    evaluation = 0;
    sizeCliqueCover = 0;
    smallestClique = 1;

    for(int i=0; i<graph->getNVertex(); i++){
        cliquecover.push_back(Clique(i, G));
        sizeCliqueCover++;
    }
}

Clique Solution::getClique(int n) {
    if(n >= sizeCliqueCover){
        cout << "Erro! Solution.cpp getClique() : n>size (n = " << n << ", size = " << sizeCliqueCover << ")" << endl;
    }
    return cliquecover[n];
}

int Solution::getSizeCliqueCover() const {
    return sizeCliqueCover;
}

int Solution::createRandomNeighbour() {

    oldEvaluation = evaluation;

    random_shuffle(cliquecover.begin(), cliquecover.end());

    int cliquesToRemove = nToRemove[rand()%10];
    int i = 1;

    while(i <= cliquesToRemove) {
        int temp = rand()%sizeCliqueCover;
        addChange(cliquecover[temp], i);
        cliquecover.erase(cliquecover.begin()+temp);
        sizeCliqueCover--;
        i++;
    }

    for(auto it = fromClique.begin(); it != fromClique.end(); ++it) {
        i = 0;

        while(i<sizeCliqueCover && !addToClique(it->first, i)) {
            i++;
        }

        // nao achou clique pra colocar v
        if (i>=sizeCliqueCover-1 && !cliquecover[sizeCliqueCover-1].checkClique(it->first)) {
            cliquecover.push_back(Clique(it->first, graph));
            toClique[it->first] = sizeCliqueCover;
            sizeCliqueCover++;
        }
    }

    setEvaluation();
    return evaluation - oldEvaluation;
}

bool Solution::addToClique(int v, int c) {
    if(cliquecover[c].addToClique(v)) {
        toClique[v] = c;
        return true;
    }
    else {
        return false;
    }
}

void Solution::addChange(Clique clique, int i) {
    for (int n : clique.getClique()) {
        fromClique.insert(pair<int,int>(n,i));
    }
}

long Solution::getEvaluation() const {
    return evaluation;
}

/* calcula a avaliacao da solucao, do zero */
void Solution::setEvaluation() {
    evaluation = 0;
    smallestClique = cliquecover[0].getSize();

    for(int i=1; i<sizeCliqueCover; i++) {
       if(cliquecover[i].getSize() < smallestClique) {
           smallestClique = cliquecover[i].getSize();
       }
    }

    evaluation += (((graph->getNVertex() - sizeCliqueCover)*10000)+smallestClique);

}

void Solution::acceptChanges() {
    fromClique.clear();
    toClique.clear();
}

void Solution::reverseChanges() {
    vector<Clique> temp(3, Clique(graph));

    for(auto it = toClique.begin(); it != toClique.end(); ++it) {
        cliquecover[toClique[it->first]].removeFromClique(it->first);
        temp[fromClique[it->first]-1].addToClique(it->first);
    }

    cliquecover.insert(cliquecover.end(), temp.begin(), temp.end());
    sizeCliqueCover += 3;

    for(auto it=cliquecover.begin(); it!=cliquecover.end(); ++it) {
        if (it->getSize() == 0) {
            cliquecover.erase(it);
            sizeCliqueCover--;
            it--;
        }
    }

    evaluation = oldEvaluation;
    fromClique.clear();
    toClique.clear();
}










