//
//  Structure.h
//  GPU 2
//
//  Created by sergio junior on 03/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef Structure_h
#define Structure_h
#include "Structure.h"
#define MAX 2000

typedef struct edge
{
    int u,v,w;
}edge;

typedef struct edgelist
{
    edge data[MAX];
    int n;
}edgelist;

int AuxTerm[MAX];
int belongs[MAX],belong[MAX],belongtemp[MAX];
int n,lines=0,order=0,terminals=0,tnodes[MAX],j=0,sizebelongtemp=0;

int FindWeight (edgelist *elist, int source, int target){
    int w=0;
    for(int i=0;i<elist->n;i++){
        if((elist->data[i].u == source && elist->data[i].v == target) || (elist->data[i].v == source && elist->data[i].u == target) ){
            w=elist->data[i].w;
            break;
        }
    }
        return w;
}

int contemT2(int tnodes[],int a){
    int cont=0;
    for (int i=0; i<terminals; i++) {
        
        if (tnodes[i]==a){
            cont++;
            break;
        }
    }
    return cont;
}

void sortTerminal()
{
    int i,j;
    int temp;
    
    for(i=1;i<terminals;i++)
        for(j=0;j<terminals-1;j++)
            if(tnodes[j]>tnodes[j+1])
            {
                temp=tnodes[j];
                tnodes[j]=tnodes[j+1];
                tnodes[j+1]=temp;
            }
}

void sortVec(int vec[1000000], int size)
{
    int i,j;
    int temp;
    
    for(i=1;i<size;i++)
        for(j=0;j<size-1;j++)
            if(vec[j]>vec[j+1])
            {
                temp=vec[j];
                vec[j]=vec[j+1];
                vec[j+1]=temp;
            }
}


void sortterm(int w[][2],int size)
{
    int i,j;
    int temp[size][2];
    for(i=1;i<size;i++)
        for(j=0;j<size-1;j++)
            if(w[j][0]>w[j+1][0])
            {
                temp[j][0]=w[j][0];
        temp[j][1]=w[j][1];
                w[j][0]=w[j+1][0];
        w[j][1]=w[j+1][1];
                w[j+1][0]=temp[j][0];
        w[j+1][1]=temp[j][1];
            }
}

int GetIndex(int i, int size,int Auxt[100000]){
    int j=0;
    for (int h=0;h<size;h++){
        if (Auxt[h]==i){
            j=h;
            break;
        }
    }
    
    return j;
}

int get_nodes_solution(int vec[100000], edgelist *lista){
    int exist=0,h=0;
    for(int j=0;j<lista->n+1;j++){
        vec[j]=0;
        
    }
    
    for (int i=0;i<lista->n;i++){
        exist=0;
        for(int j=0;j<lista->n+1;j++){
            if(vec[j]==lista->data[i].u){
                exist++;
                break;
            }
        }
        if(exist==0){
            vec[h]=lista->data[i].u;
            h++;
        }
    }
    
    for (int i=0;i<lista->n;i++){
        exist=0;
        for(int j=0;j<lista->n+1;j++){
            if(vec[j]==lista->data[i].v){
                exist++;
                break;
            }
        }
        if(exist==0){
            vec[h]=lista->data[i].v;
            h++;
        }
    }
    return h;
}

int ContVertice(edgelist *elist,int no){
    //int vec[elist->n+1];
    //get_nodes_solution(vec,elist);
    int cont=0;
    for (int j=0; j<elist->n;j++){
        if (elist->data[j].u==no || elist->data[j].v==no){
            cont++;
        }
    }
    
    return cont;
}
int num_terminais(edgelist *g, int terminais,int tnodes[]){
    int cont=0;
    for (int j=0;j<terminais;j++){
            for (int i=0;i<g->n;i++){
                if ((g->data[i].u==tnodes[j]  || g->data[i].v==tnodes[j] )){
                    cont++;
                    break;
                }
            }
    }
        return cont;
    
}

int edges_in(edgelist *g, int u, int v){
    int cont=0;
    for (int i=0;i<g->n;i++){
        if ((g->data[i].u==u && g->data[i].v==v) || (g->data[i].u==v && g->data[i].v==u)){
            cont++;
            break;
        }
    }
    return cont;
}

#endif /* Structure_h */
