/**
Os algoritmos de substituição de páginas a serem
implementados são os seguintes :    
 *(FIFO)
 *OMT: Shortest Job First 
 *LRU:
Formato da saída :
    FIFO 10
    OTM 6
    LRU 8
*/
#include <iostream>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <queue>

using namespace std;

/* ------------------ PARTE DO FIFO ------------------ */
void FIFO(int *ram, int &N, int *paginas, int &M);
void Busca_Pagina(int &valor, int *ram, int &N);

/* ------------------ PARTE DO OPTIMAL ------------------ */
void OTM(int *ram_omt ,int &N, int *paginas, int &M);
void Busca_Pagina_OTM(int *paginas, int *ram_omt, int &N, int &indice, int &M);

/* ------------------ PARTE DO LRU ------------------ */
void LRU(int *ram_lru, int &N, int *paginas, int &M);
void Busca_Pagina_LRU(int *paginas, int *ram_lru, int &N, int &indice, int &M);


int main(){
    ifstream arquivo;
    string linha;
    queue<int> fila; 
    int N, M, i, x;
    int j;
    
    N=0; // inicializa N
    M=-1; // inicializa M
    arquivo.open("processo2.txt");
    if(!arquivo.is_open()){
        cout << "Sem arquivo !!\n";
    }else{
        while(!arquivo.eof()){
            arquivo >> linha;
            x = stoi(linha); 
            if(!N){
                N = x; // O primeiro valor é a quantidade de quadros
            }else{
                fila.push(x);// O restante dos valores são as páginas   
            }

            M++;
        }
    }
    arquivo.close();

    int paginas[M], ram_omt[N], ram_lru[N], ram[N];
    for(i=0; i<M; i++){
        paginas[i] = fila.front();
        fila.pop();
        //cout << "paginas[" << i << "] = " << paginas[i] << endl;
    }

    for(i=0; i<N; i++){ // Inicializa o array
        ram_omt[i]=-1;
        ram_lru[i]=-1;
        ram[i]=-1;
    }

    FIFO(ram, N, paginas, M);
    OTM(ram_omt, N, paginas, M);
    LRU(ram_lru, N, paginas, M);

    return 0;
}

/*------------------ PARTE DO FIFO ------------------ */
void FIFO(int *ram, int &N, int *paginas, int &M){
    int i=0, falta=0, c=0;
    //1- verificar se a página está na memória
    //2- se não está na memória, verifica se tem espaço
    while(i<M){
        for(int j=0; j < N; j++){
            if(paginas[i] == ram[j])c=1;
            //cout << "paginas[" << i << "] = " << paginas[i] << endl;
            //cout << "ram[" << j << "] = " << ram[j] << endl;
        }
        if(!c){ // se não encontrou ninguém, então tem-se uma falta
            falta++; 
            Busca_Pagina(paginas[i],ram, N);
        }
        c=0;
        i++;
    }

    cout << "FIFO " << falta << endl;
}

void Busca_Pagina(int &valor, int *ram, int &N){
    int c=0, i, j=0;
    for(i=0; i < N; i++){
        if(ram[i] == -1 && !c){ // Add se tem espaço vazio
            ram[i] = valor;
            c++;       
        }
    }
    
    if(i==(N) && !c){     // Se está cheio, vai substituir alguém
        while(j<N){
            ram[j] = ram[j+1]; // ram[0] sempre será trocado, por ser o mais antigo 
            j++;               // então faço um shift dos resto para o começo
        }
        ram[j-1] = valor;
    }
}

/*------------------ PARTE DO OTM ------------------ */
void OTM(int *ram_omt ,int &N, int *paginas, int &M){
    int i=0, falta=0, c=0;

    while(i<M){
       for(int j=0; j < N; j++){
            if(paginas[i] == ram_omt[j])
                c=1;
        }
        if(!c){ // se não encontrou ninguém, então tem-se uma falta
            falta++; 
            Busca_Pagina_OTM(paginas,ram_omt, N, i, M);
        }

        c=0;
        i++;
    }
    cout << "OTM " << falta << endl;
}

void Busca_Pagina_OTM(int *paginas, int *ram_omt, int &N, int &indice, int &M){
    int c=0, i, j=0, flag=0, D, flag2;
    int counter=0, maior=0, aux; 
    //cout << "Quem está indo -> " << indice << endl;
    for(i=0; i < N; i++){
        if(ram_omt[i] == -1 && !c){ // Apenas add se tem espaço vazio
            ram_omt[i] = paginas[indice];
            c++;       
        }
    }
        
    if(i==N && !c){ // Se está cheio, vai substituir alguém
        for(i=0; i < N; i++){
            j=indice;
            while(j<M){
                if(ram_omt[i] != paginas[j]){
                    counter++;
                    flag2 = i;// guarda quem não repete mais
                }   // 

                if(ram_omt[i] == paginas[j]){
                    flag = 1; // importante no final do array de páginas
                    break;                   
                }

                j++;
            }
    
            if(maior < counter){ // salva o elemento que será menos utilizado
                maior = counter;
                aux = i; // Índice que deve ser substituido
            }

            //Caso especial : quando chegamos no final do array paginas
            D = indice-M;//Distância para chegar no final for < que M
            if(D<N && !flag){ // então qualquer valor que não apareça
                aux = flag2; // pode ser substituído
            }               // flag indica que um valor não foi encontrado
                            // e flag2 quarda que índice pode ser substituido
            counter=0;
        }

        ram_omt[aux] = paginas[indice]; // substituição
    }
}

/*------------------ PARTE DO LRU ------------------ */
void LRU(int *ram_lru, int &N, int *paginas, int &M){
    int i=0, falta=0, c=0;

    while(i<M){
       for(int j=0; j < N; j++){
            if(paginas[i] == ram_lru[j])
                c=1;
        }
        
        if(!c){ // se não encontrou ninguém, então temos uma falta
            falta++; 
            Busca_Pagina_LRU(paginas,ram_lru, N, i, M);
        }
        c=0;
        i++;
    }
    cout << "LRU " << falta << endl;
}

void Busca_Pagina_LRU(int *paginas, int *ram_lru, int &N, int &indice, int &M){
    // É um pouco semelhante ao OTM
    int c=0, i, j=0;
    int counter=0, maior=0, aux; 
    
    for(i=0; i < N; i++){
        if(ram_lru[i] == -1 && !c){ // Add se tem espaço vazio
            ram_lru[i] = paginas[indice];
            c++; // indica se está a memória principal está cheia       
        }
    }
    
    if(i==N && !c){ // Se está cheio, vai substituir alguma página
        //cout << "Entrou indice " << indice << ", valor " << paginas[indice] << endl;
        for(i=0; i < N; i++){
            j=indice;
            while(j>=0){  // Analizando os termos passados
                if(ram_lru[i] != paginas[j])
                    counter++;

                if(ram_lru[i] == paginas[j])
                    break;                   
                j--;
            }
    
            if(maior < counter){ // salva o elemento que será menos utilizado
                maior = counter;
                aux = i; // Índice que deve ser substituido
            }
        
            counter=0;
        }

        ram_lru[aux] = paginas[indice]; // substituição
    }   
}