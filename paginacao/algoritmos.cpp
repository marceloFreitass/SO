#include "algoritmos.h"

int FIFO(Data& data)
{
    vector<bool> esta_na_RAM(data.maior_pag, false);
    queue<int> RAM;
    // vector<int> RAM(data.qtd_frames);
    int qtd_referencias = data.referencias.size();
    int falta_de_pag = 0;
    for(int i = 0; i < qtd_referencias; i++)
    {
        int pag = data.referencias[i];
        if(!esta_na_RAM[pag])
        {
            if(RAM.size() == data.qtd_frames)
            {
                int sai = RAM.front();
                RAM.pop();
                esta_na_RAM[sai] = false;
            }
            falta_de_pag++;
            esta_na_RAM[pag] = true;
            RAM.push(pag);
        }
    }
    

    return falta_de_pag;

}

int LRU(Data& data)
{
    vector<bool> esta_na_RAM(data.maior_pag, false);
    vector<int> RAM;
    // vector<int> posicao_RAM(data.maior_pag, -1);

    int qtd_referencias = data.referencias.size();
    int falta_de_pag = 0;

    for(int i = 0; i < qtd_referencias; i++)
    {
        int pag = data.referencias[i];

        if(!esta_na_RAM[pag])
        {

            if(RAM.size() == data.qtd_frames)
            {
                int sai = RAM[0];
                esta_na_RAM[sai] = false;
                RAM.erase(RAM.begin());
            }
            falta_de_pag++;
        }
        auto index_pag = find(RAM.begin(), RAM.end(), pag);

        if(index_pag != RAM.end())
        {
            RAM.erase(index_pag);     
        }
        esta_na_RAM[pag] = true;
        RAM.push_back(pag);
    }

    return falta_de_pag;
}

int OTM(Data& data)
{
    vector<bool> esta_na_RAM(data.maior_pag, false);
    vector<int> RAM;
    vector<int> copia_RAM;
    int qtd_referencias = data.referencias.size();
    int falta_de_pag = 0;
    for(int i = 0; i < qtd_referencias; i++)
    {
        int pag = data.referencias[i];
        // cout << "PAG: " << pag << endl;
        if(!esta_na_RAM[pag])
        {
            if(RAM.size() == data.qtd_frames)
            {
                copia_RAM = RAM;
                for(int j = i + 1; j < qtd_referencias; j++)
                {

                    int pag_frente = data.referencias[j];
                    // cout << "pag frente " << pag_frente << endl;
                    if(esta_na_RAM[pag_frente])
                    {
                        auto encontrado = find(copia_RAM.begin(), copia_RAM.end(), pag_frente);
                        if (*encontrado != pag_frente)
                            continue;
                        // std::cout << "ENCONTROU: " << *encontrado << std::endl;
                        copia_RAM.erase(encontrado);
                    }
                    // cout << "COPIA: ";
                    // print_ram(copia_RAM);
                    // getchar();
                    if(copia_RAM.size() == 1)
                        break;
                }
                auto index_sai = find(RAM.begin(), RAM.end(), copia_RAM[0]);
                esta_na_RAM[copia_RAM[0]] = false;
                RAM.erase(index_sai);
            }

            falta_de_pag++;
            esta_na_RAM[pag] = true;
            RAM.push_back(pag);
        }
        // print_ram(RAM);
        // getchar();
    }
    
    return falta_de_pag;
}