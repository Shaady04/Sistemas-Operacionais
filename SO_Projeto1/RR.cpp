#include "RR.h"

RR::RR(int temp_c, int temp_p){ 
    this->temp_c = temp_c;//tempo de chegada
    this->temp_p = temp_p;//tempo de pico
    this->init_exec = 0;
    this->end_exec = 0;
    this->resp_time = resp_time;
}

RR::~RR(){

}

int RR::getTempoDeChegada_RR(){
    return temp_c;
}

int RR::getTempoDePico_RR(){
    return temp_p;
}

int RR::Execucao_RR(int temp_exec){
    if(!aux1){
        init_exec = temp_exec;
        //cout << "Init_exec = " << init_exec << endl;
        TempoDeResposta_RR();
        aux1 = temp_p;
    }

    if(temp_p > 0)--temp_p;   // quando o tempo de pico =0
                             // então foi executado o processo
    if(!temp_p){
        end_exec = (temp_exec+1);
        //cout << "End_exec = "<< end_exec << endl;
        TempoDeRetorno_RR(); // O tempo de retorno 
        TempoDeEspera_RR(); // 
    }
   
    return temp_exec;
}

int RR::TempoDeResposta_RR(){
    resp_time = init_exec - temp_c;
    return resp_time;
}

int RR::TempoDeRetorno_RR(){
    ret_time = end_exec - temp_c;
    return ret_time;
}

int RR::TempoDeEspera_RR(){
    wait_time = ret_time - aux1;
    return wait_time;
}

