#include "aux.h"

Data ler_instancia(string file_name)
{
    
    ifstream file(file_name);
    if(file.fail())
    {
        std::cout << "Arquivo nao existente\n";
        exit(1);
    }
    int quantidade;
    int referencia;
    int maior_pag = -1;
    file >> quantidade; 
    vector<int> referencias;
    while(file >> referencia)
    {
        if(referencia > maior_pag)
        {
            maior_pag = referencia;
        }
        referencias.push_back(referencia);
    }

    // Data data;

    return {quantidade, referencias, maior_pag};
}

void print_ram(vector<int> RAM)
{
    std::cout << "RAM: ";
    for(int i = 0; i < RAM.size(); i++)
    {
        std::cout << RAM[i] << " ";
    }
    std::cout << std::endl;
}