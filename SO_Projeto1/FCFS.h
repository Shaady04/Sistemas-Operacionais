#ifndef FCFS_H
#define FCFS_H

#include <iostream>
#include <vector>
using namespace std;

class FCFS {
    public:
        //tempo de chegada, tempo de pico, tempo de execução
        int temp_c, temp_p, init_exec, end_exec;
        int resp_time, ret_time, wait_time;
        
        FCFS(int temp_c,int temp_p); // construtor 
        ~FCFS(); // destrutor

        int getTempoDeChagada();
        int getTempoDePico();
        int Execucao(int temp_exec);
        //int teste();
        int TempoDeResposta();       
        int TempoDeRetorno();        
        int TempoDeEspera();    
};

/*Estratégia
  Como é um método de FIFO o que importa é quem chega primeiro
  então se eu coloco numa array onde cada índice é o tempo de chegada
  e contendo a quantidade de pico
 */

#endif //FCFS_H