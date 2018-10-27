#include <iostream>
#include <list>
#include <vector>
#include <string.h>
#include "robberyScheme.hpp"
#include "problemGenerator.hpp"

using namespace std;

int getValue(const char *x, int begin)                                                               //policz liczbę całkowitą z danego przedziału tablicy char (od danego znaku)                                                   
{
    int value=0;
    while(x[begin]!='\0')
    {
        value= value*10 + x[begin++] -'0';
    }
    return value;
}

int main(int argc, char* argv[])
{
    int numberOfNodes, numberOfEdges, trunkVolume, type, nodesPerLevel;
    int x, y;                                                                                        //zmienne pomocnicze

    if(strcmp(argv[1],"-m1")==0)
    {
        cin >> numberOfNodes;
        cin >> numberOfEdges;
        cin >> trunkVolume;

        vector<int> lootVolume(numberOfNodes);
        vector<int> lootValue(numberOfNodes);
        vector<list<int>> graph(numberOfNodes);

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
        cout << "Liczba znalezionych najkrotszych sciezek: " << scheme.getNumberOfEscapeRoutes() << endl;
        cout << "Dlugosc najkrotszej sciezki: " << scheme.getEscapeRouteLength() << endl;
        cout << "Maksymalna wartosc skradzionego towaru: " << scheme.getMaxLoot() << endl;
        cout << "Wiercholki nalezace do najkrotszej sciezki dajacej najwieksze mozliwe zyski: ";
        for(int i : scheme.getEscapeRoute())
            cout << i << " ";
    } else if(strcmp(argv[1],"-m2")==0)
    {
        numberOfNodes=getValue(argv[2],2);
        trunkVolume=getValue(argv[3],3);
        type=getValue(argv[4],5);
        nodesPerLevel=getValue(argv[5],2);
        
        problemGenerator generator(numberOfNodes, trunkVolume, type, nodesPerLevel);
        generator.generate();
        generator.showGeneratedProblem();
        robberyScheme scheme(numberOfNodes, trunkVolume, generator.getLootVolumeVector(), generator.getLootValueVector(), generator.getGraph());
        scheme.solve();

        cout << "Liczba znalezionych najkrotszych sciezek: " << scheme.getNumberOfEscapeRoutes() << endl;
        cout << "Dlugosc najkrotszej sciezki: " << scheme.getEscapeRouteLength() << endl;
        cout << "Maksymalna wartosc skradzionego towaru: " << scheme.getMaxLoot() << endl;
        cout << "Wiercholki nalezace do najkrotszej sciezki dajacej najwieksze mozliwe zyski: ";
        for(int i : scheme.getEscapeRoute())
            cout << i << " ";
    }

    return 0;
}