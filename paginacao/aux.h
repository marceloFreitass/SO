#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

typedef struct Data
{
    int qtd_frames;
    vector<int> referencias;
    int maior_pag;
}Data;


Data ler_instancia(string file_name);
void print_ram(vector<int> RAM);