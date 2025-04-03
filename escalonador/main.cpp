#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "algoritmos.h"
#include "aux.h"
using namespace std;


vector<tuple<int,int,int>> ler_instancia(string file_name)
{
    
    ifstream file(file_name);
    if(file.fail())
    {
        std::cout << "Arquivo nao existente\n";
        exit(1);
    }
    vector<tuple<int,int,int>> processos;
    int chegada, pico;
    int process_count = 0;
    while(file >> chegada >> pico)
    {
        processos.push_back({process_count++, chegada, pico});
    }

    return processos;
}

struct sort_chegada {
    bool operator()(const std::tuple<int,int,int> &left, const std::tuple<int,int,int> &right) {
        return get<1>(left) < get<1>(right);
    }
};
struct sort_processamento {
    bool operator()(const std::tuple<int,int,int> &left, const std::tuple<int,int,int> &right) {
        return get<2>(left) < get<2>(right);
    }
};


int main(int argc, char** argv)
{

    vector<tuple<int,int,int>> processos;
    vector<tuple<int,int,int>> gant_retorno;

    if(argc != 2)
    {
        cout << "INCORRETO!" << endl;
        cout << "USO: ./programa instancia.txt" << endl;
        return -1;
    }

    //FCFS
    processos = ler_instancia(argv[1]);
    //ordena pelo tempo de chegada
    sort(processos.begin(), processos.end(), sort_chegada());

    //gerando o gant do FCFS
    gant_retorno = FCFS(processos);
    // print_gant(gant_retorno);
    cout << "FCFS: ";
    //calculando e printando tempos
    calcula_tempos(gant_retorno, ler_instancia(argv[1]));


    //SJF
    processos = ler_instancia(argv[1]);
    //ordena pelo tempo de pico
    sort(processos.begin(), processos.end(), sort_processamento());
    //gerando o gant do SJF
    gant_retorno = SJF(processos);
    // print_gant(gant_retorno);
    cout << "SJF: ";
    //calculando e printando tempos
    calcula_tempos(gant_retorno, ler_instancia(argv[1]));

    //RR
    processos = ler_instancia(argv[1]);
    sort(processos.begin(), processos.end(), sort_chegada());
    //gerando o gant do RR
    gant_retorno = RR(processos);
    // print_gant(gant_retorno);
    cout << "RR: ";
    //calculando e printando tempos
    calcula_tempos(gant_retorno, ler_instancia(argv[1]));


    return 0;
}


