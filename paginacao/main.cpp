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

    // lendo instância 
    Data data = ler_instancia(argv[1]);

    // rodando algoritimos
    cout << "FIFO " << FIFO(data) << endl;
    cout << "OTM " << OTM(data) << endl;
    cout << "LRU " << LRU(data) << endl;
    
    return 0;
}