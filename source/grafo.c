

#include <stdio.h>
#include <stdlib.h>

#include "../include/grafo.h"

typedef struct vertice vertice;



struct vertice{
    int * adjacentes;
    int qtd;
    int size;
};


struct graf{
    vertice* vertices;
    int size;
    int constante;
};

static void libera_vertice(vertice * v){
    free(v->adjacentes);
    return ;
}

static void realloc_adjacentes(vertice * v, int constante){
    v->size += 10;
    v->adjacentes = (int*)realloc(v->adjacentes, sizeof(int)*(v->size));
}

static void init_vertice(vertice * vert){

    int size = 10;
    vert->adjacentes = (int*)malloc(sizeof(int)*(size));
    vert->size = size;
    vert->qtd =0;

    return ;
}

graf* init_graf(int N){
    graf* g = (graf*)malloc(sizeof(graf));
    g->size = N;
    g->vertices = (vertice*)malloc(sizeof(vertice)*N);

    for(int i =0; i < N; i ++){
        init_vertice(&g->vertices[i]);
    }
    
    if(N>=1000) g->constante = 1000;
    else g->constante = N;

    return g;
}

void add_aresta_graf(graf* g, int id1, int id2){
    id1--;
    id2--;
    vertice * aux1 = &g->vertices[id1];
    vertice * aux2 = &g->vertices[id2];

    aux1->qtd ++;
    if(aux1->qtd > aux1->size){
        realloc_adjacentes(aux1, g->constante);
    }
    aux1->adjacentes[aux1->qtd -1] = id2;

    aux2->qtd ++;
    if(aux2->qtd > aux2->size){
        realloc_adjacentes(aux2, g->constante);
    }
    aux2->adjacentes[aux2->qtd -1] = id1;

    return;

}

static void private_dfs(graf*g, int id, int* visitado, FILE * tour){
    visitado[id] =1 ;
    vertice * aux = &g->vertices[id];

    fprintf(tour,"%d\n", id + 1);

    for(int i =0; i < aux->qtd; i ++){
        int id_aux = aux->adjacentes[i];
        if( !visitado[id_aux] ){
            private_dfs(g, id_aux, visitado, tour);
        }
    }
}

void dfs(graf* g, FILE * tour){
    int * visitado = (int*)calloc(1, sizeof(int)*g->size);
    private_dfs(g, 0, visitado, tour);
    free(visitado);
}


void libera_graf(graf* g){
    for(int i =0; i < g->size; i ++){
        libera_vertice(&g->vertices[i]);
    }
    free(g->vertices);
    free(g);
}

void printa_adjacentes(graf * g){
    for(int i =0 ; i < g->size; i ++){
        vertice * aux = &g->vertices[i];
        printf("vertice : %d\n", i +1);
        for(int j =0 ; j < aux->qtd; j ++){
            printf("%d ", aux->adjacentes[j] + 1 );
        }
        puts("");
    }
}