#include <vector>
#include <iostream>
#include <limits>
#include "aux.h"
using namespace std;

vector<tuple<int,int,int>> inicia_gant(vector<tuple<int,int,int>>& processos);
vector<tuple<int,int,int>> FCFS(vector<tuple<int,int,int>>& processos);
vector<tuple<int,int,int>> SJF(vector<tuple<int,int,int>> processos);
vector<tuple<int,int,int>> RR(vector<tuple<int,int,int>> processos);