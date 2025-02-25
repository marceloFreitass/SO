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
    int quantum = 2;
    vector<tuple<int, int , int>> fila;
    
    while(!processos.empty() || !fila.empty())
    {
        while(get<1>(processos[0]) <= tempo_atual && !processos.empty()){
            fila.push_back(processos[0]);
            processos.erase(processos.begin());
        }

        if(fila.empty())
            tempo_atual = get<1>(processos[0]);
        
            
        for(int i = 0; i < fila.size(); i++){
            gant.push_back({get<0>(fila[i]), tempo_atual, tempo_atual + min(quantum, get<2>(fila[i]))});
            tempo_atual += min(quantum, get<2>(fila[i]));
            if(get<2>(fila[i]) > quantum)
            {
                while(get<1>(processos[0]) <= tempo_atual && !processos.empty()){
                    fila.push_back(processos[0]);
                    processos.erase(processos.begin());
                }
                fila.push_back({get<0>(fila[i]), tempo_atual, get<2>(fila[i]) - quantum});
            }
            fila.erase(fila.begin() + i);
            break;
        }
    }

    return gant;
}

void calcula_tempos(vector<tuple<int,int,int>> gant, vector<tuple<int,int,int>> processos){
    size_t n_processos = processos.size();
    vector<bool> ids(n_processos, false);
    vector<int>  ultima_saida(n_processos, 0);
    double espera, retorno, resposta;
    espera = retorno = resposta = 0;

    double p_total = 0;

    for(int i = 0; i < n_processos; i++){
        ultima_saida[i] = get<1>(processos[i]);
        p_total += get<2>(processos[i]);
    }

    p_total = p_total/n_processos;

    for(int i = 0; i < gant.size(); i++){
        int processo_id = get<0>(gant[i]);
        if(!ids[processo_id]){
            resposta += get<1>(gant[i]) - get<1>(processos[processo_id]);
            ids[processo_id] = true;
        }
        espera += get<1>(gant[i]) - ultima_saida[processo_id];
        ultima_saida[processo_id] = get<2>(gant[i]);
    }

    espera = espera/n_processos;
    retorno = espera + p_total;
    resposta = resposta/n_processos;

    cout << retorno << " " << resposta << " " << espera << endl;
}