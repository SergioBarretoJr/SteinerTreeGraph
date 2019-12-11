//
//  Dijkstra.h
//  GPU 2
//
//  Created by sergio junior on 03/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef PathRelinking_h
#define PathRelinking_h


#include <time.h>
#include <stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Dijkstra.h"
#include "MSTP.h"
#include "Structure.h"
#include "ReadFile.h"
#include "PathRelinking.h"
#include "Local_Search.h"
#include <time.h>
#include <stdlib.h>


void Intersection(edgelist *elist,edgelist *elistObj,edgelist *elistIntersect){
    elistIntersect->n=0;
    for(int i=0;i<elist->n;i++){
        for (int j=0;j<elistObj->n;j++){
            if (((elist->data[i].u==elistObj->data[j].u) && (elist->data[i].v==elistObj->data[j].v)) ||
                ((elist->data[i].u==elistObj->data[j].v) && (elist->data[i].v==elistObj->data[j].u))){
                elistIntersect->data[elistIntersect->n].u=elist->data[i].u;
                elistIntersect->data[elistIntersect->n].v=elist->data[i].v;
                elistIntersect->data[elistIntersect->n].w=elist->data[i].w;
                elistIntersect->n++;
                break;
                
            }
        }
    }
}

int edge_in(edge *elist,edgelist *elistObj){
    int cont=0;
    for (int j=0;j<elistObj->n;j++){
        if (((elist->u==elistObj->data[j].u) || (elist->u==elistObj->data[j].v))&&
            ((elist->v==elistObj->data[j].u) || (elist->v==elistObj->data[j].v))){
            cont++;
            break;
            
        }
    }
    return cont;
}

void add_edgePR(edgelist *elist,int src,int dest,int cost){
    
    elist->data[elist->n].u=src;
    elist->data[elist->n].v=dest;
    elist->data[elist->n].w=cost;
    elist->n++;
    
}

void change(edgelist *elist,int src,int dest,int cost,int srcb,int destb,int costb){
    for(int i=0;i<elist->n;i++){
        if (((elist->data[i].u==src) && (elist->data[i].v==dest)) ||
        ((elist->data[i].u==dest) && (elist->data[i].v==src))){
            elist->data[i].u=srcb;
            elist->data[i].v=destb;
            elist->data[i].w=costb;
        }
        
    }
}


void remove_edgePR(edgelist *elist,edgelist *elistcopy,int src,int dest,int cost){
    elistcopy->n=elist->n;
    for(int i=0;i<elist->n;i++){
        if (((elist->data[i].u==src) && (elist->data[i].v==dest)) ||
        ((elist->data[i].u==dest) && (elist->data[i].v==src))){
            
        }else{
            elistcopy->data[i].u=elist->data[i].u;
            elistcopy->data[i].v=elist->data[i].v;
            elistcopy->data[i].w=elist->data[i].w;
        }
    }
    
}

void copy_edgelist(edgelist *elist,edgelist *elist2){
    //printf("dest %d - origem %d\n",elist2->n,elist->n);
    
    elist2->n=elist->n;
    for(int i=0;i<elist2->n;i++){
        elist2->data[i].u=elist->data[i].u;
        elist2->data[i].v=elist->data[i].v;
        elist2->data[i].w=elist->data[i].w;
    }
}

void adjust_weight(edgelist *elist,int src,int dest,int cost){
    for(int i=0;i<elist->n;i++){
        if ((elist->data[i].u==src) && (elist->data[i].v==dest)){
            elist->data[i].w=cost;
        }
    }
}

