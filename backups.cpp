// #include <stdlib.h>
// #include <stdio.h>
// #include <math.h>
// #include <cstring>
// #include <iostream>

// using namespace std;

// int k;
// int n_presentes;
// int q;
// int n_elementos;
// int array[40];
// int lista[100][100];

// struct trenos {
//     int array[40];
//     int itens;
//     int qtd;
// };


// int ReadInstance(){
//     FILE *arq;

//     arq = fopen("teste.txt", "r");
//     if(!arq) {
//         puts("Não abriu");
//         return 0;
//     }

//     fscanf(arq, "%d\n", &n_presentes);
//     fscanf(arq, "%d\n", &k);
//     fscanf(arq, "%d\n", &q);
//     fscanf(arq, "%d\n", &n_elementos);

//     for (int i=0; i < n_presentes; i++){
//         fscanf(arq, "%d ", &array[i]);
//     }
//     int aux1, aux2;
//     for (int i=0; i < n_elementos; i++){
//         fscanf(arq, "%d ", &aux1);
//         fscanf(arq, "%d\n", &aux2);

//         lista[aux1][aux2]=1;
//     }

//     return 1;

// }

// int main(){
//     ReadInstance();

//     struct trenos trenos[40];

//     //Adicionando peso para cada trenó
//     for (int i=0; i<n_presentes;i++){
//         trenos[i].qtd = q;
//         trenos[i].itens = 0;

//         for(int j=0;j<n_presentes;j++){
//             trenos[i].array[j] = 100;
//         }
//     }

//     int aux2 = 0;
//     int t_arm = 0;
    
//     // For percorrendo os trenós
//     for(int i=0;i<n_presentes; i++){
//         printf("treno %d \n", i);
//         if(!trenos[i].qtd){
//             printf("quantidade treno[%d] = %d \n", i, trenos[i].qtd);
//             continue;
//         }

//         // For percorrendo os presentes
//         for(int p=aux2; p<n_presentes;p++){                
//             printf("entrou p = %d \n", p);
//             bool flag = false;
//             if(trenos[i].qtd < array[p]){
//                 break;
//             }
            
            
//             for(int t=0; t<n_presentes;t++){
//                 printf("entrou t = %d  \n", t);
                
//                 // não houve ocorrencias
//                 flag = true;
//                 int aux = trenos[i].array[t];
                
//                 if(aux == 100){                  
//                     t_arm = t;
//                     aux2 = p+1;
//                     break;
//                 }

//                 if(lista[aux][p]){
//                     flag = false;
//                     aux2 = p;
//                     break;
//                 }
                
//             }

//             if(!flag){
//                 break;
//             }else{
//                 printf("entrou\n");
//                 trenos[i].array[t_arm] = array[p];
//                 trenos[i].qtd = trenos[i].qtd - array[p];
//                 trenos[i].itens++;

//                 printf("numero de itens treno[%d] = %d \n", i, trenos[i].itens);

//                 i=-1;
//                 break;
//             }            
//         }
//     }


//     for(int i=0;i<n_presentes;i++){
//        if(trenos[i].itens == 0){
//             continue;
//        }

//        printf("trenos[%d] = %d \n", i, trenos[i].itens);

//     }
//     return 0;
// }