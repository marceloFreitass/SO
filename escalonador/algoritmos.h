#include <vector>
#include <iostream>
#include <limits>
#include <locale>
#include <iomanip>
#include "aux.h"
using namespace std;

//inicializando gant
vector<tuple<int,int,int>> inicia_gant(vector<tuple<int,int,int>>& processos);
//algoritmos de escalonamento
vector<tuple<int,int,int>> FCFS(vector<tuple<int,int,int>>& processos);
vector<tuple<int,int,int>> SJF(vector<tuple<int,int,int>> processos);
vector<tuple<int,int,int>> RR(vector<tuple<int,int,int>> processos);
//calculando estatisticas com base no gant
void calcula_tempos(vector<tuple<int,int,int>> gant, vector<tuple<int,int,int>> processos);