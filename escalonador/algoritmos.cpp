#include "algoritmos.h"
//formato gant: [ID PROCESSO, TEMPO DE CHEGADA NA CPU, TEMPO DE SAIDA DA CPU]
//UM PROCESSO PODE SAIR E ENTRAR VARIAS VEZES
vector<tuple<int,int,int>> inicia_gant(vector<tuple<int,int,int>>& processos)
{
    //reservando espaço para o gant (soma dos tempos de pico)
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
    //os processos estao ordeandos por TEMPO DE CHEGADA (crescente)
    vector<tuple<int,int,int>> gant = inicia_gant(processos);
    int tempo_atual = 0;
    for(int p = 0; p < processos.size(); p++)
    {
        int tempo_pico = get<2>(processos[p]);
        int tempo_chegada = get<1>(processos[p]);
        //caso o proximo job nao tenha chegado ainda (cpu ociosa)
        if(tempo_atual < tempo_chegada)
        {
            tempo_atual = tempo_chegada;
        }
        //adicionando o job atual no gant
        gant.push_back({get<0>(processos[p]), tempo_atual, 
        tempo_atual + tempo_pico});
        //adicionando a tempo atual o tempo de pico do processo
        tempo_atual += tempo_pico;
    }

    return gant;
}

vector<tuple<int,int,int>> SJF(vector<tuple<int,int,int>> processos)
{
    //os processos estao ordeandos por TEMPO DE PICO (crescente)
    vector<tuple<int,int,int>> gant = inicia_gant(processos);
    int tempo_atual = 0;
    bool alocou = false;
    while(!processos.empty())
    {
        int menor_tempo = numeric_limits<int>::max();
        alocou = false;
        for(int i = 0; i < processos.size(); i++)
        {
            int tempo_pico = get<2>(processos[i]);
            int tempo_chegada = get<1>(processos[i]);
            //pegando o job com menor processamento que pode entrar no momento
            if(tempo_atual >= tempo_chegada)
            {
                gant.push_back({get<0>(processos[i]), tempo_atual, tempo_atual + tempo_pico});
                tempo_atual += tempo_pico;
                processos.erase(processos.begin() + i);
                
                alocou = true;
                break;
            }
            //pegando o job que chega mais cedo
            if(tempo_chegada < menor_tempo)
            {
                menor_tempo = tempo_chegada;
            }
        }
        //se nenhum job dos restantes chegou ainda (caso em que a CPU fica ociosa)
        if(!alocou)
        {
            tempo_atual = menor_tempo;
        }
    }

    return gant;
}

vector<tuple<int,int,int>> RR(vector<tuple<int,int,int>> processos)
{
    //os processos estao ordeandos por TEMPO DE CHEGADA (crescente)
    vector<tuple<int,int,int>> gant = inicia_gant(processos);
    int tempo_atual = 0;
    int quantum = 2;
    //FILA DE PROCESSOS PRONTOS PARA ENTRAR NA CPU
    vector<tuple<int, int , int>> fila;
    
    while(!processos.empty() || !fila.empty())
    {      
        
        //adicionando processos prontos a fila (dando prioridade aos mais novos)
        while(get<1>(processos[0]) <= tempo_atual && !processos.empty()){
            fila.push_back(processos[0]);
            processos.erase(processos.begin());
        }

        //caso nao tenha nenhum processo pronto (CPU ociosa)
        if(fila.empty())
        {  
            tempo_atual = get<1>(processos[0]);            
            fila.push_back(processos[0]);
            processos.erase(processos.begin());
        }
            
        //o primeiro da fila vai entrar na CPU
        int tempo_pico = get<2>(fila[0]);
        //colocando no gant
        gant.push_back({get<0>(fila[0]), tempo_atual, tempo_atual + min(quantum, tempo_pico)});
        //somando o quantum (ou o tempo de pico se < quantum)
        tempo_atual += min(quantum, tempo_pico);
        //caso o processo nao tenha terminado, ele volta para fila novamente
        if(tempo_pico > quantum)
        {
            //verificando se algum processo novo chegou nesse meio tempo
            // e dando prioridade a eles
            while(get<1>(processos[0]) <= tempo_atual && !processos.empty()){
                fila.push_back(processos[0]);
                processos.erase(processos.begin());
            }
            fila.push_back({get<0>(fila[0]), tempo_atual, tempo_pico - quantum});
        }
        //retirando processo da fila
        fila.erase(fila.begin());
    }

    return gant;
}

void calcula_tempos(vector<tuple<int,int,int>> gant, vector<tuple<int,int,int>> processos){
    size_t n_processos = processos.size();
    //vetor que informa se o processo ja entrou na CPU pela primeira vez
    vector<bool> entrou(n_processos, false);
    //vetor que guarda a ultima vez que um processo saiu da CPU
    vector<int>  ultima_saida(n_processos, 0);
    double espera, retorno, resposta;
    espera = retorno = resposta = 0;

    double p_total = 0;

    //iniciando ultima saida e pegando o tempo de processamento total
    for(int i = 0; i < n_processos; i++){
        ultima_saida[i] = get<1>(processos[i]);
        p_total += get<2>(processos[i]);
    }

    //calculando media do tempo de processamento
    p_total = p_total/n_processos;

    for(int i = 0; i < gant.size(); i++){
        int processo_id = get<0>(gant[i]);
        //caso o processo nunca esteve na CPU
        if(!entrou[processo_id]){
            //adicionando o tempo de resposta do processo
            resposta += get<1>(gant[i]) - get<1>(processos[processo_id]);
            entrou[processo_id] = true;
        }
        //adicionando o tempo de espera do processo
        espera += get<1>(gant[i]) - ultima_saida[processo_id];
        //atualizando a ultima vez em que o processo saiu
        ultima_saida[processo_id] = get<2>(gant[i]);
    }

    //calculando as medias
    espera = espera/n_processos;
    retorno = espera + p_total;
    resposta = resposta/n_processos;

    std::locale::global(std::locale("pt_BR.utf8"));
    std::cout.imbue(std::locale("pt_BR.utf8"));

    cout << fixed << setprecision(1) << retorno << " " << resposta << " " << espera << endl;
}