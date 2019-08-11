#ifndef RR_H
#define RR_H

#include <iostream>
using namespace std;

class RR {
    public:
        //tempo de chegada, tempo de pico, tempo de execução
        int temp_c, temp_p, init_exec, end_exec,aux1;
        int resp_time, ret_time, wait_time;
        
        RR(int temp_c,int temp_p); // construtor 
        ~RR(); // destrutor

        int getTempoDeChegada_RR();
        int getTempoDePico_RR();
        int Execucao_RR(int temp_exec);// Apenas a execução é diferente, as fórmulas de tempo
                                        // de resposta, retorno e espera são as mesmas
        int TempoDeResposta_RR();       
        int TempoDeRetorno_RR();        
        int TempoDeEspera_RR();    
};

#endif //RR_H