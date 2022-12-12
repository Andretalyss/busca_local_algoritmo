#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <time.h>   

#define N_PRESENTES 1000

using namespace std;

int k;
int n_presentes;
int q;
int n_elementos;
int array[N_PRESENTES];
int array_index[N_PRESENTES];
int lista[N_PRESENTES][N_PRESENTES];
int melhor_vizinho_vnd1;
int melhor_vizinho_vnd2;

struct trenos {
    int array[N_PRESENTES];
    int array_index[N_PRESENTES];
    int itens;
    int qtd;
};

struct trenos trenos[N_PRESENTES]; 
struct trenos trenos_aux[N_PRESENTES]; // Utilizado para o vnd1.
struct trenos trenos_aux1[N_PRESENTES]; // Utilizado para o vnd2.

int ReadInstance(){
    FILE *arq;

    // Seleciona o arquivo de instâncias a ser lido.
    arq = fopen("./instances/n1000_k200_B.txt", "r");
    if(!arq) {
        puts("Não abriu");
        return 0;
    }

    fscanf(arq, "%d\n", &n_presentes);
    fscanf(arq, "%d\n", &k);
    fscanf(arq, "%d\n", &q);
    fscanf(arq, "%d\n", &n_elementos);

    for (int i=1; i <= n_presentes; i++){
        fscanf(arq, "%d ", &array[i]);
        array_index[i] = i;
    }
    int aux1, aux2;
    for (int i=1; i <= n_elementos; i++){
        fscanf(arq, "%d ", &aux1);
        fscanf(arq, "%d\n", &aux2);

        lista[aux1][aux2]=1;
    }

    return 1;
}

void ordena_presentes(){
    int copia_peso;
    int copia_index;
    int troca;
    do {
        troca = 0;
        for(int j=1;j<N_PRESENTES;j++){
          if(array[j] > array[j+1]){
            copia_peso = array[j];
            array[j] = array[j+1];
            array[j+1] = copia_peso;

            copia_index = array_index[j];
            array_index[j] = array_index[j+1];
            array_index[j+1] = copia_index;
            troca = 1;

          }
        }
    }while(troca);
    
}

void inicializa_vetores(){
    for (int i=0; i<n_presentes;i++){
        trenos[i].qtd = q;
        trenos[i].itens = 0;

        // Inicializa sacola do treno com 1000 em cada index.
        for(int j=0;j<n_presentes;j++){
            trenos[i].array[j] = 1000;
        }
    }
}

void copia_trenos(int melhor){
    for(int i=0;i<melhor;i++){
       if(trenos[i].itens == 0){
            continue;
       }
       trenos_aux[i].qtd = trenos[i].qtd;
       trenos_aux[i].itens = trenos[i].itens;
       for(int j=0;j<trenos[i].itens;j++){
            trenos_aux[i].array[j] = trenos[i].array[j];
            trenos_aux[i].array_index[j] = trenos[i].array_index[j]; 
       }
    }
}

void copia_trenos_vnd2(int melhor){
    for(int i=0;i<melhor;i++){
       if(trenos_aux[i].itens == 0){
            continue;
       }
       trenos_aux1[i].qtd = trenos_aux[i].qtd;
       trenos_aux1[i].itens = trenos_aux[i].itens;
       for(int j=0;j<trenos_aux[i].itens;j++){
            trenos_aux1[i].array[j] = trenos_aux[i].array[j];
            trenos_aux1[i].array_index[j] = trenos_aux[i].array_index[j]; 
       }
    }
}

