#ifndef GRAFO_H
#define GRAFO_H

typedef struct graf graf;

graf* init_graf(int N);

void add_aresta_graf(graf* g, int id1, int id2);

void dfs(graf* g, FILE* tour);

void printa_adjacentes(graf * g);

void libera_graf(graf* g);


#endif 



