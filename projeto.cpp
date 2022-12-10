#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

#define N_PRESENTES 30

using namespace std;

int k;
int n_presentes;
int q;
int n_elementos;
int array[N_PRESENTES];
int lista[100][100];
int melhor;

struct trenos {
    int array[N_PRESENTES];
    int array_index[N_PRESENTES];
    int itens;
    int qtd;
};

struct trenos trenos[N_PRESENTES];

int ReadInstance(){
    FILE *arq;

    arq = fopen("teste.txt", "r");
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
    }
    int aux1, aux2;
    for (int i=1; i <= n_elementos; i++){
        fscanf(arq, "%d ", &aux1);
        fscanf(arq, "%d\n", &aux2);

        lista[aux1][aux2]=1;
    }

    return 1;

}

void ordenavetor(){
    int i, j, aux; 
 
    for(i = 1; i < 40; i++){ 
        j = i; 
    
        while((j != 0) && (array[j] > array[j - 1])) { 
        aux = array[j]; 
        array[j] = array[j - 1]; 
        array[j - 1] = aux; 
        j--;
        } 
    }
}

void ordenavetor_vnd(){
    int troca;
    int copia;

    do {
        troca = 0;
        for(int i=0;i<melhor;i++){
            for(int j=0;i<N_PRESENTES;i++){
                if(trenos[i].array[j] > trenos[i].array[j+1]){
                    copia = trenos[i].array[j];
                    trenos[i].array[j] = trenos[i].array[j+1];
                    trenos[i].array[j+1] = copia;
                    troca = 1;

                }
            }
        }
    }while(troca);
    
    int i,j;
    for(i=0;i<n_presentes;i++){
        if(trenos[i].qtd == 150){
            continue;
        }
        for(j=0;j<n_presentes;j++){
            if(trenos[i].array[j] == 1000){
                break;
            }

            printf("trenos[%d].array[%d] = %d \n", i, j, trenos[i].array[j]);

        }
        printf("\n----------\n");
    }
        
}

void vnd_ordenado(){
    int melhor_vizinho = 0;
    bool incidencia = false;
    ordenavetor_vnd();
    while(melhor >= melhor_vizinho){
        melhor_vizinho = 0;
        for(int i=0;i<melhor;i++){
            // printf("i = %d, melhor = %d \n", i, melhor);
            // printf("Entrou no treno[%d] \n", i);
            for(int j=0;j<N_PRESENTES;j++){
                // printf("Verifica se posicao %d do treno[%d] é igual a 1000. \n", i, j);
                if(trenos[i].array[j] == 1000){
                    // printf("É igual a 1000, partindo para próxima posição");
                    continue;
                }
                    
                
                // printf("Posição %d não é igual a 1000, partindo para verificação dos outros trénos. \n", j);
                for(int t=0;t<melhor;t++){
                    // printf("Comparando com o treno[%d]\n", t);
                    if(t==i)
                        continue;

                    // printf("Comparando trenos[%d].array[%d] = %d com treno[%d] \n", i, j, trenos[i].array[j], t);
                    if(trenos[t].qtd >= trenos[i].array[j]){
                        // printf("Quantidade livre do treno[%d] é maior que o peso do presente = %d \n", t, trenos[i].array[j]);
                        for(int p=0;p<n_presentes;p++){
                            // printf("Verifica incidencias do presente %d com os presentes no treno[%d].posicao[%d]\n", trenos[i].array_index[j], t,p);
                            if(trenos[t].array[p] == 1000)
                                continue;

                            // printf("Verifica incidencia em lista[%d][%d]\n", trenos[t].array_index[p], trenos[i].array_index[j]);
                            if(lista[trenos[t].array_index[p]][trenos[i].array_index[j]]){
                                // printf("-> Encontrou incidencia.");
                                incidencia = true;
                                break;
                            }
                            // printf("Verifica incidencia em lista[%d][%d]\n", trenos[i].array_index[j], trenos[t].array_index[p]);
                            if(lista[trenos[i].array_index[j]][trenos[t].array_index[p]]){
                                // printf("-> Encontrou incidencia.");
                                incidencia = true;
                                break;
                            }    
                        }

                        if(!incidencia){
                            // printf("Não teve incidencia nos presentes, portando: \n");
                            // printf("Movendo presente do treno[%d].posicao[%d] com peso = %d para treno[%d].posicao[%d] \n", i,j,trenos[i].array[j], t, trenos[t].itens);
                            // printf("Trocando de trenó\n");
                            trenos[t].array[trenos[t].itens] = trenos[i].array[j];
                            // printf("Diminuindo peso. \n");
                            trenos[t].qtd -= trenos[i].array[j];
                            // printf("Modif. index\n");
                            trenos[t].array_index[trenos[t].itens] = trenos[i].array_index[j];
                            // printf("Aumentando número de itens\n");
                            trenos[t].itens++;

                            // printf("\nAumentando qtd treno abaixo\n");
                            trenos[i].qtd += trenos[i].array[j];
                            // printf("modif. index para 1000\n");
                            trenos[i].array_index[j] = 1000;
                            // printf("diminuindo itens\n");
                            trenos[i].itens--;
                            // printf("modif. array para 1000\n");
                            trenos[i].array[j] = 1000;
                            break;
                        }else{
                            // printf("Incidencia encontrada partindo para próximo trenó. \n");
                            incidencia = false;
                            continue;
                        }
                    }
                }        
            }
        }

        for(int i=0;i<n_presentes;i++){
            if(trenos[i].itens == 0){
                    continue;
            }

            // printf("trenos[%d] = %d --- peso rest: %d \n", i, trenos[i].itens, trenos[i].qtd);
            melhor_vizinho++;
        }

        printf("Melhor_vizinho = %d ---- Melhor resultado = %d \n", melhor_vizinho, melhor);        

    }

    printf("Melhor_vizinho = %d \n", melhor_vizinho);
    
}

