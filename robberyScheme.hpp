#ifndef ROBBERY_SCHEME_HPP_
#define ROBBERY_SCHEME_HPP_

#include <list>

using namespace std;

class robberyScheme
{
    int numberOfNodes, trunkVolume, maxLoot, *lootVolume, *lootValue;
    list<int> *graph;
    list<int> *path;

    public:
    robberyScheme(int n, int t, int *lVol, int *lVal, list<int> *g)
    {
        numberOfNodes=n;
        trunkVolume=t;
        lootVolume=lVol;
        lootValue=lVal;
        graph=g;
        maxLoot=0;
    }
    ~robberyScheme()
    {
        delete[] lootVolume;
        delete[] lootValue;
        delete[] graph;
        delete[] path;
    }
};

#endif