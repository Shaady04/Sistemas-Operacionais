#ifndef SJF_H
#define SJF_H

#include <iostream>
//#include <vector>
using namespace std;

class SJF {
    public:
        //tempo de chegada, tempo de pico, tempo de execução
        int temp_c, temp_p, init_exec, end_exec,aux1;
        int resp_time, ret_time, wait_time;
        
        SJF(int temp_c,int temp_p); // construtor 
        ~SJF(); // destrutor

        int getTempoDeChegada_SJF();
        int getTempoDePico_SJF();
        int Execucao_SJF(int temp_exec);// Apenas a execução é diferente, as fórmulas de tempo
        //int teste();              // de resposta, retorno e espera são as mesmas
        int TempoDeResposta_SJF();       
        int TempoDeRetorno_SJF();        
        int TempoDeEspera_SJF();    
};

#endif //SJF_H