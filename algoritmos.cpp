#include "algoritmos.h"
vector<tuple<int,int,int>> inicia_gant(vector<tuple<int,int,int>>& processos)
{
    int tempo_total = 0;
    vector<tuple<int,int,int>> gant;
    for(int i = 0; i < processos.size(); i++)
    {
        tempo_total += get<2>(processos[i]);
    }

    gant.reserve(tempo_total);
    return gant;
}

vector<tuple<int,int,int>> FCFS(vector<tuple<int,int,int>>& processos)
{
    vector<tuple<int,int,int>> gant = inicia_gant(processos);
    int tempo_atual = 0;
    for(int p = 0; p < processos.size(); p++)
    {
        //caso o proximo job nao tenha chegado ainda
        if(tempo_atual < get<1>(processos[p]))
        {
            tempo_atual = get<1>(processos[p]);
        }
        gant.push_back({get<0>(processos[p]), tempo_atual, 
        tempo_atual + get<2>(processos[p])});

        tempo_atual += get<2>(processos[p]);
    }

    return gant;
}

vector<tuple<int,int,int>> SJF(vector<tuple<int,int,int>> processos)
{
    vector<tuple<int,int,int>> gant = inicia_gant(processos);
    int tempo_atual = 0;
    bool alocou = false;
    while(!processos.empty())
    {
        int menor_tempo = numeric_limits<int>::max();
        alocou = false;
        for(int i = 0; i < processos.size(); i++)
        {
            //pegando o job com menor processamento que pode entrar no momento
            if(tempo_atual >= get<1>(processos[i]))
            {
                gant.push_back({get<0>(processos[i]), tempo_atual, tempo_atual + get<2>(processos[i])});
                tempo_atual += get<2>(processos[i]);
                processos.erase(processos.begin() + i);
                
                alocou = true;
                break;
            }
            //pegando o job que chega mais cedo
            if(get<1>(processos[i]) < menor_tempo)
            {
                menor_tempo = get<1>(processos[i]);
            }
        }
        //se nenhum job dos restantes chegou ainda
        if(!alocou)
        {
            tempo_atual = menor_tempo;
        }
    }

    return gant;
}

vector<tuple<int,int,int>> RR(vector<tuple<int,int,int>> processos)
{
    vector<tuple<int,int,int>> gant = inicia_gant(processos);
    int tempo_atual = 0;
    bool alocou = false;
    int quantum = 2;
    while(!processos.empty())
    {
        int menor_tempo = numeric_limits<int>::max();
        alocou = false;
        for(int i = 0; i < processos.size(); i++)
        {
            if(tempo_atual >= get<1>(processos[i]))
            {
                gant.push_back({get<0>(processos[i]), tempo_atual, tempo_atual + min(quantum, get<2>(processos[i]))});
                tempo_atual += min(quantum, get<2>(processos[i]));
                if(get<2>(processos[i]) > quantum)
                {
                    processos.push_back({get<0>(processos[i]), tempo_atual, get<2>(processos[i]) - quantum});
                }
                
                processos.erase(processos.begin() + i);

                
                alocou = true;
                break;
            }
            //pegando o job que chega mais cedo
            if(get<1>(processos[i]) < menor_tempo)
            {
                menor_tempo = get<1>(processos[i]);
            }
        }
        //se nenhum job dos restantes chegou ainda
        if(!alocou)
        {
            tempo_atual = menor_tempo;
        }
    }

    return gant;
}