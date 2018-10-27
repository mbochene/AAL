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
    int numberOfNodes, trunkVolume, type, modulo, numberOfParts;                                                           //type to typ tworzonego grafu; numberOfParts to liczba powtarzających się elementów grafu
    vector<list<int>> graph;
    vector<int> lootVolume;
    vector<int> lootValue;
    
    public:
    problemGenerator(int number, int volume, int t)
    {
        numberOfNodes=number;
        trunkVolume=volume;
        type=t;
        graph.resize(numberOfNodes);
        lootVolume.resize(numberOfNodes);
        lootValue.resize(numberOfNodes);
    }
    ~problemGenerator(){};

    void generate()                                                                                                      //enerowanie i rysowanie grafu sąsiedztwa                                          
    {
        int node=0;                                                                                                      //numer wierzchołka
        if(type==1)
        {
            modulo=(numberOfNodes-1)%3;
            numberOfParts=(numberOfNodes-1)/3;

            for(int i=0;i<numberOfParts;i++)                                                                            //konstrukcja części grafu
            {
                graph[node].push_back(node+1);
                graph[node].push_back(node+2);
                graph[node+1].push_back(node+3);
                graph[node+2].push_back(node+3);
                node+=3;
            }

            for(int i=0;i<modulo;i++)                                                                                   //dopisanie reszty wierchołków do grafu (już nie według wzoru)
            {
                graph[node].push_back(node+1);
                node+1;
            }
        }
        srand(time(NULL));
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