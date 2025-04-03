#include <algorithm>
#include "algoritmos.h"
#include "aux.h"

int main(int argc, char** argv)
{


    if(argc != 2)
    {
        cout << "INCORRETO!" << endl;
        cout << "USO: ./programa instancia.txt" << endl;
        return -1;
    }

    Data data = ler_instancia(argv[1]);

    // for(int i = 0; i < data.referencias.size(); i++)
    // {
    //     cout << data.referencias[i] << " ";
    // }
    // cout << endl;
    //cout << "MAIOR REF: " << data.maior_pag << endl;

    //FIFO
    cout << "FIFO " << FIFO(data) << endl;
    cout << "OTM " << OTM(data) << endl;
    cout << "LRU " << LRU(data) << endl;
    
}