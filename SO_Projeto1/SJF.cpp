#include "SJF.h"

SJF::SJF(int temp_c, int temp_p){ 
    this->temp_c = temp_c;//tempo de chegada
    this->temp_p = temp_p;//tempo de pico
    this->init_exec = 0;
    this->end_exec = 0;
    this->resp_time = resp_time;
    this->aux1 = 0;
}

SJF::~SJF(){

}

int SJF::getTempoDeChegada_SJF(){
    return temp_c;
}

int SJF::getTempoDePico_SJF(){
    return temp_p;
}

int SJF::Execucao_SJF(int temp_exec){ // Preciso decrementar o tempo de pico dos processos
    //int aux1=0;
    if(!aux1){
        init_exec = temp_exec;
        //cout << "Init_exec = " << init_exec << endl;
        TempoDeResposta_SJF();
        aux1 = temp_p;
        //aux+=1;
    }
    if(temp_p > 0)--temp_p;   // quando o tempo de pico =0
                             // então foi executado o processo

    if(!temp_p){
        end_exec = temp_exec;
        //cout << "End_exec = "<< end_exec << endl;
        TempoDeRetorno_SJF(); // O tempo de retorno 
        TempoDeEspera_SJF(); // 
    }
    //temp_exec = temp_p;
    
    return temp_p;
}
//tempo de resposta => tempo que começou a executar - tempo de chegada
//tempo de retorno  => tempo de término de execução - tempo de chegada
//tempo de espera   => tempo de retorno - tempo de pico

int SJF::TempoDeResposta_SJF(){
    resp_time = init_exec - temp_c;
    //cout << "tempo de resposta: " << resp_time << endl;
    return resp_time;
}

int SJF::TempoDeRetorno_SJF(){
    ret_time = (end_exec+1) - temp_c;
    //cout << "tempo de retorno: " << ret_time << endl ;
    return ret_time;
}

int SJF::TempoDeEspera_SJF(){
    wait_time = ret_time - aux1;//temp_p;
    //cout << "Tempo de espera: " << wait_time << endl;
    return wait_time;
}