void vnd1(int melhor, bool copiar){
    melhor_vizinho_vnd1 = N_PRESENTES;
    bool inc = false;
    bool zerou = false;
    while(melhor < melhor_vizinho_vnd1){
        melhor_vizinho_vnd1 = N_PRESENTES;

        for(int i=0;i<melhor;i++){
            if(zerou)
                break;

            if(!copiar){
               copia_trenos(melhor);
            }
            
            for(int j=0;j<trenos[i].itens;j++){
                if(trenos_aux[i].array[j] == 1000)
                    break;
                
                if(zerou){
                    break;
                }
                    
                for(int t=0;t<melhor;t++){
                    if(t==i)
                        continue;
                    
                    if(trenos_aux[t].itens == 0)
                        continue;
                    
                    inc = false;
                    
                    if(trenos_aux[t].qtd >= trenos_aux[i].array[j]){
                        for(int s=0;s<trenos[t].itens;s++){
                            if(trenos_aux[t].array[s] == 1000)
                                break;
                            
                            if(lista[trenos_aux[t].array_index[s]][trenos_aux[i].array_index[j]]){                               
                                inc = true;
                                break;
                            }else if(lista[trenos_aux[i].array_index[j]][trenos_aux[t].array_index[s]]){
                                inc = true;
                                break;
                            }
                        }

                        if(!inc){
                            trenos_aux[t].array[trenos_aux[t].itens] = trenos_aux[i].array[j];
                            trenos_aux[t].array_index[trenos_aux[t].itens] = trenos_aux[i].array_index[j];
                            trenos_aux[t].qtd -= trenos_aux[t].array[trenos_aux[t].itens];
                            trenos_aux[t].itens++;

                            trenos_aux[i].array[j] = 1000;
                            trenos_aux[i].array_index[j] = 100;
                            trenos_aux[i].qtd += trenos_aux[t].array[trenos_aux[t].itens-1];
                            trenos_aux[i].itens--;
                            
                            if(trenos_aux[i].itens == 0){
                                zerou = true;
                            }

                            break;
                        }else{
                            continue;
                        }
                    }


                }

            }
        }

        for(int i=0;i<n_presentes;i++){
            if(trenos_aux[i].itens != 0){
                    continue;
            }
            melhor_vizinho_vnd1--;
        }

        printf("Melhor vizinho VND1  = %d \n", melhor_vizinho_vnd1);
        if(melhor_vizinho_vnd1 < melhor){
            copiar = true;
            vnd1(melhor_vizinho_vnd1, copiar);
        }
    }
    
    
}

void vnd2(int melhor, bool copiar){
    int melhor_peso = 0;
    int item_leve = 1000;
    int treno_leve = 0;

    if(!copiar)
        copia_trenos(melhor);

    for(int i = 0;i<melhor;i++){
        if(trenos_aux1[i].itens == 1){
            if (trenos_aux1[i].qtd >= melhor_peso){
                if(trenos_aux1[i].array[0] < item_leve){
                    item_leve = trenos_aux1[i].array[0];
                    melhor_peso = trenos_aux1[i].qtd;
                    treno_leve = i;
                }
                 
            }
        }
        
    }
    bool troca = false;
    bool reincertion = false;
    bool inc = false;
    int pos_livre;
    int i = 0;
    while(troca == false && i < melhor){
        if(i==treno_leve){
            i++;
            continue;
        }

        for(int j=0;j<trenos_aux1[i].itens; j++){
            if(troca == true){
                break;
            } 

            if(trenos_aux1[i].array[j] == 1000){
                break;
            }

            for(int t=0; t<melhor; t++){
                if(reincertion == true && troca == false){
                    copia_trenos_vnd2(melhor);
                    reincertion = false;
                }

                if(t==treno_leve){
                    t++;
                    continue;
                }
                if(trenos_aux1[t].qtd < trenos_aux1[i].array[j]){
                    continue;
                }
                inc = false;
                for(int s=0;s< trenos_aux1[t].itens;s++){
                    if(lista[trenos_aux1[t].array_index[s]][trenos_aux1[i].array_index[j]]){
                        inc = true;
                        break;
                    }
                }
                if(!inc){
                    trenos_aux1[t].array[trenos_aux1[t].itens] = trenos_aux1[i].array[j];
                    trenos_aux1[t].array_index[trenos_aux1[t].itens] = trenos_aux1[i].array_index[j];
                    trenos_aux1[t].qtd -= trenos_aux1[t].array[trenos_aux1[t].itens];
                    trenos_aux1[t].itens++;

                    pos_livre = trenos_aux1[i].array_index[j];

                    trenos_aux1[i].array[j] = 1000;
                    trenos_aux1[i].array_index[j] = 100;
                    trenos_aux1[i].qtd += trenos_aux1[t].array[trenos_aux1[t].itens-1];
                    trenos_aux1[i].itens--;

                    reincertion = true;
                    
                    if(trenos_aux1[treno_leve].array[0] < trenos_aux1[i].qtd){
                        inc = false;
                        for(int s=0;s< trenos_aux1[i].itens;s++){
                            if(lista[trenos_aux1[treno_leve].array_index[0]][trenos_aux1[i].array_index[s]]){
                                inc = true;
                            }
                        }
                        if(!inc){
                            trenos_aux1[i].array[j] = trenos_aux1[treno_leve].array[0];
                            trenos_aux1[i].array_index[j] = pos_livre;
                            trenos_aux1[i].itens++;
                            trenos_aux1[treno_leve].itens = 0;
                            trenos_aux1[treno_leve].qtd += trenos_aux1[treno_leve].array[0];
                            trenos_aux1[treno_leve].array[0] = 1000;
                            trenos_aux1[treno_leve].array_index[0] = 100; 
                            troca = true;
                            break; 
                        }
                    }
                    

                }

            }
            
        }
        i++;
    }

    int melhor_vizinho_vnd2 = 0;
    for(int i=0;i<n_presentes;i++){
       if(trenos_aux1[i].itens == 0){
            continue;
       }

       for(int j=0;j<n_presentes;j++){
            if(trenos_aux1[i].array[j] == 1000)
                continue;
       }

       melhor_vizinho_vnd2++;
    }

    printf("Melhor vizinho VND2 = %d \n", melhor_vizinho_vnd2);
    if(melhor_vizinho_vnd2 < melhor){
        copiar = true;
        vnd2(melhor_vizinho_vnd2, copiar);
    }

    
}

