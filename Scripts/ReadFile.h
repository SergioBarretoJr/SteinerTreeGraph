//
//  ReadFile.h
//  GPU 2
//
//  Created by sergio junior on 03/10/19.
//  Copyright © 2019 sergio junior. All rights reserved.
//

#ifndef ReadFile_h
#define ReadFile_h
#include<stdio.h>
#include<string.h>
#include<math.h>

int a2i(const char *s)
{
    int sign=1;
    if(*s == '-')
        sign = -1;
    s++;
    int num=0;
    while(*s)
    {
        num=((*s)-'0')+num*10;
        s++;
    }
    return num*sign;
}
char *ltrim(char *str, const char *seps)
{
    size_t totrim;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    totrim = strspn(str, seps);
    if (totrim > 0) {
        size_t len = strlen(str);
        if (totrim == len) {
            str[0] = '\0';
        }
        else {
            memmove(str, str + totrim, len + 1 - totrim);
        }
    }
    return str;
}
char *rtrim(char *str, const char *seps)
{
    int i;
    if (seps == NULL) {
        seps = "\t\n\v\f\r ";
    }
    i = (int)strlen(str) - 1;
    while (i >= 0 && strchr(seps, str[i]) != NULL) {
        str[i] = '\0';
        i--;
    }
    return str;
}
char *trim(char *str, const char *seps)
{
    return ltrim(rtrim(str, seps), seps);
}

void split_string(edgelist *elist, char* str){
    
    char delim[] = " ";
    char *temp[100000];
    char *ptr = strtok(str, delim);
    temp[0]=ptr;
    int i=1;
    
    while(ptr != NULL)
    {
        ptr = strtok(NULL, delim);
        if ((ptr) && (atoi(ptr))){
            temp[i]=ptr;
            i=i+1;
        }
    }
    //printf("i=%d - terminals=%d\n",i,terminals);
    if(i==2 && terminals==0){
        n=atoi(temp[0]);
        order=atoi(temp[1]);
    }
    else{
        if(i==3 && terminals==0){
            
            elist->data[elist->n].u=atoi(temp[0])-1;
            elist->data[elist->n].v=atoi(temp[1])-1;
            elist->data[elist->n].w=atoi(temp[2]);
            elist->n++;
            //printf("%d - //%d\t%d\t%d\n",elist.n-1,elist.data[elist.n-1].u+1,elist.data[elist.n-1].v+1,elist.data[elist.n-1].w);
        }
        else{
            if (i==1 && terminals==0){
                terminals=atoi(temp[0]);
                //printf("terminals=%d\n",terminals);
                
            }
            else{
                if (i>=terminals && terminals>0){
                    for (int h=0;h<terminals;h++){
                        tnodes[h]=atoi(temp[h])-1;
                    }
                }
            }
        }
    }
}

void ler(edgelist *elist, char* path){
    int i = 0;
    char* palavras[50000];
    char line[50000];
    FILE *arquivo;
    arquivo = fopen(path,"r");
    lines=1;
    if (arquivo){
        while(fgets(line, sizeof(line), arquivo) != NULL){
            palavras[i] = strdup(line);
            //printf("\n bruta %d - %s\n",i,palavras[i]);
            split_string(elist, trim(palavras[i],""));
        }
        fclose(arquivo);
    }
    else{
        printf("Erro ao abrir o arquivo %s", path);
    }
}


#endif /* ReadFile_h */
