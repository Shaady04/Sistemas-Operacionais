/**
 * Os algoritmos de escalonamento a serem
implementados são os seguintes:
 *FCFS: First-Come, First-Served (FIFO)
 *SJF: Shortest Job First 
 *RR: Round Robin (com quantum = 2) */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include "FCFS.h"
#include <string.h>
#include <list>
#include <cctype>
#include "SJF.h"
#include "RR.h"

/*  FUNÇÕES PARA O MÉTODO DE ESCALONAMENTO (RR) */
void Executa_RR(list<RR> &rr, int &totalExec);
void Inserir_RR(list<RR> &rr, int &temp_c, int &temp_p);
bool Ordena_RR(RR firs, RR second);
void Imprime_RR(list<RR> &rr);

/* FUNÇÕES PARA O MÉTODO SJF (posteriormente otimizar esse código) */
bool Verifica_SJF(list<SJF> &sjf, int &temp_c, int &temp_p, int &tempo_totalExec);
void Inserir_SJF(list<SJF> &sjf, int &temp_c, int &temp_p);
bool Compara_SJF(SJF first, SJF second);
void Imprime_SJF(list<SJF> &sjf);
bool SJF_Puro(SJF first, SJF second);


void Inserir_FCFS(list<FCFS> &fifo, int &temp_c, int &temp_p);
int Executa_FCFS(list<FCFS> &fifo);
int Teste(list<FCFS> &fifo);

//essa função serve para organizar a lista baseado no tempo de chegada, caso ela esteja desorganizada 
bool compara_ordem(FCFS first, FCFS second){
    if (first.getTempoDeChagada() > 
        second.getTempoDeChagada()) 
        return false;
 
    if (first.getTempoDeChagada() < 
        second.getTempoDeChagada()) 
        return true;

    return true;
}

int main(){
    ifstream arquivo;
    string linha, valor;
    char ler[30];
    list<FCFS> fifo;
    list<SJF> sjf;
    list<RR> rr;
    int teste, totalExec =0;

    arquivo.open("teste.txt");
    if(!arquivo.is_open()){
        cout << "Sem arquivo !!\n";
    }else{
        while(!arquivo.eof()){
            arquivo >> linha;
            valor += linha + ' ';
        }
    }
    arquivo.close();

    for(int i=0; i < valor.size();i++){
        ler[i] = valor[i];
    }
    
    char *token = strtok(ler," ");
    int c=0,i=0, j=0;
    while (token != NULL){ 
        //cout << "token : "<< token;
        teste = atoi(token);
        if(c%2==0){
            i = teste;
        }else{
            j = teste;
            Inserir_FCFS(fifo,i,j); // 
            Inserir_SJF(sjf,i,j);
            Inserir_RR(rr,i,j);

        }
        c++;
        token = strtok(NULL, " "); 
    } 
    
    fifo.sort(compara_ordem); // Em caso do arquivo vir desordenado o problema é resolvido
    totalExec = Executa_FCFS(fifo);
    
    sjf.sort(Compara_SJF);
    int tempoDeExec=0;
    int x=1;
    while(tempoDeExec != totalExec){ //enquanto ainda tiver processos em execução ele roda
        list<SJF>::iterator it;
        for(it = sjf.begin(); it != sjf.end(); it++){
            bool testes = true;

            while(testes){
                int opa;
                opa = it->getTempoDePico_SJF();
                testes = Verifica_SJF(sjf,tempoDeExec,opa, totalExec);
                if(testes){
                    it->Execucao_SJF(tempoDeExec);
                    tempoDeExec++;
                }
                opa = it->getTempoDePico_SJF();
                //cout << "Tempo de execução2 : " << tempoDeExec  << " Arrive time2: "<< it->getTempoDeChegada_SJF() << " Burst time : " << opa << endl;
                
                if(!it->getTempoDePico_SJF()){
                    testes = false;
                }
            }
        }
    }
    Imprime_SJF(sjf);

    // Parte da execução do RR
    rr.sort(Ordena_RR);
    Executa_RR(rr, totalExec);
    Imprime_RR(rr);

    return 0;
}


/*                              ------------------- SEÇÃO RR -------------------  */
void Executa_RR(list<RR> &rr, int &totalExec){
    // Fazer semelhante ao SJF
    int tempoDeExec =0;
    //cout << "Tempo total = " << totalExec << endl;
    while(tempoDeExec != totalExec){ //enquanto ainda tiver processos em execução ele roda
        list<RR>::iterator it;

        for(it = rr.begin(); it != rr.end(); it++){
            int quantum = 2;
            while(quantum!=0){
                int opa;
                opa = it->getTempoDePico_RR();
                if(!opa){
                    break;
                }
                it->Execucao_RR(tempoDeExec);
                tempoDeExec++;
                quantum--;
                //opa = it->getTempoDePico_RR();
                //cout << "Tempo de execução2 : " << tempoDeExec  << " Arrive time2: "<< it->getTempoDeChegada_RR() << " Burst time : " << opa << endl; 
            }
        }
    }
}

void Inserir_RR(list<RR> &rr, int &temp_c, int &temp_p){
    RR r = RR(temp_c,temp_p); 
    rr.push_front(r);
}   

bool Ordena_RR(RR first, RR second){
    if (first.getTempoDeChegada_RR() > second.getTempoDeChegada_RR()) 
        return false;
    if (first.getTempoDeChegada_RR() < second.getTempoDeChegada_RR()) 
        return true;

    return true; 
}

