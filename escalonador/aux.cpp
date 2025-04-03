#include "aux.h"

void print_gant(const vector<tuple<int,int,int>>& gant)
{
    int i;
    for(i = 0; i < gant.size() - 1; i++)
    {
        std::cout << get<0>(gant[i]) << ":" << "(" << 
        get<1>(gant[i]) << "," << get<2>(gant[i]) << ")" 
        << " -> ";
    }
    std::cout << get<0>(gant[i]) << ":" << "(" << 
        get<1>(gant[i]) << "," << get<2>(gant[i]) << ")" << endl; 
}

void print_processos(const vector<tuple<int,int,int>>& processos)
{
    for(int i = 0; i < processos.size(); i++)
    {
        cout << "ID: " << get<0>(processos[i]) << " (" << 
        get<1>(processos[i]) << "," << get<2>(processos[i]) << ")" << endl;
    }
}