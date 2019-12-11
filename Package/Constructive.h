//
//  Dijkstra.h
//  GPU 2
//
//  Created by sergio junior on 03/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef Constructive_h
#define Constructive_h

#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Dijkstra.h"
#include "MSTP.h"
#include "Structure.h"
#include "ReadFile.h"
#include <time.h>
#include <stdlib.h>

void HeuristicaGulosaRand(float alfa, int terminais, int vec[],edgelist *elist,edgelist *edgelistMST, edgelist *elistTemp,edgelist *edgelistPruned,int tnodes[],int cost[][MAX]){
    int T=terminais,u=0,inicialnode=0;
    if (alfa<=0){
        u=0;
    }else{
        u=rand() % (terminais+1);
    }
    edgelistMST->n=0;
    inicialnode=vec[u];
    deletar(u,vec,T);
    T--;
    int next=0;
    while(T>0){
        
        next=FindNextTerminalRand(inicialnode,alfa,T);
        Pdijsktra(elist, edgelistMST,cost, inicialnode, next, n);
        u=GetIndex(next, T,vec);
        deletar(u,vec,T);
        T--;
        inicialnode=next;
    }
    MST(edgelistMST,elistTemp,edgelistPruned,tnodes);
}


#endif
