#ifndef ROBBERY_SCHEME_HPP_
#define ROBBERY_SCHEME_HPP_

#include <iostream>
#include <list>
#include <vector>

using namespace std;

class robberyScheme
{
    int numberOfNodes, trunkVolume, maxLoot, *lootVolume, *lootValue;
    list<int> *graph;
    list<int> *path;                                                                    //zmienna przechowująca najkrótsze ścieżki (wynik algorytmu Dijkstry)

    void returnPaths()                                                                  //zmodyfikowany algorytm Dijkstry -> wierzchołek może mieć więcej poprzedników niż 1
    {
        vector<int> cost(numberOfNodes, 2147483647);                                    //MAXINT jako początkowy minimalny koszt dla każdego wierzchołka
        cost[0]=0;                                                                      //wierzchołek startowy
        vector<bool> QS(numberOfNodes, false);
        for(int i=0;i<numberOfNodes;i++)
        {
            int minNode=numberOfNodes-1;                                                //numer wierzchołka ze zbioru Q o najtańszym koszcie dojścia (na początek można szukać od n-1, bo rabuś zawsze kończy na tym wierzchołku, czyli za każdym razem koszt dojścia jest największy)
            for(int j=0;j<numberOfNodes;j++)                                            //znajdowanie wierzchołka ze zbioru Q o najtańszym koszcie dojścia
            {
                if(!QS[j] && cost[j]<cost[minNode])
                {
                    minNode=j;
                }
            }

            QS[minNode]=true;                                                           //przeniesienie wierzchołka ze zbioru Q do zbioru S

            if(minNode==numberOfNodes-1)                                                //jeśli minNode to ostatni wierzchołek, to można zakończyć algorytm
                break;
            else
            {
                for(int j : graph[minNode])                                             //dodawanie poprzednika sąsiadom wierzchołka minNode i modyfikacja kosztów dojścia
                {
                    if(!QS[j] && cost[j]>=cost[minNode]+1)
                    {
                        cost[j]=cost[minNode]+1;
                        path[j].push_back(minNode);
                    }
                }
            }   
        }
    }

    public:
    robberyScheme(int n, int t, int *lVol, int *lVal, list<int> *g)
    {
        numberOfNodes=n;
        trunkVolume=t;
        lootVolume=lVol;
        lootValue=lVal;
        graph=g;
        maxLoot=0;
        path=new list<int>[n];
    }

    ~robberyScheme()
    {
        delete[] lootVolume;
        delete[] lootValue;
        delete[] graph;
        delete[] path;
    }

    void solve()
    {
        returnPaths();
    }

    int get()
    {
        return maxLoot;
    }
};

#endif