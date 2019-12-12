//
//  IntCompSteinerRand.c
//  GPU
//
//  Created by sergio junior on 04/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Dijkstra.h"
#include "MSTP.h"
#include "Structure.h"
#include "ReadFile.h"
#include "PathRelinking.h"
#include "Local_Search.h"
#include "GA.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    int  b, c,e,g,o;
    if (argc < 7 || argc > 7)
      {
          printf("Parâmetros passados erroneamente. Por favor conferir arquivo readme\n");
          return 0;
      }
    
      // Converting string type to integer type
      // using function "atoi( argument)"
      b = atoi(argv[2]);//seed
      c = atoi(argv[3]);//população
      e = atoi(argv[4]);//tempo de execução
      o =g = atoi(argv[6]);//prob mutação
    
    edgelist elistGA1,elistGA2;
    edgelist elistGA1t,elistGA2t;
    edgelist elistGA1S,elistGA2S;
    edgelist elist, final;//grafo inicial
    char *path=(char*)malloc(100*sizeof(char));
    char *pathAre=(char*)malloc(100*sizeof(char));
    pathAre=argv[1];
    elist.n=0;
    srand(b);
    long timetotals = 0;
    ler(&elist,pathAre);
    printf("\n");
    printf("terminais: %d\n",terminals);
    printf("nodes: %d\n",n);
    printf("edges: %d\n",order);
    clock_t CPU_time_2;
    int timetotal=0;
    int populacao=c;
    int vec[populacao][1000];
    int vecp1[1000];
    int vecp2[1000];
    int vec_custo[populacao][1];
    
    build_pop(&elist, order,n, vec, vec_custo,populacao, 0.2);
    int Min=999;
    for (int i=0;i<populacao;i++){
        //printf("custo %d\n",vec_custo[i][0]);
        if(vec_custo[i][0]<Min){
            Min=vec_custo[i][0];
        }
    }
    CPU_time_2 = clock();
    printf("best sol Inicial %d\n",Min);
    while(timetotals<e){
        //printf("inicio\n");
        int p1,p2;
        select_pais(&p1, &p2, populacao);
        //printf("seleção\n");
        int r=rand()%(n);
        cross_over(vecp1, vecp2, vec, n,r,p1,p2);
        //printf("cross\n");
        mutation(vecp1, o , n);
        //printf("mutação\n");
        mutation(vecp2, o, n);
        //printf("mutação\n");
        rebuildGraph(&elist, &elistGA1, vecp1,n,tnodes,terminals);
        rebuildGraph(&elist, &elistGA2, vecp2,n,tnodes,terminals);
        //printf("induzido\n");
        MST(&elistGA1, &elistGA1t, &elistGA1S, tnodes);
        MST(&elistGA2, &elistGA2t, &elistGA2S, tnodes);
        //printf("MST\n");
        if(num_terminais(&elistGA1S, terminals, tnodes)==terminals && num_terminais(&elistGA2S, terminals, tnodes)==terminals){
            
            add_cromo(vecp1, getCostEdgelist(&elistGA1S), vec, vec_custo, populacao, n);
            add_cromo(vecp2, getCostEdgelist(&elistGA2S), vec, vec_custo, populacao, n);
            //printf("added\n");
            timetotal++;
            timetotals=(float)(clock()-CPU_time_2)/(float)1000;
            //printf("inicio tttplot\n");
            if(g>0){
                int min=9999;
                for (int i=0;i<c;i++){
                    if (vec_custo[i][0]<min) {
                        min=vec_custo[i][0];
                    }
                    
                }
                if(min<=g){
                    //printf("tttplot ok\n");
                    int timer=(float)(clock()-CPU_time_2)/(float)1000;
                    fprintf(f, "%f\n",(float)(timer)/(float)1000);
                    break;
                }
            }
        }
        timetotals=(float)(clock()-CPU_time_2)/(float)1000;
    }
    
    int min=9999;
    for (int i=0;i<c;i++){
        if (vec_custo[i][0]<min) {
            min=vec_custo[i][0];
        }
    }
    printf("best solution %d",min);
    printf("\n");
    printf("total time %f\n",(float)(timetotals)/(float)1000);
    return 0;
}
