#include <stdio.h>
#include <stdlib.h>

int* color;
int* d;
int* c;
int* pred;
int time = 0;

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


void dfs (graph* graph, int ini, int* color, int* d, int* c, int* pred) {
    time = time + 1;
    color[ini] = 1;    
    d[ini] = time;
    puts("");
    puts("Descobrimento");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", d[i]);
    }
    puts("");
    puts("Fechamento");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", c[i]);
    }
    puts("");
    puts("Predecessores");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", pred[i]);
    }
    puts("");
    puts("Cor");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", color[i]);
    }

    node* temp = graph->array[ini].head;
    while (temp != NULL) {
        if(color[temp->vertex] == 0) {
            pred[temp->vertex] = ini;            
            dfs(graph, temp->vertex, color, d, c, pred);
        }
        temp = temp->next;
    }
    color[ini] = 2;
    time = time + 1;
    c[ini] = time;
    puts("");
    puts("Descobrimento");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", d[i]);
    }
    puts("");
    puts("Fechamento");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", c[i]);
    }
    puts("");
    puts("Predecessores");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", pred[i]);
    }
    puts("");
    puts("Cor");
    for (int i = 0; i < graph->num_vertex; ++i) {
        printf("%d ", color[i]);
    }
    
}

void dfs_ini (graph* graph, int ini, int* color, int* d, int* c, int* pred) {
    for (int i = 0; i < graph->num_vertex; ++i) {
        color[i] = 0;
        d[i] = 0;
        c[i] = 0;
        pred[i] = -1;
    }    

    dfs(graph, ini, color, d, c, pred);
    for (int i = 0; i < graph->num_vertex; ++i) {
        if(color[i] == 0) {
            dfs(graph, i, color, d, c, pred);
        }
    }
}


void graph_print (graph* graph) {
    printf("Lista de Ajdacencias\n");
    for(int i = 0; i < graph->num_vertex; ++i) {
        node* temp = graph->array[i].head;
       
        printf("[%d]", i);
        while (temp != NULL) {
            printf("-> %d", temp->vertex);
            temp = temp->next;
        }
        puts("");
    }
}


int main(int argc, char* argv[]) {
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

    color = (int*) malloc(nv * sizeof(int));
    d = (int*) malloc(nv * sizeof(int));
    c = (int*) malloc(nv * sizeof(int));
    pred = (int*) malloc(nv * sizeof(int));
    graph_print (graph);
    dfs_ini (graph, ini, color, d, c, pred);
    
    return 0;
}