#include <iostream>
#include <list>
#include <string.h>
#include "robberyScheme.hpp"

using namespace std;

int main(int argc, char* argv[])
{
    int numberOfNodes, numberOfEdges, trunkVolume, *lootVolume, *lootValue;
    int x, y;                                                                                        //auxiliary variables
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
            cin >> x >> y;                                                                         //read edges from user input
            graph[x].push_back(y);
        }

        for(int i=0;i<numberOfNodes;i++)
        {
            cin >> x >> y;                                                                        //read volume and value of the loot available on the node
            lootVolume[i]=x;
            lootValue[i]=y;
        }


        robberyScheme scheme(numberOfNodes, trunkVolume, lootVolume, lootValue, graph);
    }
    return 0;
}