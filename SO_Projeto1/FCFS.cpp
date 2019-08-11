#include "FCFS.h"

FCFS::FCFS(int temp_c, int temp_p){ 
    this->temp_c = temp_c;//tempo de chegada
    this->temp_p = temp_p;//tempo de pico
    this->init_exec = 0;
    this->end_exec = 0;
    this->resp_time = resp_time;
}

FCFS::~FCFS(){

}

int FCFS::getTempoDeChagada(){
    return temp_c;
}

int FCFS::getTempoDePico(){
    return temp_p;
}

int FCFS::Execucao(int temp_exec){
    int aux;
    //cout << "PROCESSO " << temp_c << endl;
    init_exec = temp_exec;
    TempoDeResposta();
    temp_exec += temp_p; // tempo de execução é quando começa + tempo de uso da CPU
    end_exec = temp_exec;
    TempoDeRetorno();
    TempoDeEspera();
    return temp_exec;
}
//tempo de resposta => tempo que começou a executar - tempo de chegada
//tempo de retorno  => tempo de término de execução - tempo de chegada
//tempo de espera   => tempo de retorno - tempo de pico

int FCFS::TempoDeResposta(){
    resp_time = init_exec - temp_c;
    //cout << "tempo de resposta: " << resp_time << endl;
    return resp_time;
}

int FCFS::TempoDeRetorno(){
    ret_time = end_exec - temp_c;
    //cout << "tempo de retorno: " << ret_time << endl ;
    return ret_time;
}

int FCFS::TempoDeEspera(){
    wait_time = ret_time - temp_p;
    //cout << "Tempo de espera: " << wait_time << endl;
    return wait_time;
}

