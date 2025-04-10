#include "algoritmos.h"

int FIFO(Data& data)
{
    // vetor que indica se a pagina já se encontra na memoria principal
    vector<bool> esta_na_RAM(data.maior_pag, false);
    // vetor que representa a memoria principal
    queue<int> RAM;
    int qtd_referencias = data.referencias.size();
    // contador de falta de paginas
    int falta_de_pag = 0;
    for(int i = 0; i < qtd_referencias; i++)
    {
        // pagina sendo referenciada
        int pag = data.referencias[i];
        // se a pagina referenciada nao estiver na ram
        if(!esta_na_RAM[pag])
        {
            // se a ram estiver cheia
            if(RAM.size() == data.qtd_frames)
            {
                // tira a pagina mais antiga
                int sai = RAM.front();
                RAM.pop();
                // atualizada o estado da pagina retirada da ram
                esta_na_RAM[sai] = false;
            }
            falta_de_pag++;
            // adicionando a pagina referenciada na memoria principal
            esta_na_RAM[pag] = true;
            RAM.push(pag);
        }
    }
    
    return falta_de_pag;

}

int LRU(Data& data)
{
    // vetor que indica se a pagina já se encontra na memoria principal
    vector<bool> esta_na_RAM(data.maior_pag, false);
    // vetor que representa a memoria principal
    // quando a pagina é referenciada ela é movida para o final do vetor
    vector<int> RAM;
    
    int qtd_referencias = data.referencias.size();
    //contador de falta de paginas
    int falta_de_pag = 0;

    for(int i = 0; i < qtd_referencias; i++)
    {
        // pagina sendo referenciada
        int pag = data.referencias[i];

        // se a pagina referenciada nao estiver na ram
        if(!esta_na_RAM[pag])
        {
            // se a ram estiver cheia
            if(RAM.size() == data.qtd_frames)
            {
                // removendo pagina menos recentemente usada  
                int sai = RAM[0];
                esta_na_RAM[sai] = false;
                RAM.erase(RAM.begin());
            }
            falta_de_pag++;
        }

        // index no vector ram da pagina referenciada
        auto index_pag = find(RAM.begin(), RAM.end(), pag);

        // se a pagina já estava na memoria principal
        // ela foi referenciada novamente
        if(index_pag != RAM.end())
        {
            RAM.erase(index_pag);     
        }
        // inserindo a pagina referenciada no final do vetor
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