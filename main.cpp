#include <stdio.h>
#include <stdlib.h>

typedef struct _TNode{
    int w;
    struct _TNode *next;
}TNode;

typedef struct{
    int V;
    int A;
    TNode **adj;
}TDigraph;


TDigraph * Init(int V);

int main(){

}


TDigraph * Init(int V){
    TDigraph *D;

    D = (TDigraph*) calloc(1, sizeof(TDigraph));
    D->V = V;
    D->A = 0;

    D->adj = (TNode**) calloc(D->V, sizeof(TNode*));

    return D;
}