#include <vector>
#include <iostream>

using namespace std;

//diagrama de gant
void print_gant(const vector<tuple<int,int,int>>& gant);
//printando processo com seu id e pico
void print_processos(const vector<tuple<int,int,int>>& processos);