#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cstring>
#include <iostream>

#define N_PRESENTES 40

using namespace std;

int k;
int n_presentes;
int q;
int n_elementos;
int array[N_PRESENTES];
int lista[100][100];

struct trenos {
    int array[N_PRESENTES];
    int itens;
    int qtd;
};


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

    for (int i=0; i < n_presentes; i++){
        fscanf(arq, "%d ", &array[i]);
    }
    int aux1, aux2;
    for (int i=0; i < n_elementos; i++){
        fscanf(arq, "%d ", &aux1);
        fscanf(arq, "%d\n", &aux2);

        lista[aux1][aux2]=1;
    }

    return 1;

}

int main(){
    ReadInstance();

    struct trenos trenos[N_PRESENTES];

    //Adicionando peso para cada trenó
    for (int i=0; i<n_presentes;i++){
        trenos[i].qtd = q;
        trenos[i].itens = 0;

        // Inicializa sacola do treno com 100 em cada index.
        for(int j=0;j<n_presentes;j++){
            trenos[i].array[j] = 100;
        }
    }

    //auxiliar para o p
    int aux2 = 0;

    //auxiliar para posição vazia na sacola dos trenos
    int t_arm = 0;

    // For percorrendo os trenós
    for(int i=0;i<n_presentes; i++){
        printf("treno %d \n", i);

        // verifica se a capacidade dos trenos é igual a 0
        if(!trenos[i].qtd){
            printf("quantidade treno[%d] = %d \n", i, trenos[i].qtd);
            continue;
        }

        // For percorrendo os presentes
        for(int p=aux2; p<n_presentes;p++){                
            printf("entrou p = %d \n", p);

            // flag para verificar incidencia da lista
            bool flag = false;

            // verifica se o peso do presente é maior que a capacidade do treno.
            if(trenos[i].qtd < array[p]){
                break;
            }
            
            // for percorrendo a sacola do treno
            for(int t=0; t<n_presentes;t++){
                printf("entrou t = %d  \n", t);
                
                // não houve ocorrencias
                flag = true;
                int aux = trenos[i].array[t];
                
                // if true, posicao da sacola está vazia, podemos adicionar
                if(aux == 100){                  
                    t_arm = t;
                    aux2 = p+1;
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
                printf("entrou\n");


                // Adiciona presente na sacola do treno em questão
                // Diminui o peso do presente na capacidade do treno
                // Soma +1 no numero de itens da sacola do treno
                trenos[i].array[t_arm] = array[p];
                trenos[i].qtd = trenos[i].qtd - array[p];
                trenos[i].itens++;

                printf("numero de itens treno[%d] = %d \n", i, trenos[i].itens);

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
       
       total = total + trenos[i].itens;
       printf("trenos[%d] = %d \n", i, trenos[i].itens);

    }

    printf("total = %d \n", total);

    return 0;
}