int conec(edgelist *elistLSMSTPruned, int n){
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

int simetric_dif(edgelist *edlist,edgelist *edlist2){
    
    int cont=0;

    for (int i=0;i<edlist2->n;i++){
        for(int j=0;j<edlist->n;j++){
            if ((edlist2->data[i].u==edlist->data[j].u && edlist2->data[i].v==edlist->data[j].v) || (edlist2->data[i].u==edlist->data[j].v && edlist2->data[i].v==edlist->data[j].u)){
                   cont++;
            }
        }
    }
    
    return (edlist->n-cont);
}

int get_dif(edgelist *edlist,edgelist *edlist2, int dif[]){
    int cont=0,h=0;
    int nodes0[1000];
    int nodes1[1000];
    int n0=get_nodes_solution(nodes0,edlist);
    int n1=get_nodes_solution(nodes1,edlist2);
    
    for (int i=0;i<n1;i++){
        cont=0;
        for(int j=0;j<n0;j++){
            if (nodes1[i]==nodes0[j]){
                   cont++;
            }
        }
        if (cont==0){
            dif[h]=nodes1[i];
            h++;
        }
    }
    return h;
}

void PathRelinking (edgelist *elistG,edgelist *elist,edgelist *elistObj,edgelist *FinalPR, int tnodes[]){
    //printf("elist %d\t objective %d\n",getCostEdgelist(elist),getCostEdgelist(elistObj));
    int difI[1000];
    int difR[1000];
    int I=0,R=0,Min=9999, MinT=999;
    edgelist temp;
    edgelist temp0;
    edgelist temp1;
    edgelist temp2;
    edgelist temp3;
    edgelist tempI;
    edgelist temp2I;
    edgelist temp3I;
    copy_edgelist(elist,&temp1);
    //printf("elist inicial %d\n",elist->n);
    //printf("elist Objective %d\n",elistObj->n);
    //printf("elist Intersection %d\n",elistIntersect.n);
    //printf("delta temp -> Obj %d\n",simetric_dif(elistObj,&temp1));
    //printf("delta Obj -> temp %d\n",simetric_dif(&temp1,elistObj));
    //só tem no grafo objetivo
    I=get_dif(&temp1,elistObj,difI);
    //só tem no grafo inicial
    R=get_dif(elistObj,&temp1,difR);
    //printf("I %d\n",I);
    //printf("R %d\n",R);
    int iter=0;
    while((I!=0 || R!=0)&&iter<50){
        Min=9999;
        for (int i=0;i<R;i++){
            //printf("removing %d\n",difR[i]);
            drop_LS(elistG,&temp1, &temp, R,difR[i]);
            MST(&temp,&temp2,&temp3,tnodes);
            //printf("cost mst %d\n",getCostEdgelist(&temp3));
            //printf("Min %d\n",Min);
            if(getCostEdgelist(&temp3)<Min){
                Min=getCostEdgelist(&temp3);
                copy_edgelist(&temp3,&temp0);
                //printf("remove %d\n",difR[i]);
                //printf("Novo Min %d\n",Min);
            }
        }
        //printf("Min %d\n",Min);
        for (int i=0;i<I;i++){
            //printf("add %d\n",difI[i]);
            addEdges(elistG,&temp1, &tempI, R,difI[i]);
            MST(&tempI,&temp2I,&temp3I,tnodes);
            //printf("cost mst %d\n",getCostEdgelist(&temp3I));
            //printf("Min %d\n",Min);
            if(getCostEdgelist(&temp3I)<Min){
                Min=getCostEdgelist(&temp3I);
                copy_edgelist(&temp3I,&temp0);
                //printf("add %d\n",difI[i]);
                //printf("Novo Min %d\n",Min);
            }
        }
        //printf("best Min %d\n",Min);
        copy_edgelist(&temp0,&temp1);
        I=get_dif(&temp1,elistObj,difI);
        R=get_dif(elistObj,&temp1,difR);
        //printf("\n");
        //printf("I %d\n",I);
        //printf("R %d\n",R);
        iter++;
        if(getCostEdgelist(&temp0)<MinT){
            MinT=getCostEdgelist(&temp0);
            copy_edgelist(&temp0,FinalPR);
        }
        //printf("MinT %d\n",MinT);
    }
    if (iter>=50){
        copy_edgelist(elistObj,FinalPR);
    }
}



int max_f(edgelist edlist[],int Maxelite){
    
    int Max=-999, index=0;
        for (int i=0;i<Maxelite;i++){
            if (getCostEdgelist(&edlist[i])>Max){
                   Max=getCostEdgelist(&edlist[i]);
                    index=i;
            }
        }
    return Max;
}

int max_findece(edgelist edlist[],int Maxelite){
    
    int Max=-999, index=0;
        for (int i=0;i<Maxelite;i++){
            if (getCostEdgelist(&edlist[i])>Max){
                   Max=getCostEdgelist(&edlist[i]);
                    index=i;
            }
        }
    return index;
}


int get_best_PR_Solution(edgelist vecedgelist[], int Maxelite){
    int Min=999, index=0;
    for (int i=0;i<Maxelite;i++){
        if (getCostEdgelist(&vecedgelist[i])<Min &&getCostEdgelist(&vecedgelist[i])>0 ){
            Min=getCostEdgelist(&vecedgelist[i]);
            index=i;
        }
    }
    printf("Best cost solution GRASP + PathRelinking %d\n",Min);
    return Min;
}

void Add2Elite(edgelist *PR, edgelist *elist, int Maxelite, edgelist vecedgelist[], int *elite, int terminals ){
    edgelist temp;
    if (*elite==0){
        //printf("Iniciando conjunto elite\n");
        copy_edgelist(PR,&temp);
        vecedgelist[0]=temp;
        //printf("temp %d\n",getCostEdgelist(&temp));
        (*elite)++;
    }else{
        int index=0;
        int delta=0;
        //printf("teminais %d - %d\n",terminals,num_terminais(PR, terminals, tnodes));
        if(num_terminais(PR, terminals, tnodes)==terminals){
            if ((*elite)<Maxelite){
                delta=999;
                for (int i=0; i<(*elite);i++){
                    //int dif[1000];
                    //printf("delta %d\n",simetric_dif(PR,&vecedgelist[i]));
                    
                    if (delta>simetric_dif(PR,&vecedgelist[i])){
                        delta=simetric_dif(PR,&vecedgelist[i]);
                        index=i;
                    }
                }
                //printf("delta %d\n",delta);
                if(delta>0){
                    //printf("Add conjunto elite\n");
                    copy_edgelist(PR,&temp);
                    vecedgelist[(*elite)]=temp;
                    (*elite)++;
                }
            }else{
                int min_delta=9999,maxF=max_f(vecedgelist,(*elite));
                int index=0;
                for (int i=0; i<(*elite);i++){
                    //int dif[1000];
                     //printf("elite %d - %d",i,getCostEdgelist(&vecedgelist[i]));
                     if (min_delta>simetric_dif(PR,&vecedgelist[i])){
                        min_delta=simetric_dif(PR,&vecedgelist[i]);
                         index=i;
                    }
                 }
                //printf("min delta %d\n",min_delta);
                
                if(min_delta>0 && getCostEdgelist(PR)<maxF){
                    //printf("Add sub conjunto elite\n");
                    index=max_findece(vecedgelist,(*elite));
                    copy_edgelist(PR,&temp);
                    vecedgelist[index]=temp;
                }
            }
        }
    }
}

void DoPathRelinking(int n,int elite,edgelist *elist,edgelist *PR,edgelist *bestelistLS,int terminals,int tnodes[],edgelist vecedgelist[]){
    int in=0,lim_int=0, u=0;
    while(in!=1&&lim_int<50){
        u=rand() % elite;
        if(elite<2){
            u=0;
            break;
        }
        if(simetric_dif(&vecedgelist[u],bestelistLS)>0){
            in=1;
            break;
        }
        lim_int++;
    }
    edgelist *elistpathRelink=(edgelist*)malloc(sizeof(edgelist));
    if(getCostEdgelist(bestelistLS)>getCostEdgelist(&vecedgelist[u])){
        PathRelinking(elist,bestelistLS,&vecedgelist[u],elistpathRelink,tnodes);
    }else{
        PathRelinking(elist,&vecedgelist[u],bestelistLS,elistpathRelink,tnodes);
    }
    prune_tree(elistpathRelink, PR, tnodes);
}

#endif /* Dijkstra_h */
