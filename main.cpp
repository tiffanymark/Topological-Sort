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

int size;
TDigraph * Init(int V);
TDigraph * insert(TDigraph *D, int v, int w);
void verifyCycle(TDigraph *D, int v, int *marked);
void printDigraph(TDigraph *D);
void topologicalSort(TDigraph *D);
void depthFirstSearch(TDigraph *D, int v, int *marked, int *sorting);
void printTopologicalSort(int *sort, int size);
FILE * readFile();
int tasksNumber();
void insertTasks(TDigraph *D);

int main(){

    size = tasksNumber();

    TDigraph *digraph;
    digraph = Init(size);

    insertTasks(digraph);

    printDigraph(digraph);

    topologicalSort(digraph);

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
    int *marked = (int*) calloc(D->V, sizeof(int)), index;

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

        for(index = 0; index < D->V; index++)
            marked[index] = 0;

        verifyCycle(D, w, marked);

        if(marked[v]){
            printf("Arc (%d,%d) forms cycle\n", v, w);
        }else {
            newN = (TNode *) calloc(1, sizeof(TNode));
            newN->w = w;
            newN->next = node;

            if (!prev) {
                D->adj[v] = newN;
            } else {
                prev->next = newN;
            }
            D->A++;
        }
    }
    return D;
}

void verifyCycle(TDigraph *D, int v, int *marked){
    marked[v] = 1;

    TNode *vertex;
    vertex = D->adj[v];

    while(vertex){
        if(!marked[vertex->w]){
            verifyCycle(D, vertex->w, marked);
        }
        vertex = vertex->next;
    }
}

void printDigraph(TDigraph *D){
    int index;
    for(index = 0; index < D->V; index++){
        TNode *vertex = D->adj[index];
        printf("%d ->", index);

        while(vertex){
            printf(" %d", vertex->w);
            vertex = vertex->next;
        }
        printf("\n");
    }
    printf("\n");
}

void topologicalSort(TDigraph *D){
    int *marked, *sort, v;
    marked = (int*) calloc(D->V, sizeof(int));
    sort = (int*) calloc(D->V, sizeof(int));

    for(v = 1; v < D->V; v++){
        if(!marked[v]){
            depthFirstSearch(D, v, marked, sort);
        }
    }
}

void depthFirstSearch(TDigraph *D, int v, int *marked, int *sort){
    marked[v] = 1;

    TNode *vertex;
    vertex = D->adj[v];

    while(vertex){
        if(!marked[vertex->w]){
            depthFirstSearch(D, vertex->w, marked, sort);
        }
        vertex = vertex->next;
    }

    sort[--size] = v;

    if(size == 1)
        printTopologicalSort(sort, D->V);

}

void printTopologicalSort(int *sort, int size){
    int index;

    for(index = 0; index < size; index++){
        printf("%d ", sort[index]);
    }
}

FILE * readFile(){
    FILE *file;
    file = fopen("D:\\Repository\\Topological-Sort\\tasks.txt", "r");

    if(file)
        return file;

    return NULL;
}

int tasksNumber(){
    FILE *file = readFile();

    if(file) {
        int number;

        fscanf(file, "%d", &number);

        fclose(file);

        return number;
    }
    else
        return 0;
}

void insertTasks(TDigraph *D){
    FILE *file = readFile();

    if(file) {
        char line[50];
        int tasks, count = 0, v, w;

        tasks = tasksNumber();

        while (fgets(line, sizeof(line), file) != NULL) {
            if (count > tasks) {
                fscanf(file, "%d %d", &v, &w);
                insert(D, v, w);
            }
            count++;
        }
        fclose(file);
    }
    else
        printf("Error, file not found");
}