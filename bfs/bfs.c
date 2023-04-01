#include <stdio.h>
#include <stdlib.h>

int* dist;
int* pred;
int* color;

typedef struct node {
    int vertex;
    struct node* next;
} node;


typedef struct list {
    struct node* head;
} list;

typedef struct graph {
    int num_vertex;
    struct list* array;
} graph;


struct node* create_node(int n) {
    struct node* new_node = (node*) malloc(sizeof(node));
    new_node->vertex = n;
    new_node->next = NULL;
    return new_node;
}

struct graph* create_graph(int num_v) {
    struct graph* graph =  malloc(sizeof(graph));
    graph->num_vertex = num_v;
    graph->array = (list*) malloc(num_v * sizeof(list));

    for(int i = 0; i < num_v; ++i) {
        graph->array[i].head = NULL;
    }    
    return graph;
}

void create_edge(graph* graph, int u, int v) {

    struct node* temp = create_node(v);
    temp->next = graph->array[u].head;
    graph->array[u].head = temp;

    temp = create_node(u);
    temp->next = graph->array[v].head;
    graph->array[v].head = temp;
        
}

void bfs (graph* graph , int root, int* dist, int* pred, int* color) {
    int front = 0, rear = 0, v;
    int nv = graph->num_vertex;
    int* queue =  (int*) malloc(nv * sizeof(int));    
    for (int i = 0; i < nv; ++i) {
        dist[i] = 0;
        pred[i] = -1;
        color[i] = 0;
    }
    ++rear;
    queue[rear] = root;
    color[root] = 1;
    printf("\n\n");
    puts("FILA");
    for(int i = front + 1; i <= rear; ++i){
        printf("%d ", queue[i]);
    }
    printf("\n\n");    
    puts("COR");
    for(int i = 0; i < nv; ++i){
        printf("%d ", color[i]);
    }       
    printf("\n\n");
    puts("DISTANCIA");
    for(int i = 0; i < nv; ++i){
        printf("%d ", dist[i]);
    }
    printf("\n\n");
    puts("PREDECESSORES");
    for(int i = 0; i < nv; ++i){
        printf("%d ", pred[i]);
    }
    
    while(front != rear) {
        front = (front + 1) % nv;
        v = queue[front];
        node* temp = graph->array[v].head;
            
        while (temp != NULL) {
            if(color[temp->vertex] == 0) {
                rear = (rear + 1) % nv;
                queue[rear] = temp->vertex;
                dist[temp->vertex] = dist[v] + 1;
                pred[temp->vertex] = v;
                color[temp->vertex] = 1;
            }
            temp = temp->next;
        }
        color[v] = 2;
        printf("\n\n");
        puts("FILA");
        for(int i = front; i <= rear ; ++i){
            printf("%d ", queue[i]);
        }
        printf("\n\n");
        puts("COR");
        for(int i = 0; i < nv; ++i){
            printf("%d ", color[i]);
        }       
        printf("\n\n");
        puts("DISTANCIA");
        for(int i = 0; i < nv; ++i){
            printf("%d ", dist[i]);
        }
        printf("\n\n");
        puts("PREDECESSORES");
        for(int i = 0; i < nv; ++i){
            printf("%d ", pred[i]);
        }
    }
    free(queue);
}

void graph_print (graph* graph) {
    printf("\nLista de Ajdacencias\n");
    for(int i = 0; i < graph->num_vertex; ++i) {
        node* temp = graph->array[i].head;
       
        printf("[%d]", i);
        while (temp != NULL) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

int main (int argc, char* argv[]) {
    FILE* p_file;
    p_file = fopen(argv[1], "r");

    if (p_file == NULL) {
        puts("ERRO: Arquivo de entrada nao encontrado!");
        system("pause");
        exit(1);
    }

    int nv, ne, ini;
    int e1, e2;
    struct graph* graph;
    int flag = 1;
    char line [20];
    while (!feof(p_file)) {
        fgets (line, 20, p_file);

        if (flag) {
            sscanf (line, "%d %d %d", &nv, &ne, &ini);
            graph = create_graph (nv);
            --flag;
            continue;
        }

        sscanf (line, "%d %d", &e1, &e2);
        create_edge (graph, e1, e2);
    }
    fclose(p_file);    

    dist = (int *) malloc(nv * sizeof(int));
    pred = (int *) malloc(nv * sizeof(int));
    color = (int *) malloc(nv * sizeof(int));
    graph_print (graph);
    bfs (graph, ini, dist, pred, color);
    
      
  
    return 0;
}