int main(){
    double time_spent = 0.0;
    clock_t begin = clock();

    ReadInstance();
    ordena_presentes();
    inicializa_vetores();
    
    int melhor = 0;
    bool copiar = false;
    
    //auxiliar para o p
    int aux2 = N_PRESENTES;

    //auxiliar para posição vazia na sacola dos trenos
    int t_arm = 0;

    // For percorrendo os trenós
    for(int i=0;i<n_presentes; i++){

        // verifica se a capacidade trenos[i].array[t]dos trenos é igual a 0
        if(!trenos[i].qtd){
            continue;
        }

        // For percorrendo os presentes
        for(int p=aux2; p>0;p--){

            // flag para verificar incidencia da lista
            bool flag = false;

            // verifica se o peso do presente é maior que a capacidade do treno.
            if(trenos[i].qtd < array[p]){
                break;
            }
            
            // for percorrendo a sacola do treno
            for(int t=0; t<n_presentes;t++){
                
                // não houve ocorrencias
                flag = true;
                int aux = trenos[i].array_index[t];
                int verifica_vazia = trenos[i].array[t];
                // if true, posicao da sacola está vazia, podemos adicionar
                if(verifica_vazia == 1000){                  
                    t_arm = t;
                    aux2 = p-1;
                    break;
                }

                // if true, existe proibição do p na sacola do treno.
                if(lista[aux][p]){
                    flag = false;
                    aux2 = p;
                    break;
                }
                
            }

            if(!flag){
                break;
            }else{
                // Adiciona presente na sacola do treno em questão
                // Diminui o peso do presente na capacidade do treno
                // Soma +1 no numero de itens da sacola do treno
                trenos[i].array[t_arm] = array[p];
                trenos[i].qtd = trenos[i].qtd - array[p];
                trenos[i].array_index[trenos[i].itens] = p;
                trenos[i].itens++;

                i=-1;
                break;
            }            
        }
    }
    
    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("---------------- Algoritmo guloso -------------------\n");
    printf("\n---> Tempo gasto do algoritmo guloso: %f seconds \n", time_spent);

    for(int i=0;i<n_presentes;i++){
       if(trenos[i].itens == 0){
            continue;
       }

       melhor++;
    }
    printf("Resultado do algoritmo guloso foi que = %d trenós são necessários. \n\n", melhor);
    
    bool sair = false;
  
    while(!sair){
        printf("---------------- vnd1 -------------------\n\n");
        time_spent = 0;
        begin = clock();
        vnd1(melhor, copiar);
        end = clock();
        
        time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
        printf("---> Tempo gasto pelo vnd1 foi de %f segundos. \n\n", time_spent);

        if(melhor <= melhor_vizinho_vnd1){
            printf("---------------- vnd2 -------------------\n\n");
            time_spent = 0;
            begin = clock();
            copia_trenos_vnd2(melhor);
            vnd2(melhor, copiar);
            end = clock();

            time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
            printf("---> Tempo gasto pelo vnd2 foi de %f segundos. \n\n", time_spent);

        }

        sair = true;
    }
    
    return 0;
}