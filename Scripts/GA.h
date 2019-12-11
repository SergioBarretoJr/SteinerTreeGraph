
#ifndef GA_h
#define GA_h
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

void cromossomo(edgelist *elist, int vec[], int n){
    int vecn[1000];
    int vertices=0;
    vertices=get_nodes_solution(vecn, elist);
    for (int i=0;i<n;i++){
        vec[i]=0;
    }
    
    
    for (int j=0;j<vertices;j++){
        vec[vecn[j]]=1;
    }
}

void print_cromossomoI(int index,int vec[][1000],int vec_custo[][1],int populacao, int nos){
    printf("\n\n");
    printf("Cromossomo %d - ",index);
    for (int j=0;j<nos;j++){
        printf(" %d ",vec[index][j]);
    }
    printf("custo %d ",vec_custo[index][0]);
    printf("\n\n");
}

void print_cromossomo2(int index,int vec[1000],int vec_custo[][1],int populacao, int nos){
    printf("\n\n");
    printf("Cromossomo %d - ",index);
    for (int j=0;j<nos;j++){
        printf(" %d ",vec[j]);
    }
    printf("custo %d ",vec_custo[index][0]);
    printf("\n\n");
}

void build_pop(edgelist *elist, int order, int nos,int vec[][1000],int vec_custo[100][1], int n, float alfa){
    edgelist elistTemp;//grafo inicial
    edgelist elistMST;//grafo construção
    edgelist elistMSTPruned;//grafo construido pruned
    printf("Utilizando alfa %4.2f\n",alfa);
    int j=0;
    elistMSTPruned.n=0;
    int vec_nodes[1000];
    for (j=0;j<n;j++){
        
        int custo=0;
        InicializeCostDijkstra(nos);
        for (int i=0;i<order;i++){
            buildCostDijkstra(elist->data[i].u, elist->data[i].v, elist->data[i].w);
        }
        sortVec(tnodes,terminals);
        
        for (int i=0;i<terminals;i++){
            AuxTerm[i]=tnodes[i];
        }
        HeuristicaGulosaRand(alfa,terminals,AuxTerm,elist,&elistMST,&elistTemp,&elistMSTPruned,tnodes);
        for(int i=0;i<elistMSTPruned.n;i++)
        {
            custo=custo+elistMSTPruned.data[i].w;
        }
       
        
        /*int aux=0,vecaux[1000];
        aux=get_nodes_solution(vecaux, &elistMSTPruned);
        for(int i=0;i<aux;i++){
            printf(" %d ",vecaux[i]);
        }
        printf("\n");*/
        //if(num_terminais(&elistMSTPruned, terminals, tnodes)==terminals){
        cromossomo(&elistMSTPruned, vec_nodes, n);
        
        //printf("cromo %d - ",j);
        for (int i=0;i<nos;i++){
            vec[j][i]=vec_nodes[i];
            //printf(" %d ",vec_nodes[i]);
        }
        //printf("\n");
            
            
            vec_custo[j][0]=custo;
        //}
    }
}

void sort_pop(int vec[][1000],int vec_custo[][1], int n, int nos){
    int i,j;
    int temp=0, temp2=0;;
    for(i=1;i<n;i++)
        for(j=0;j<n-1;j++)
            if(vec_custo[j][0]>vec_custo[j+1][0])
            {
                temp=vec_custo[j][0];
                vec_custo[j][0]=vec_custo[j+1][0];
                vec_custo[j+1][0]=temp;
                for(int k=0;k<nos;k++){
                    temp2=vec[j][k];
                    vec[j][k]=vec[j+1][k];
                    vec[j+1][k]=temp2;
                }
            }
}
void Delete_cromo(int pos, int vec[][1]){
    vec[pos][0]=999;
}

void select_pais(int *i, int *j, int n){
    (*i)=0;
    (*j)=0;
    while((*i)==(*j)){
        (*i)=rand()%(n);
        (*j)=rand()%(n);
        //(*j)=(rand() % (n - (int)(n*95) + 1)) + (int)(n*95)-2;
    }
}

void cross_over(int vecp1[],int vecp2[],int vec[][1000], int nos,int r, int p1, int p2){
    for(int k=0;k<r;k++){
        vecp1[k]=vec[p1][k];
        vecp2[k]=vec[p2][k];
    }
    for(int k=r;k<nos;k++){
        vecp1[k]=vec[p2][k];
        vecp2[k]=vec[p1][k];
    }
}
void add_cromo(int vecp1[],int cost,int vec[][1000], int vec_cost[][1], int pop, int n){
    for (int i=0;i<pop;i++){
        if(vec_cost[i][0]>cost){
            vec_cost[i][0]=cost;
            for (int j=0;j<n;j++){
                vec[i][j]=vecp1[j];
            }
            break;
        }
    }
}

void print_cromossomos(int vec[][1000],int vec_custo[][1],int populacao, int nos){
    printf("\n\n");
    for(int i=0;i<populacao;i++){
        printf("Cromossomo %d - ",i);
        for (int j=0;j<nos;j++){
            printf(" %d ",vec[i][j]);
        }
        printf("custo %d ",vec_custo[i][0]);
        printf("\n\n");
    }
}



void mutation(int vec[],float prob, int nos){
    double ale= (double)rand() / (double)RAND_MAX;
    //printf("ale %4.2f\n",ale);
    //printf("ale %4.2f\n",prob);
    int index=0,index2=0;
    if (ale<prob){
        while(1){
            index=rand()%(nos+1);
            if (nos-index>nos*0.1 && index<terminals){
                break;
            }
            
        }
        index2=index+nos*0.1;
        //printf("index %d index2 %d\n", index,index2);
        for (int i=0;i<nos;i++){
            if(i>=index && i<=index2){
                if (vec[i]==0){
                    vec[i]=1;
                }else{
                    vec[i]=0;
                }
            }
        }
    }
}

void show_nodes(int vec[][1000], int nos, int index){
    for (int i=0;i<nos;i++){
        if(vec[index][i]==1){
            printf(" %d ",i);
        }
    }
    printf("\n");
}
void show_nodes2(int vec[1000], int nos){
    for (int i=0;i<nos;i++){
        if(vec[i]==1){
            printf(" %d ",i);
        }
    }
    printf("\n");
}
#endif
