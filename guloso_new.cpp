#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <time.h>   

#define N_PRESENTES 30

using namespace std;

int k;
int n_presentes;
int q;
int n_elementos;
int array[N_PRESENTES];
int array_index[N_PRESENTES];
int lista[N_PRESENTES][N_PRESENTES];

struct trenos {
    int array[N_PRESENTES];
    int array_index[N_PRESENTES];
    int itens;
    int qtd;
};

struct trenos trenos[N_PRESENTES];
struct trenos trenos_aux[N_PRESENTES];

int ReadInstance(){
    FILE *arq;

    arq = fopen("./instances/n30_k150_A.txt", "r");
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

        // Inicializa sacola do treno com 100 em cada index.
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
       for(int j=0;j<N_PRESENTES;j++){
            trenos_aux[i].array[j] = trenos[i].array[j];
            trenos_aux[i].array_index[j] = trenos[i].array_index[j]; 
       }
    }
}

void vnd1(int melhor, bool copiar){
    int melhor_vizinho = N_PRESENTES;
    bool inc = false;
    bool zerou = false;
    while(melhor < melhor_vizinho){
        melhor_vizinho = N_PRESENTES;

        for(int i=0;i<melhor;i++){
            if(zerou)
                break;

            if(!copiar){
               copia_trenos(melhor);
            }
            
            for(int j=0;j<N_PRESENTES;j++){
                if(trenos_aux[i].array[j] == 1000)
                    break;
                
                if(zerou){
                    printf("Zerou trenó \n");
                    break;
                }
                    
                for(int t=0;t<melhor;t++){
                    if(t==i)
                        continue;
                    
                    if(trenos_aux[t].itens == 0)
                        continue;
                    
                    inc = false;
                    // printf("Comparando trenos[%d].posicao[%d] com trenos[%d] \n", i, j, t);
                    // printf("Comparando capacidade do treno[%d] = %d com presente %d de peso %d\n", t, trenos_aux[t].qtd, trenos_aux[i].array_index[j], trenos_aux[i].array[j]);
                    if(trenos_aux[t].qtd >= trenos_aux[i].array[j]){
                        for(int s=0;s<N_PRESENTES;s++){
                            if(trenos_aux[t].array[s] == 1000)
                                break;
                            
                            if(lista[trenos_aux[t].array_index[s]][trenos_aux[i].array_index[j]]){
                                // printf("Teve inc. \n");
                                inc = true;
                                break;
                            }else if(lista[trenos_aux[i].array_index[j]][trenos_aux[t].array_index[s]]){
                                // printf("Teve inc. \n");
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
                            // printf("treno_aux[%d].itens = %d \n", i, trenos_aux[i].itens);
                            // printf("Troca posição %d do treno[%d] para o treno[%d] \n", j, i, t);

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
            melhor_vizinho--;
        }

        printf("Melhor vizinho = %d , melhor = %d \n", melhor_vizinho, melhor);
        if(melhor_vizinho < melhor){
            copiar = true;
            vnd1(melhor_vizinho, copiar);
        }
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
    
    // for(int i=1;i<N_PRESENTES;i++){
    //     printf("Posição [%d] com peso[%d] do array de presente com index %d \n",i, array[i], array_index[i]);
    // }
    
    //auxiliar para o p
    int aux2 = N_PRESENTES;

    //auxiliar para posição vazia na sacola dos trenos
    int t_arm = 0;

    // For percorrendo os trenós
    for(int i=0;i<n_presentes; i++){
        // printf("treno %d \n", i);

        // verifica se a capacidade trenos[i].array[t]dos trenos é igual a 0
        if(!trenos[i].qtd){
            // printf("quantidade treno[%d] = %d \n", i, trenos[i].qtd);
            continue;
        }

        // For percorrendo os presentes
        for(int p=aux2; p>0;p--){                
            // printf("entrou p = %d \n", p);

            // flag para verificar incidencia da lista
            bool flag = false;

            // verifica se o peso do presente é maior que a capacidade do treno.
            if(trenos[i].qtd < array[p]){
                break;
            }
            
            // for percorrendo a sacola do treno
            for(int t=0; t<n_presentes;t++){
                // printf("entrou treno[%d].posicao[%d] \n", i,t);
                
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
                // printf("Verifica incidencia na lista[%d][%d]\n", aux, p);
                if(lista[aux][p]){
                    // printf("--> ENCONTROU INCIDENCIA\n");
                    flag = false;
                    aux2 = p;
                    break;
                }
                
            }

            if(!flag){
                break;
            }else{
                // printf("entrou\n");
                // Adiciona presente na sacola do treno em questão
                // Diminui o peso do presente na capacidade do treno
                // Soma +1 no numero de itens da sacola do treno
                trenos[i].array[t_arm] = array[p];
                trenos[i].qtd = trenos[i].qtd - array[p];
                trenos[i].array_index[trenos[i].itens] = p;
                trenos[i].itens++;
                
                // printf("Adicionou um item ao treno[%d] com peso %d e posição em array[%d]. \n", i, array[p], p);
                // printf("numero de itens treno[%d] = %d \n", i, trenos[i].itens);

                i=-1;
                break;
            }            
        }
    }
    
    clock_t end = clock();

    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n\n ----> Tempo gasto do algoritmo guloso: %f seconds \n\n", time_spent);
    int total = 0;
    for(int i=0;i<n_presentes;i++){
       if(trenos[i].itens == 0){
            continue;
       }
    //    printf("trenos[%d].itens = %d \n", i, trenos[i].itens);
       melhor++;
       
       for(int j=0;j<N_PRESENTES;j++){
         if(trenos[i].array[j] == 1000)
            continue;

         total++;
       }
    }
    printf("total de presentes = %d \n", total);
    printf("Melhor resultado = %d \n", melhor);
    
    time_spent = 0;
    begin = clock();
    vnd1(melhor, copiar);
    end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\n\n ----> Tempo gasto pelo vnd1 = %f seconds \n\n", time_spent);
}