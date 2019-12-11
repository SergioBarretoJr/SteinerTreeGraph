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
    
    int  b, c;
    if (argc < 4 || argc > 4)
      {
          printf("Parâmetros passados erroneamente. Por favor conferir arquivo readme\n");
          return 0;
      }
    
      // Converting string type to integer type
      // using function "atoi( argument)"
      b = atoi(argv[2]);//seed
      c = atoi(argv[3]);//tempo de execução em milisegundos
    
    
    int elite=0, custoF=99999,turns=100,custo=0,cust[turns],bestSolLS=99999,system(const char *command),timetotal=0;
    char *path=(char*)malloc(100*sizeof(char)), *pathAre=(char*)malloc(100*sizeof(char));
    long timer=0;
    float alfa=0.2;
    edgelist bestelistLS;
    edgelist bestelistLSF;
    edgelist elist;//grafo inicial
    edgelist elistTemp;//grafo inicial
    edgelist elistMST;//grafo construção
    edgelist elistMSTPruned;//grafo construido pruned
    edgelist PR,Final;
    pathAre=argv[1];
    elist.n=0;
    ler(&elist,pathAre);
    srand(b);
    printf("terminais: %d\n",terminals);
    printf("nodes: %d\n",n);
    printf("edges: %d\n",order);
    clock_t CPU_time_1;
    clock_t CPU_time_2;
///////////////////////////////////// Construir Solução ////////////////////////////////
    CPU_time_2 = clock();
    while (timetotal<c){
        custo=0;
        InicializeCostDijkstra(n);
        for (int i=0;i<order;i++){
            buildCostDijkstra(elist.data[i].u, elist.data[i].v, elist.data[i].w);
        }
        sortVec(tnodes,terminals);
        
        for (int i=0;i<terminals;i++){
            AuxTerm[i]=tnodes[i];
        }
        printf("Iniciando Guloso\n");
        CPU_time_1 = clock();
        HeuristicaGulosaRand(alfa,terminals,AuxTerm,&elist,&elistMST,&elistTemp,&elistMSTPruned,tnodes,cost);
        int timeCons=clock()-CPU_time_1;
        custo=getCostEdgelist(&elistMSTPruned);
//////////////////////////////// Local Search ////////////////////////////////
        CPU_time_1 = clock();
        DoLocalSearch(&elist, &elistMSTPruned, &bestelistLSF, terminals, getCostEdgelist(&elistMSTPruned));
        timer=clock()-CPU_time_1;
        bestSolLS=getCostEdgelist(&bestelistLSF);
        printf("CPU end time is for Constructive: %4.2f\n", (float)(timeCons)/(float)1000);
        printf("CPU end time is for LS: %4.2f\n", (float)(timer)/(float)1000);
        printf("Constructive solution: %d\n", custo);
        printf("Improvement from LS : %d\n", bestSolLS);
        printf("--------------------------------------------------------------------------\n");
        if (bestSolLS<custoF){
            copy_edgelist(&bestelistLSF,&Final);
            custoF=getCostEdgelist(&bestelistLSF);
        }
        timer=clock()-CPU_time_2;
        timetotal=(float)(timer)/(float)1000;
    }
    printf("CPU end time is : %4.2f\n", (float)(timer)/(float)1000);
    printf("best sol %d\n",getCostEdgelist(&Final));
///////////////////////////// Melhor solução Geral ////////////////////////////////
    printEdgelist(&Final, 1);
    printf("\n");
    system("python SteinerGraph.py");
    return 0;
}
