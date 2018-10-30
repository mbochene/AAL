/*
    Mateusz Bochenek
    AAL-9-LS rabuś
*/

#ifndef PROBLEM_GENERATOR_HPP_
#define PROBLEM_GENERATOR_HPP_

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

class problemGenerator{
    int numberOfNodes, trunkVolume, type, modulo, numberOfParts, nodesPerLevel, node;                                     //type to typ tworzonego grafu; numberOfParts to liczba powtarzających się elementów grafu; node to zmienna pomocnicza oznaczająca numer wierzchołka
    vector<list<int>> graph;
    vector<int> lootVolume;
    vector<int> lootValue;
    
    public:
    problemGenerator(int number, int volume, int t, int l)
    {
        numberOfNodes=number;
        trunkVolume=volume;
        type=t;
        graph.resize(numberOfNodes);
        lootVolume.resize(numberOfNodes);
        lootValue.resize(numberOfNodes);
        modulo=0;
        numberOfParts=0;
        node=0;
        nodesPerLevel=l;
    }
    ~problemGenerator(){};

    void generate()                                                                                                       //generowanie i rysowanie grafu sąsiedztwa                                          
    {
        if(type==1)                                                                                                       //"łańcuch" (dla nodesPerLevel==1 daje pojedyńczą ścieżkę, a dla nodesPerLevel==n-2 daje graf, w którym jest n-2 ścieżek o długości 3)
        {
            modulo=(numberOfNodes-1)%(nodesPerLevel+1);
            numberOfParts=(numberOfNodes-1)/(nodesPerLevel+1);

            for(int i=0;i<numberOfParts;i++)                                                                              //konstrukcja części grafu
            {
                for(int j=0;j<nodesPerLevel;j++)
                {
                    graph[node].push_back(node+j+1);
                    graph[node+j+1].push_back(node+nodesPerLevel+1);
                }
                node=node+nodesPerLevel+1;
            }

            for(int i=0;i<modulo;i++)                                                                                     //dopisanie reszty wierchołków do grafu (już nie według wzoru)
            {
                graph[node].push_back(node+1);
                node+=1;
            }
        } else if(type==2)
        {
            modulo=(numberOfNodes-2)%nodesPerLevel;
            numberOfParts=(numberOfNodes-2)/nodesPerLevel;
            int auxiliary=nodesPerLevel+1;
            node=(nodesPerLevel*numberOfParts)+1;
            for(int i=1;i<node-nodesPerLevel;i++)                                                                         //konstrukcja "środka" grafu
            {
                for(int j=0;j<nodesPerLevel;j++)
                {
                    graph[i].push_back(auxiliary+j);
                }
                if(i%nodesPerLevel==0)
                    auxiliary+=nodesPerLevel;
            }

            for(int i=0;i<nodesPerLevel;i++)                                                                             //konstrukcja góry i dołu
            {
                graph[0].push_back(1+i);
                graph[node-nodesPerLevel+i].push_back(node);
            }

            for(int i=node;i<numberOfNodes-1;i++)                                                                        //doczepianie pozostałych wierzchołków (jeśli takie istnieją)
            {
                graph[i].push_back(i+1);
            }
        }

        srand(time(NULL));                                                                                              //wypełnianie wektorów lootVolume i lootalue losowymi danymi
        for(int i=0;i<numberOfNodes;i++)
        {
            lootVolume[i]=(rand()%(trunkVolume-1)+1);                                                                   //losuj wartość z przedziału <1,trunkVolume>
            lootValue[i]=((rand()%199)+1);                                                                              //losuj wartość z przedziału <1,200>
        }
    }

    vector<int> getLootVolumeVector()
    {
        return lootVolume;
    }

    vector<int> getLootValueVector()
    {
        return lootValue;
    }

    vector<list<int>> getGraph()
    {
        return graph;
    }

    void showGeneratedProblem()
    {
        cout << "wierzcholek -----> sasiedzi" << endl;
        for(int i=0;i<numberOfNodes;i++)                                                                                //rysowanie grafu sąsiedztwa
        {
            cout << i << " -----> ";
            for(int j : graph[i])
                cout << j << " ";
            cout << endl;
        }
        cout << endl << "Objetosc i wartosc lukow w miastach (podane w tej kolejnosci): ";
        for(int i=0;i<numberOfNodes;i++)
            cout << "[" << lootVolume[i] << "," << lootValue[i] << "] ";
        cout << endl;
    }

    int getModulo()
    {
        return modulo;
    }

    int getNumberOfParts()
    {
        return numberOfParts;
    }

};

#endif