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
// int array[30];
// int lista[100][100];

// struct trenos {
//     int array[30];
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

//     struct trenos trenos[30];

//     // printf(" k = %d \n n_presentes = %d \n q = %d \n n_elementos = %d \n", k, n_presentes, q, n_elementos);
    
//     // for (int i=0; i<n_presentes; i++){
//     //     printf("array[%d] = %d \n", i, array[i]);
//     // }

//     // for(int i=1; i<=n_presentes;i++){
//     //     for(int k=1; k<=n_presentes; k++){
//     //         printf("lista[%d][%d] = %d \n", i, k, lista[i][k]);
//     //     }
//     // }

    
//     return 0;
// }