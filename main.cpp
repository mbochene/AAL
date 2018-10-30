#include <iostream>
#include <list>
#include <vector>
#include <string.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <math.h>
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
    }   else if(strcmp(argv[1],"-m3")==0)
    {
        numberOfNodes=getValue(argv[2],2);
        trunkVolume=getValue(argv[3],3);
        type=getValue(argv[4],5);
        nodesPerLevel=getValue(argv[5],2);
        int k=getValue(argv[6],2);
        int step=getValue(argv[7],5);
        int r=getValue(argv[8],2);
        vector<int> table1(k);
        vector<double> table2(k);
        vector<double> T(k);
        double q;
        double mediant;
        double medianT;

        cout << "|" << setw(10) << "n" << "|" << setw(20) << "t(n)" << "|" << setw(20) << "q" << "|" << endl << "------------------------------------------------------" << endl;
        for(int i=0;i<k;i++)
        {
            for(int j=0;j<r;j++)
            {
                problemGenerator generator(numberOfNodes, trunkVolume, type, nodesPerLevel);
                generator.generate();
                robberyScheme scheme(numberOfNodes, trunkVolume, generator.getLootVolumeVector(), generator.getLootValueVector(), generator.getGraph());
                chrono::high_resolution_clock::time_point begin=chrono::high_resolution_clock::now();
                scheme.solve();
                chrono::high_resolution_clock::time_point end=chrono::high_resolution_clock::now();
                table2[i]+=chrono::duration_cast<std::chrono::milliseconds>(end-begin).count();
                T[i]=(numberOfNodes*numberOfNodes)+(scheme.getNumberOfEscapeRoutes()*(trunkVolume*scheme.getEscapeRouteLength()));
            }
            table1[i]=numberOfNodes;
            numberOfNodes+=step;
        }
        
        if(k&1)
        {
            mediant=table2[k/2];
            medianT=T[k/2];
        }
        else
        {
            mediant=(table2[k/2]+table2[(k/2)-1])/2;
            medianT=(T[k/2]+T[(k/2)-1])/2;
        }

        for(int i=0;i<k;i++)                                                                                                                                                //rysowanie tabelki
        {
            q=(table2[i]*medianT)/(T[i]*mediant);
            cout << "|" << setw(10) << table1[i] << "|" << setw(20) << table2[i] << "|" << setw(20) << q << "|" << endl << "------------------------------------------------------" << endl;
        }
    }

    return 0;
}