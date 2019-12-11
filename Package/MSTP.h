//
//  MSTP.h
//  GPU 2
//
//  Created by sergio junior on 03/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef MSTP_h
#define MSTP_h

#include<stdio.h>
#include<time.h>
#include <stdlib.h>
#include <string.h>
#include "Structure.h"
#include "Dijkstra.h"

void copy_edgelist1(edgelist *elist,edgelist *elist2){
    //printf("dest %d - origem %d\n",elist2->n,elist->n);
    
    elist2->n=elist->n;
    for(int i=0;i<elist2->n;i++){
        elist2->data[i].u=elist->data[i].u;
        elist2->data[i].v=elist->data[i].v;
        elist2->data[i].w=elist->data[i].w;
    }
}

int find(int belongs[],int vertexno)
{
    return(belongs[vertexno]);
}

void union1(int belongs[],int c1,int c2)
{
    int i;
    
    for(i=0;i<n;i++)
        if(belongs[i]==c2)
            belongs[i]=c1;
}

void sort(edgelist *spanlist)
{
    int i,j;
    edge temp;
    
    for(i=1;i<spanlist->n;i++)
        for(j=0;j<spanlist->n-1;j++)
            if(spanlist->data[j].w>spanlist->data[j+1].w)
            {
                temp=spanlist->data[j];
                spanlist->data[j]=spanlist->data[j+1];
                spanlist->data[j+1]=temp;
            }
}


void printEdgelist(edgelist *elist,int save)
{
    printf("print tree\n");
    int i;
    char *path=(char*)malloc(100*sizeof(char));
    path= "Solution.txt";
    FILE *f = fopen(path, "w");
    for(i=0;i<elist->n;i++)
    {
        printf("\n%d\t%d\t%d",elist->data[i].u,elist->data[i].v,elist->data[i].w);
        if (save==1){
            fprintf(f, "%d\t%d\t%d\n",elist->data[i].u,elist->data[i].v,elist->data[i].w);
        }
    }
    fclose(f);
}

int getCostEdgelist(edgelist *elist)
{
    int cost=0;
    int i;
    for(i=0;i<elist->n;i++)
    {
        cost=cost+elist->data[i].w;
    }
    return cost;
}
int Contem(int vec[], int a, int sizes){
    int boo=0;
    for (int i=0;i<sizes;i++){
        if (vec[i]==a){
            boo=1;
            break;
        }
    }
    return boo;
}

void prune_tree(edgelist *elist,edgelist *elistout,int tnodes[100000]){
    elistout->n=0;
    int vec[elist->n];
    int vertices=get_nodes_solution(vec,elist),aux[10000][1];
    for (int i=0;i<vertices;i++){
        int cont=0;
        for (int j=0;j<elist->n;j++){
            if (elist->data[j].u==vec[i] || elist->data[i].v==vec[i]){
                cont++;
            }
        }
        aux[vec[i]][0]=cont;
    }
    for (int i=0;i<terminals;i++){
        aux[tnodes[i]][0]=10;
    }
    for (int i=0;i<elist->n;i++){
        if (aux[elist->data[i].u][0]==1 || aux[elist->data[i].v][0]==1){
        }else{
            elistout->data[elistout->n].u=elist->data[i].u;
            elistout->data[elistout->n].v=elist->data[i].v;
            elistout->data[elistout->n].w=elist->data[i].w;
            elistout->n++;
        }
    }
}


void MST(edgelist *elist,edgelist *elistout,edgelist *edgelistpruned,int tnodes[100000])
{
    int i,cno1,cno2;
    elistout->n=0;
    sort(elist);
    for ( i=0;i<n;i++){
        belongs[i]=i;
    }
    for (i=0;i<elist->n;i++) {
        cno1=find(belongs,elist->data[i].u);
        cno2=find(belongs,elist->data[i].v);
        if(cno1!=cno2)
        {
            elistout->data[elistout->n]=elist->data[i];
            elistout->n=elistout->n+1;
            union1(belongs,cno1,cno2);
        }
    }
    copy_edgelist1(elistout, edgelistpruned);
}

void MST_sPrune(edgelist *elist,edgelist *elistout,int tnodes[100000])
{
    int i,cno1,cno2;
    elistout->n=0;
    sort(elist);
    for ( i=0;i<n;i++){
        belongs[i]=i;
    }
    for (i=0;i<elist->n;i++) {
        cno1=find(belongs,elist->data[i].u);
        cno2=find(belongs,elist->data[i].v);
        if(cno1!=cno2)
        {
            elistout->data[elistout->n]=elist->data[i];
            elistout->n=elistout->n+1;
            union1(belongs,cno1,cno2);
        }
    }
}
#endif /* MSTP_h */
