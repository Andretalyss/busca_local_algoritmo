void copia_trenos(){
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


void vnd(){
    int melhor_vizinho = N_PRESENTES;
    bool inc = false;
    bool zerou = false;
    while(melhor < melhor_vizinho){
        melhor_vizinho = N_PRESENTES;

        for(int i=0;i<melhor;i++){
            if(zerou)
                break;

            copia_trenos();
            
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
                    
                    inc = false;
                    printf("Comparando trenos[%d].posicao[%d] com trenos[%d] \n", i, j, t);
                    printf("Comparando capacidade do treno[%d] = %d com presente %d de peso %d\n", t, trenos[t].qtd, trenos[i].array_index[j], trenos[i].array[j]);
                    if(trenos_aux[t].qtd >= trenos_aux[i].array[j]){
                        for(int s=0;s<N_PRESENTES;s++){
                            if(trenos_aux[t].array[s] == 1000)
                                break;
                            
                            if(lista[trenos_aux[t].array_index[s]][trenos_aux[i].array_index[j]]){
                                printf("Teve inc. \n");
                                inc = true;
                                break;
                            }else if(lista[trenos_aux[i].array_index[j]][trenos_aux[t].array_index[s]]){
                                printf("Teve inc. \n");
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
                            printf("treno_aux[%d].itens = %d \n", i, trenos_aux[i].itens);
                            printf("Troca posição %d do treno[%d] para o treno[%d] \n", j, i, t);

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
    }
    
    
}