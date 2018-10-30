#ifndef ROBBERY_SCHEME_HPP_
#define ROBBERY_SCHEME_HPP_

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

using namespace std;

class robberyScheme
{
    int numberOfNodes, trunkVolume, maxLoot, routeLength, numberOfEscapeRoutes;
    vector<list<int>> graph;
    vector<list<int>> path;                                                                    //zmienna przechowująca najkrótsze ścieżki (wynik algorytmu Dijkstry)
    vector<int> finalRoute;
    vector<int> lootVolume;
    vector<int> lootValue;

    void findPaths()                                                                    //zmodyfikowany algorytm Dijkstry -> wierzchołek może mieć więcej poprzedników niż 1
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
                        if(cost[j]!=cost[minNode]+1)
                        {
                            cost[j]=cost[minNode]+1;
                        }
                        path[j].push_back(minNode);
                    }
                }
            }   
        }
        routeLength=cost[numberOfNodes-1]+1;                                             //zapisanie długości najkrótszej ścieżki (dodanie wierzchołka początkowego)
    }

    void getPaths(int currentLength, int node, vector<int> escapeRoute, list<int>::iterator it)
    {
        numberOfEscapeRoutes++;                                                         
        int currentNode=node;                                                           //zapisanie numeru sprawdzanego wierzchołka
        while(currentNode!=0)
        {
            if(*it!=path[currentNode].back())                                           //jesli kolejny sąsiad istnieje, to wywołaj funkcję dla sąsiada
            {
                getPaths(currentLength, currentNode, escapeRoute, ++it);
                it--;
            }
            escapeRoute[currentLength]=currentNode;                                     //dodanie obecnego wierzchołka do wektora przechowującego wierzchołki tej ścieżki
            currentNode=*it;
            currentLength++;                                                            
            it=path[*it].begin();                                                       //przeniesienie się na sąsiada
        }
        solveKnapsackProblem(escapeRoute);                                              //rozwiązanie problemu plecakowego dla danej ścieżki
    }

    void solveKnapsackProblem(const vector<int>& node)                                         
    {
        vector<vector<int>> matrix(trunkVolume+1, vector<int>(routeLength+1,0));        //stworzenie macierzy (trunkVolume+1)x(routeLength+1)
        for(int i=1;i<=routeLength;i++)
        {
            for(int j=0;j<=trunkVolume;j++)
            {
                if(lootVolume[node[i-1]]>j)                                             //jeśli przedmiot nie mieści się do plecaka (przesunięcie w lootVolume spowodowane jest faktem, że pierwszy element jest na indeksie 0)
                {
                    matrix[j][i]=matrix[j][i-1];                                        //to nie należy go wkładać
                }
                else
                {
                    matrix[j][i]=max(matrix[j][i-1], matrix[j-lootVolume[node[i-1]]][i-1]+lootValue[node[i-1]]);
                }
            }
        }
        if(matrix[trunkVolume][routeLength]>maxLoot)                                    //jeśli możliwy do uzyskania łup jest maksymalny, to przypisz wartości odpowiednim zmiennym
        {
            maxLoot=matrix[trunkVolume][routeLength];
            finalRoute=node;
        }
    }

    public:

    robberyScheme(){};

    robberyScheme(int n, int t, const vector<int>& lVol, const vector<int>& lVal, const vector<list<int>>& g)
    {
        numberOfNodes=n;
        trunkVolume=t;
        lootVolume=lVol;
        lootValue=lVal;
        graph=g;
        maxLoot=0;
        numberOfEscapeRoutes=0;
        path.resize(numberOfNodes);
    }

    ~robberyScheme(){};

    void solve()
    {
        findPaths();
        vector<int> i(routeLength);
        list<int>::iterator it=path[numberOfNodes-1].begin();
        getPaths(0, numberOfNodes-1, i, it);
    }

    int getEscapeRouteLength()
    {
        return routeLength;
    }

    int getNumberOfEscapeRoutes()
    {
        return numberOfEscapeRoutes;
    }

    vector<int> getEscapeRoute()
    {
        return finalRoute;
    }

    int getMaxLoot()
    {
        return maxLoot;
    }
};

#endif