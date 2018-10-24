#include <iostream>
#include <list>
#include <string.h>
#include "robberyScheme.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    int numberOfNodes, numberOfEdges, trunkVolume, *lootVolume, *lootValue;
    int x, y;                                                                                        //zmienne pomocnicze
    list<int> *graph;

    if(strcmp(argv[1],"-m1")==0)
    {
        cin >> numberOfNodes;
        cin >> numberOfEdges;
        cin >> trunkVolume;

        lootVolume=new int[numberOfNodes];
        lootValue=new int[numberOfNodes];
        graph=new list<int>[numberOfNodes];

        for(int i=0;i<numberOfEdges;i++)
        {
            cin >> x >> y;                                                                         //wczytywanie krawędzi
            graph[x].push_back(y);
        }

        for(int i=0;i<numberOfNodes;i++)
        {
            cin >> x >> y;                                                                        //wczytywanie wielkości i wartości łupów na poszczególnych węzłach
            lootVolume[i]=x;
            lootValue[i]=y;
        }

        robberyScheme scheme(numberOfNodes, trunkVolume, lootVolume, lootValue, graph);
        scheme.solve();
        cout << scheme.getEscapeRouteLength() << endl;
    }

    return 0;
}