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
#include "Constructive.h"
#include "Local_Search.h"
#include "GA.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    int  b, c,g,o;
    if (argc < 5     || argc > 5)
      {
          printf("Parâmetros passados erroneamente. Por favor conferir arquivo readme\n");
          return 0;
      }
    
      // Converting string type to integer type
      // using function "atoi( argument)"
      b = atoi(argv[2]);//seed
      c = atoi(argv[3]);//tempo de execução
      o = atoi(argv[4]);//Conjunto ELite
    
    
    int elite=0, custoF=99999,turns=100,custo=0,cust[turns],bestSolLS=99999,Maxelite=o,system(const char *command),timetotal=0;
    char *path=(char*)malloc(100*sizeof(char)), *pathAre=(char*)malloc(100*sizeof(char));
    long timer;
    float alfa=0.2;
    edgelist bestelistLS;
    edgelist bestelistLSF;
    edgelist elist;//grafo inicial
    edgelist elistTemp;//grafo inicial
    edgelist elistMST;//grafo construção
    edgelist elistMSTPruned;//grafo construido pruned
    edgelist PR,Final;
    edgelist *vecedgelist=(edgelist*)malloc(Maxelite*sizeof(edgelist));
    pathAre=argv[1];
    elist.n=0;
    ler(&elist,pathAre);
    srand(b);
    printf("terminais: %d\n",terminals);
    printf("nodes: %d\n",n);
    printf("edges: %d\n",order);
    FILE *f = fopen(path, "w");
    clock_t CPU_time_1;
    clock_t CPU_time_2;
    clock_t CPU_time_3;
///////////////////////////////////// Construir Solução ////////////////////////////////
    CPU_time_3 = clock();
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
        printf("First Improvement from LS : %d\n", bestSolLS);
        printf("--------------------------------------------------------------------------\n");
        if (bestSolLS<custoF){
            copy_edgelist(&bestelistLSF,&Final);
            custoF=getCostEdgelist(&bestelistLSF);
        }
    ////////////////////////////////// Conjunto Elite ///////////////////////////////////////////
        printf("Starting Path Relinking\n");
        //printf("elite %d\n",elite);
        if (elite==0){
            Add2Elite(&bestelistLSF, &elist, Maxelite, vecedgelist,&elite,terminals);
        }else{
/////////////////////////////////// Path Relinking  ///////////////////////////////////////////////////////////
            DoPathRelinking(elist.n,elite,&elist,&PR,&bestelistLSF,terminals,tnodes,vecedgelist);
            if(conec(&PR, elist.n)==1){
                Add2Elite(&PR, &elist, Maxelite, vecedgelist,&elite,terminals);
                copy_edgelist(&PR, &Final);
            }
        }
        printf("\n");
        timer=clock()-CPU_time_2;
        timetotal=(float)(timer)/(float)1000;
    }
    timer=clock()-CPU_time_2;
    printf("CPU end time is for PR: %4.2f\n", (float)(timer)/(float)1000);
    
   
    timetotal=(float)(clock()-CPU_time_3)/(float)1000;
        
    printf("best sol %d\n",getCostEdgelist(&Final));
    printf("total time %f\n",(float)(timetotal)/(float)1000);
///////////////////////////// Melhor solução Geral ////////////////////////////////
    printEdgelist(&Final, 1);
    printf("\n");
    system("python SteinerGraph.py");
    
    
    return 0;
}
