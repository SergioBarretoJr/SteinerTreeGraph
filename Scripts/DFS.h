//
//  DFS.h
//  GPU 2
//
//  Created by sergio junior on 01/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef DFS_h
#define DFS_h

#include <stdio.h>
#include <stdlib.h>
#include "Structure.h"

 
struct node
{
    int vertex;
    struct node* next;
};
struct node* createNode(int v);
struct Graph
{
    int numVertices;
    int* visited;
    struct node** adjLists; // we need int** to store a two dimensional array. Similary, we need struct node** to store an array of Linked lists
};

int DFS(struct Graph* graph, int vertex) {
    
    struct node* adjList = graph->adjLists[vertex];
    struct node* temp = adjList;
    int cont=0;
    graph->visited[vertex]=1;
    
    //printf("Visited %d - %d\n", vertex,graph->visited[vertex]);
    cont++;
    while(temp!=NULL) {
        int connectedVertex = temp->vertex;
    
        if(graph->visited[connectedVertex] == 0) {
            cont=cont+DFS(graph, connectedVertex);
        }
        temp = temp->next;
    }
    return cont;
}



struct node* createNode(int v)
{
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}
struct Graph* createGraph(int vertices)
{
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;
 
    graph->adjLists = malloc(vertices * sizeof(struct node*));
    
    graph->visited = malloc(vertices * sizeof(int));
 
    int i;
    for (i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}
 
void addEdge(struct Graph* graph, int src, int dest)
{
    // Add edge from src to dest
    struct node* newNode = createNode(dest);
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
 
    // Add edge from dest to src
    newNode = createNode(src);
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}
 
void printGraph(struct Graph* graph)
{
    int v;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        //printf("\n Adjacency list of vertex %d\n ", v);
        while (temp)
        {
            //printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        //printf("\n");
    }
}

int contemDFS(struct Graph* graph,int vertex){
    int v,cont=0;
    for (v = 0; v < graph->numVertices; v++)
    {
        struct node* temp = graph->adjLists[v];
        
        while (temp)
        {
            if(temp->vertex==vertex){
                cont++;
            }
            temp = temp->next;
        }
        
    }
    return cont;
}

#endif /* DFS_h */
