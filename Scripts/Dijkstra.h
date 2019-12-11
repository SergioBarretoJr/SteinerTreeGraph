//
//  Dijkstra.h
//  GPU 2
//
//  Created by sergio junior on 03/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef Dijkstra_h
#define Dijkstra_h
#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Structure.h"
#include "MSTP.h"
#include "DFS.h"
#include <time.h>
#include <stdlib.h>



int cost[MAX][MAX],aleat=0,nextno[MAX],to_connect=0,k=0,u_rand[2]={0},u_r=0;
int costTerminal[MAX][MAX];


int DropDuplicated(edgelist *elist,int a, int b){
    int boo=0;
    for (int i=0;i<elist->n;i++){
        if ((a==elist->data[i].u && b==elist->data[i].v) || (a==elist->data[i].v && b==elist->data[i].u) ){
            boo=1;
            break;
        }
    }
    return boo;
}

int Ddijsktra(int cost[][MAX],int source,int target,int n)
{
    int N=n;
    int IN=999;
    int dist[N],prev[N],selected[100000]={0},i,m,min,start,d,j;
    for(i=0;i< N;i++)
    {
        
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0)
    {
        min = IN;
        m = 0;
        for(i=0;i< N;i++)
        {
            d = dist[start] +cost[start][i];
            if(d< dist[i] && selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    
    return dist[target];
}

void Pdijsktra(edgelist *elist,edgelist *spanlist, int cost[][MAX],int source,int target,int n)
{
    int N=n;
    int IN=MAX;
    int dist[N],prev[N],selected[3125]={0},i,m,min,start,d,j;
    int grafo[N];
    
    for(i=0;i< N;i++)
    {
        dist[i] = IN;
        prev[i] = -1;
    }
    start = source;
    selected[start]=1;
    dist[start] = 0;
    while(selected[target] ==0)
    {
        min = IN;
        m = 0;
        for(i=0;i< N;i++)
        {
            d = dist[start] +cost[start][i];
            if(d< dist[i] && selected[i]==0)
            {
                dist[i] = d;
                prev[i] = start;
            }
            if(min>dist[i] && selected[i]==0)
            {
                min = dist[i];
                m = i;
            }
        }
        start = m;
        selected[start] = 1;
    }
    start = target;
    j = 0;
    while(start != -1)
    {        
        //printf("-- %d -> ",start);
        grafo[j++] = start;
        start = prev[start];
    }
    
    for (int i=0;i<j-1;i++){
        if (DropDuplicated(spanlist, grafo[i], grafo[i+1])==0){
            spanlist->data[spanlist->n].u=grafo[i];
            spanlist->data[spanlist->n].v=grafo[i+1];
            spanlist->data[spanlist->n].w=FindWeight(elist,grafo[i], grafo[i+1]);
            spanlist->n++;
        }
    }
    
}

void InicializeCostDijkstra(int n){
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            cost[i][j]=MAX;
        }
    }
}

void buildCostDijkstra(int source, int target, int dist){
    cost [source][target] = dist;
    cost [target][source] = dist;
    
}

void buildCostTerminal(int source, int target, int dist){
    costTerminal [source][target] = dist;
    costTerminal [target][source] = dist;
    
}


int DistDijkstra(int source, int target,int n)
{
    int dist;
    
    dist = Ddijsktra(cost,source,target,n);
    return dist;
}

int min_cost(int w[MAX][2],int size){
    int min=MAX;
    for(int i=0; i<size;i++){
        if (w[i][0]<min){
            min=w[i][0];
        }
    }
    return min;
}
int max_cost(int w[MAX][2],int size){
    int max=0;
    for(int i=0; i<size;i++){
        if (w[i][0]>max && w[i][0]!=MAX){
            max=w[i][0];
        }
    }
    return max;
}
int Get_index(float alfa,int MatrixDist[MAX][2],int size){
    int index=0;
    int min=min_cost(MatrixDist,size),max=max_cost(MatrixDist,size),range=max-min;
    int lim=min+alfa*range;
    for(int i=0; i<size;i++){
        if (MatrixDist[i][0]<=lim){
            index=i;
        }
    }
    
    return index;
}

int FindNextTerminal(int u, int size, int Auxt[100000]){
    int next=0,dist=0;
    int Minimum=MAX;
    for ( int k=0;k<size;k++){
        if(Auxt[k]!=Auxt[u]){
            int src=Auxt[u],tgt=Auxt[k];
            dist=DistDijkstra(src, tgt,n);
            if(dist<Minimum){
                Minimum=dist;
                next=k;
            }
        }
    }
    
    return next;
}

int FindNextTerminalRand(int u,float alfa,int size){
    int next=0,index=0;
    int MatrixDist[MAX][2];
    
    for ( int k=0;k<size;k++){
        if(AuxTerm[k]!=u){
            MatrixDist[k][0]=DistDijkstra(u, AuxTerm[k],n);
            MatrixDist[k][1]=AuxTerm[k];
        }
    }
    
    sortterm(MatrixDist,size);
    if(alfa==0){
        index=0;
    }else{
        index=rand() % (Get_index(alfa,MatrixDist,size)+1);
    }
    next=MatrixDist[index][1];
    return next;
}


void deletar(int pos, int vec[100000], int size){
    int i=0;
    for(i=pos; i<size-1; i++)
    {
        vec[i] = vec[i + 1];
    }
}


int node_in(edgelist *elist, int a){
    int boo=0;
    for (int i=0;i<elist->n;i++){
        if ((a==elist->data[i].u) || (a==elist->data[i].v) ){
            boo=1;
            break;
        }
    }
    return boo;
}



void HeuristicaGulosaRand(float alfa, int terminais, int vec[],edgelist *elist,edgelist *edgelistMST, edgelist *elistTemp,edgelist *edgelistPruned,int tnodes[]){
    
    int T=terminais,u=0,inicialnode=0;
    //if (alfa<=0){
      //  u=0;
    //}else{
      //  u=rand() % (terminais+1);
        
    //}
    u=rand() % (terminais+1);
    edgelistMST->n=0;
    inicialnode=vec[u];
    deletar(u,vec,T);
    T--;
    int next=0;
    //printf("next %d\n",inicialnode);
    while(T>0){
        
        next=FindNextTerminalRand(inicialnode,alfa,T);
        //printf("next %d\n",next);
        Pdijsktra(elist, edgelistMST,cost, inicialnode, next, n);
        u=GetIndex(next, T,vec);
        deletar(u,vec,T);
        T--;
        inicialnode=next;
    }
    
    //printf("Guloso finalizado\n");
    //printf("Iniciando MST\n");
    MST(edgelistMST,elistTemp,edgelistPruned,tnodes);
    //printf("MST Finalizado %d\n",getCostEdgelist(edgelistPruned));
}

int get_rand_nodes(int nelementos,int nodes[100000],int term,int vec[100000]){
    int u=0;
    int check=0;
    int ct=0,rand_index=0;
    while(check==0 && ct<30000){
        rand_index=rand() % (nelementos+1);
        u=nodes[rand_index];
        check=1;
        for (int i=0;i<term;i++){
            if (vec[i]==u){
                check=0;
                break;
            }
        }
        k++;
        ct++;
    }
    return u;
}

void drop_LS(edgelist *elist,edgelist *elistMSTPruned, edgelist *temp, int nelementos,int no){
    temp->n=0;
    for(int i=0;i<elist->n;i++){
        if(node_in(elistMSTPruned,elist->data[i].u)>=1 && node_in(elistMSTPruned, elist->data[i].v)>=1 &&
           elist->data[i].u!=no && elist->data[i].v!=no){
            //printf("Adding drop u %d - v %d\n",elist->data[i].u,elist->data[i].v);
            temp->data[temp->n].u=elist->data[i].u;
            temp->data[temp->n].v=elist->data[i].v;
            temp->data[temp->n].w=elist->data[i].w;
            temp->n++;
        }
    }
}

void addEdges(edgelist *elist,edgelist *elistMSTPruned, edgelist *temp, int nelementos,int no){
    temp->n=0;
    for(int i=0;i<elist->n;i++){
        if(node_in(elistMSTPruned,elist->data[i].u)>=1 && node_in(elistMSTPruned, elist->data[i].v)>=1){
            //printf("Adding add u %d - v %d\n",elist->data[i].u,elist->data[i].v);
            temp->data[temp->n].u=elist->data[i].u;
            temp->data[temp->n].v=elist->data[i].v;
            temp->data[temp->n].w=elist->data[i].w;
            temp->n++;
        }else{
            if((elist->data[i].u==no && node_in(elistMSTPruned,elist->data[i].v)>=1) ||(elist->data[i].v==no && node_in(elistMSTPruned,elist->data[i].u)>=1 )){
                temp->data[temp->n].u=elist->data[i].u;
                temp->data[temp->n].v=elist->data[i].v;
                temp->data[temp->n].w=elist->data[i].w;
                temp->n++;
            }
        }
    }
}

void graph_induce(edgelist *elist,edgelist *elistMSTPruned){
    for(int i=0;i<elist->n;i++){
        if(node_in(elistMSTPruned,elist->data[i].u)>=1 && node_in(elistMSTPruned, elist->data[i].v)>=1 && edges_in(elistMSTPruned,elist->data[i].u,elist->data[i].v)==0){
            elistMSTPruned->data[elistMSTPruned->n].u=elist->data[i].u;
            elistMSTPruned->data[elistMSTPruned->n].v=elist->data[i].v;
            elistMSTPruned->data[elistMSTPruned->n].w=elist->data[i].w;
            elistMSTPruned->n++;
        }
    }
}
int in_vector(int nodes[], int x, int nelementos){
    int cont=0;
    for(int i=0;i<nelementos;i++){
        if(nodes[i]==x){
            cont++;
            break;
        }
    }
    return cont;
}
int bit_in(int nodes[], int x, int nelementos){
    int cont=0;
    for(int i=0;i<nelementos;i++){
        if(nodes[i]==1){
            cont++;
            break;
        }
    }
    return cont;
}
void rebuildGraph(edgelist *elist,edgelist *output, int nodes[],int nos, int tnodes[],int terminals){
    output->n=0;
    //printf("\nterminals - ");
    for (int i=0;i<terminals;i++){
        //printf(" %d ",tnodes[i]);
        nodes[tnodes[i]]=1;
    }
    //printf("\n");
    for(int i=0;i<elist->n;i++){
        //printf("u %d - v %d -> w %d\n",elist->data[i].u,elist->data[i].v,elist->data[i].w);
        if(nodes[elist->data[i].u]==1 && nodes[elist->data[i].v]==1){
            output->data[output->n].u=elist->data[i].u;
            output->data[output->n].v=elist->data[i].v;
            output->data[output->n].w=elist->data[i].w;
            //printf("add u %d - v %d -> w %d\n",elist->data[i].u,elist->data[i].v,elist->data[i].w);
            output->n++;
        }
    }
}
#endif
