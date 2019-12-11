//
//  Dijkstra.h
//  GPU 2
//
//  Created by sergio junior on 03/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef Local_Search_h
#define Local_Search_h

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
int conec2(edgelist *elistLSMSTPruned, int n){
    int aux=0;
    struct Graph* temps2= createGraph(n);
    if(elistLSMSTPruned->n>=1){
        for (int j=0;j<elistLSMSTPruned->n;j++){
            addEdge(temps2,elistLSMSTPruned->data[j].u,elistLSMSTPruned->data[j].v);
        }
        //conferir se a arvore eh conexa
        int dfs=DFS(temps2,elistLSMSTPruned->data[0].u);
        
        //printf("DFS edges: %d\tExpected: %d\n",dfs,elistLSMSTPruned->n+1);
        if (dfs==elistLSMSTPruned->n+1){
            aux=1;
        }
    }
    return aux;
}

void copy_edgelist2(edgelist *elist,edgelist *elist2){
    //printf("dest %d - origem %d\n",elist2->n,elist->n);
    
    elist2->n=elist->n;
    for(int i=0;i<elist2->n;i++){
        elist2->data[i].u=elist->data[i].u;
        elist2->data[i].v=elist->data[i].v;
        elist2->data[i].w=elist->data[i].w;
    }
}

void DoLocalSearch(edgelist *elist, edgelist *elistMSTPruned, edgelist*bestelistLS, int terminals, int bestSolLS){
    edgelist elistLSMST, temp,elistLSMSTPruned;
    int node_solutions[elist->n];
    int nelementos=get_nodes_solution(node_solutions,elistMSTPruned);
    int Cont_term[MAX][2];
    int improviment=0;
    int g=0;
    while (improviment<=0 && g<300){
        for (int i=0;i<terminals;i++){
            Cont_term[i][0]=tnodes[i];
            Cont_term[i][1]=0;
        }
        int no=get_rand_nodes(nelementos,node_solutions,terminals,tnodes);
        //printf("no %d\n",no);
        drop_LS(elist, elistMSTPruned,&temp, nelementos,no);
        
        MST(&temp,&elistLSMST,&elistLSMSTPruned,tnodes);
        int custoLS=0,aux=0;
        //custo da solucao alternativa da busca local
        for(int i=0;i<elistLSMSTPruned.n;i++)
        {
            custoLS=custoLS+elistLSMSTPruned.data[i].w;
        }
        aux=conec2(&elistLSMSTPruned,elist->n);
        int auxt=0;
        //conferir se os terminais estão na solucao
        for(int k=0;k<elistLSMSTPruned.n;k++){
            for (int t=0;t<terminals;t++){
                if(elistLSMSTPruned.data[k].u==Cont_term[t][0] && Cont_term[t][1]==0){
                    Cont_term[t][1]=1;
                    auxt++;
                }
                if(elistLSMSTPruned.data[k].v==Cont_term[t][0] && Cont_term[t][1]==0){
                    Cont_term[t][1]=1;
                    auxt++;
                }
            }
        }
        if(bestSolLS>custoLS && aux==1 && auxt==terminals){
            improviment++;
            bestSolLS=custoLS;
            copy_edgelist2(&elistLSMSTPruned, bestelistLS);
        }
        g++;
    }
    //printf("First Improvement from LS : %d\n", bestSolLS);
    //printf("--------------------------------------------------------------------------\n");
}
#endif
