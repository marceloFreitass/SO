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
    int maior_pag; // usado para criar os vetores
}Data;

// leitor de instância
Data ler_instancia(string file_name);
// printando estado da ram
void print_ram(vector<int> RAM);