void Imprime_RR(list<RR> &rr){
    int TMR=0, TMRT=0,TMESP=0, tempo_de_exec=0;
    list<RR>::iterator it;
    for(it = rr.begin(); it!=rr.end();it++){
        TMR += it->TempoDeResposta_RR();
        TMRT+= it->TempoDeRetorno_RR();
        TMESP+= it->TempoDeEspera_RR();
        //cout << "Processo " << it->getTempoDeChegada_RR() << " BRSTT: " << it->getTempoDePico_RR() << endl;
    }
    cout << "RR " << ((double)TMRT/rr.size()) << " " << ((double)TMR/rr.size()) << " " << ((double)TMESP/rr.size()) << endl;
}


/*                               ---------------------  SEÇÃO FCFS ---------------------*/
void Inserir_FCFS(list<FCFS> &fifo, int &temp_c, int &temp_p){
    FCFS f = FCFS(temp_c, temp_p);
    //fifo.push_back(f);
    fifo.push_front(f);// Usando um push_front não tenho o problema na troca da ordem 
    //cout << "item adicionado a lista" << endl;
}

int Teste(list<FCFS> &fifo){
    list<FCFS>::iterator it;
    for (it = fifo.begin(); it != fifo.end(); ++it) {
         return it->getTempoDeChagada();
    }
}

int Executa_FCFS(list<FCFS> &fifo){
    int TMR=0, TMRT=0,TMESP=0, tempo_de_exec=0; // TMR = tempo médio de resposta ; TMRT = tempo médio de retorno; TMESP = tempo médio de espera
    list<FCFS>::iterator it;
    for(it = fifo.begin(); it!=fifo.end();it++){ // só verificar se o sort deu certo
        //c++;
        tempo_de_exec = it->Execucao(tempo_de_exec);
        TMR += it->TempoDeResposta();
        TMRT+= it->TempoDeRetorno();
        TMESP+= it->TempoDeEspera();
        //cout << "Processo:" << it->getTempoDeChagada() << " , burst time: " << it->getTempoDePico() << endl;
    }
    //cout<<"TEMPO TOTAL DE EXEC:" << tempo_de_exec << endl;
    //cout<<"VAlor de teste " << TMR << endl;
    //cout << "Tempo médio de Resposta  Tempo médio de Retorno Tempo médio de Espera" << endl;  
    cout << "FCFS " << ((double)TMRT/fifo.size()) << " " << ((double)TMR/fifo.size()) << " " << ((double)TMESP/fifo.size()) << endl;
    return tempo_de_exec;
}

/**                                 ----------------- SEÇÃO SJF ----------------- */

bool Verifica_SJF(list<SJF> &sjf, int &temp_c, int &temp_p,int &tempo_totalExec){ // os parâmetros são : o tempo de chegada(ou seja o tempo que está ocorrendo a exec) 
    list<SJF>::iterator it;                                 // e o tempo de pico do processo que está executando, então basta comparar se o tempo
    static int MaiorTemp=0; // Maior tempo de chegada 
    if(temp_c <= tempo_totalExec){  // MUDAR PARA TEMPO TOTAL DE EXECUÇÃO                          
        for (it = sjf.begin(); it != sjf.end(); ++it) {       // do processo que chegou num X tempo de execução é menor que o tempo restante do processo
             if(it->getTempoDeChegada_SJF() > MaiorTemp) MaiorTemp = it->getTempoDeChegada_SJF();
             
             if(temp_c == it->getTempoDeChegada_SJF() && temp_p > it->getTempoDePico_SJF() && it->getTempoDePico_SJF()!=0){ // anteriormente executado
                    //cout << "QUEM QUERO, ART: " << it->getTempoDeChegada_SJF() << " BRST : " << it->getTempoDePico_SJF() << endl;
                    return false;
             }
             if(temp_c > MaiorTemp){// Se o tempo de execução for maior que o maior tempo de chegada, basta fazer um sort 
                                    // por meio do tempo de pico de cada processo restante
                sjf.sort(SJF_Puro);//Usar o sort do pico(burst time)
             }

        //cout << "Maior é : " << MaiorTemp << endl;
        }
        return true; 
    }else{
        return false;
    }  
    
}

bool SJF_Puro(SJF first, SJF second){
    if (first.getTempoDePico_SJF() > second.getTempoDePico_SJF()) 
        return false;
    if (first.getTempoDePico_SJF() < second.getTempoDePico_SJF()) 
        return true;

    return true;
}

bool Compara_SJF(SJF first, SJF second){
    if (first.getTempoDeChegada_SJF() > second.getTempoDeChegada_SJF()) 
        return false;
    if (first.getTempoDeChegada_SJF() < second.getTempoDeChegada_SJF()) 
        return true;

    return true;
}

void Inserir_SJF(list<SJF> &sjf, int &temp_c, int &temp_p){
    SJF s = SJF(temp_c, temp_p);
    sjf.push_front(s);
}

void Imprime_SJF(list<SJF> &sjf) {
    int TMR=0, TMRT=0,TMESP=0, tempo_de_exec=0;
    list<SJF>::iterator it;
    for(it=sjf.begin(); it != sjf.end(); it++){
        TMR += it->TempoDeResposta_SJF();
        TMRT+= it->TempoDeRetorno_SJF();
        TMESP+= it->TempoDeEspera_SJF();
        //cout << "Processo " << it->getTempoDeChegada_SJF() << " ASWT: " << it->TempoDeResposta_SJF()  << " RTNT: " << it->TempoDeRetorno_SJF() << " WTT: " << it->TempoDeEspera_SJF() << endl;
        //cout << "Tempo de Chegada : " << it->getTempoDeChegada_SJF() << " Tempo de pico: " << it->getTempoDePico_SJF() << endl;
    }
    cout << "SJF " << ((double)TMRT/sjf.size()) << " " << ((double)TMR/sjf.size()) << " " << ((double)TMESP/sjf.size()) << endl;

}