void vnd1(){
    int melhor_vizinho = 0;
    bool incidencia = false;
    while(melhor > melhor_vizinho){
        for(int i=0;i<melhor;i++){
            for(int j=0;j<n_presentes;j++){
                if(trenos[i].array[j] == 1000)
                    continue;

                if(trenos[i+1].qtd > trenos[i].array[j]){
                    for(int s=0;s<n_presentes;s++){
                        if(trenos[i+1].array[s] == 1000)
                            continue;
                        
                        // printf("verifica inc. lista[%d][%d] \n", trenos[i+1].array_index[s],trenos[i].array_index[j]);
                        if(lista[trenos[i+1].array_index[s]][trenos[i].array_index[j]]){
                            incidencia = true;
                        }
                        if(lista[trenos[i].array_index[j]][trenos[i+1].array_index[s]]){
                            incidencia = true;
                        }
                    }

                    if(!incidencia){
                            printf("Movendo trenos[%d].presente[%d] = %d  para trenos[%d].presente[%d] \n\n",i, j, trenos[i].array[j], i+1, trenos[i+1].itens);
                            trenos[i+1].array[trenos[i+1].itens] = trenos[i].array[j];
                            trenos[i+1].qtd -= trenos[i].array[j];
                            trenos[i+1].array_index[trenos[i+1].itens] = trenos[i].array_index[j];
                            trenos[i+1].itens++;
                            trenos[i].qtd += trenos[i].array[j];
                            trenos[i].array_index[j] = 1000;
                            trenos[i].itens--;
                            trenos[i].array[j] = 1000;
                    }else{
                        incidencia = false;
                        continue;
                    }
                        
                        
                        
                }
            }
        }

        for(int i=0;i<n_presentes;i++){
            if(trenos[i].itens == 0){
                    continue;
            }

            printf("trenos[%d].itens = %d \n", i, trenos[i].itens);
            melhor_vizinho++;
        }

    }

    printf("Melhor_vizinho = %d \n", melhor_vizinho);
    
    // for(int i=0;i<n_presentes;i++){
    //     for(int j=0;j<n_presentes;j++){
    //         if(trenos[i].array[j] == 1000){
    //             continue;
    //         }

    //         printf("treno[%d].posicao[%d] = %d \n", i,j,trenos[i].array[j]);
    //     } 
    // }

    // for(int i=0;i<n_presentes;i++){
    //     for(int j=0;j<n_presentes;j++){
    //         if(trenos[i].array[j] == 1000){
    //             continue;
    //         }

    //         printf("treno[%d].posicao_index[%d] há o seguinte index de p = %d e peso = %d\n", i,j,trenos[i].array_index[j], trenos[i].array[j]);
    //     } 
    // }

}

int main(){
    ReadInstance();
    // ordenavetor();
    melhor = 0;
    //Adicionando peso para cada trenó
    for (int i=0; i<n_presentes;i++){
        trenos[i].qtd = q;
        trenos[i].itens = 0;

        // Inicializa sacola do treno com 100 em cada index.
        for(int j=0;j<n_presentes;j++){
            trenos[i].array[j] = 1000;
        }
    }

    //auxiliar para o p
    int aux2 = 1;

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
        for(int p=aux2; p<=n_presentes;p++){                
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
                    aux2 = p+1;
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

    
    int total = 0;
    for(int i=0;i<n_presentes;i++){
       if(trenos[i].itens == 0){
            continue;
       }
       
       melhor++;
       total = total + trenos[i].itens;
       printf("trenos[%d] = %d --- peso rest: %d \n", i, trenos[i].itens, trenos[i].qtd);
    }

    printf("total = %d \n", total);
    printf("Melhor resultado = %d \n", melhor);


    vnd_ordenado();

    printf("------------------------------\n");
    total = 0;
    for(int i=0;i<n_presentes;i++){
       if(trenos[i].itens == 0){
            continue;
       }
       
       total = total + trenos[i].itens;
       printf("trenos[%d] = %d --- peso rest: %d \n", i, trenos[i].itens, trenos[i].qtd);
    }

    printf("total = %d \n", total);
    return 0;
}