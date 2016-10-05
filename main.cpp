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
TDigraph * insert(TDigraph *D, int v, int w);

int main(){

    TDigraph *digraph;
    digraph = Init(7);

    insert(digraph, 0, 1);
    insert(digraph, 0, 2);
    insert(digraph, 1, 2);
    insert(digraph, 1, 4);
    insert(digraph, 2, 3);
    insert(digraph, 3, 5);
    insert(digraph, 3, 6);
    insert(digraph, 4, 5);
    insert(digraph, 6, 6);
    insert(digraph, 5, 6);
    insert(digraph, 5, 6);

}


TDigraph * Init(int V){
    TDigraph *D;

    D = (TDigraph*) calloc(1, sizeof(TDigraph));
    D->V = V;
    D->A = 0;

    D->adj = (TNode**) calloc(D->V, sizeof(TNode*));

    return D;
}


TDigraph * insert(TDigraph *D, int v, int w){
    TNode *newN, *prev, *node;

    prev = NULL;
    node = D->adj[v];

    while(node && node->w < w){
        prev = node;
        node = node->next;
    }

    if(v == w){
        printf("v(%d) and w(%d) must be different\n", v , w);

    } else if(node && node->w == w){
        printf("Arc (%d,%d) already inserted\n", v, w);

    } else{
        newN = (TNode*) calloc(1, sizeof(TNode));
        newN->w = w;
        newN->next = node;

        if(!prev){
            D->adj[v] = newN;
        }else{
            prev->next = newN;
        }
        D->A++;
    }
    printf("\n");

    return D;
}

