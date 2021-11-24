#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0

typedef struct edge {
    int startEdge;
    int endEdge;
    struct edge* next;
}edge_t;
typedef struct {
    int Weight;
    int isVisited;
}vertex;

vertex* vertexes;
edge_t* creatFirstEdge(int startEdge, int endEdge);
edge_t* addEdge(edge_t* head, int startEdge, int endEdge);
void removeList(edge_t* head);
void dfs(edge_t* head, int number1);

int numEdges = 0;
int numVertex = 0;

edge_t* creatFirstEdge(int startEdge, int endEdge) {
    edge_t* tmp = (edge_t*)malloc(sizeof(edge_t));
    if (!tmp) {
        printf("Error allocating memory\n");
        exit(1);
    }
    tmp->next = NULL;
    tmp->startEdge = startEdge;
    tmp->endEdge = endEdge;
    return tmp;
}
edge_t* addEdge(edge_t* head, int startEdge, int endEdge) {
    if (!head) {
        printf("Error the pointer was NULL\n");
        exit(1);
    }
    edge_t* curNode = head;
    edge_t* tmp = (edge_t*)malloc(sizeof(edge_t));
    if (!tmp) {
        printf("Error allocating memory\n");
        exit(1);
    }
    tmp->next = NULL;
    tmp->startEdge = startEdge;
    tmp->endEdge = endEdge;
    while (curNode->next != NULL) {
        curNode = curNode->next;
    }
    curNode->next = tmp;
    return head;
}
void removeList(edge_t* head) {
    while (head != NULL) {
        edge_t* p;
        p = head;
        head = head->next;
        free(p);
    }
}
void dfs(edge_t* head, int weight) {
    edge_t* curEdge = head;
    fprintf(stdout, "%d ", weight);
    int minVertexWeight = numVertex;
    vertexes[weight].isVisited = TRUE;
    int j = 0;
    while (1) {
        if (j == 1) {
            break;
        }
        curEdge = head;
        minVertexWeight = numVertex;
        for (int i = 0; i < numEdges; i++) {
            if (curEdge->startEdge == weight) {
                if (vertexes[curEdge->endEdge].isVisited == FALSE) {
                    if (minVertexWeight > curEdge->endEdge) {
                        minVertexWeight = curEdge->endEdge;
                    }
                }
            }
            if (curEdge->endEdge == weight) {
                if (vertexes[curEdge->startEdge].isVisited == FALSE) {
                    if (minVertexWeight > curEdge->startEdge) {
                        minVertexWeight = curEdge->startEdge;
                    }
                }
            }
            curEdge = curEdge->next;
        }
        j++;
        if (minVertexWeight != numVertex) {
            dfs(head, minVertexWeight);
            j = 0;
        }
    }
}
int main(void) {
    edge_t* head = NULL;
    int startEdge;
    int endEdge;
    scanf("%d", &numVertex);
    vertexes = (vertex*)malloc(numVertex * sizeof(vertex));
    if (!vertexes) {
        printf("Error allocating memory\n");
        exit(1);
    }
    for (int i = 0; i < numVertex; i++) {
        vertexes[i].Weight = i;
        vertexes[i].isVisited = FALSE;
    }
    if (fscanf(stdin, "%d %d", &startEdge, &endEdge) != EOF) {
        head = creatFirstEdge(startEdge, endEdge);
        numEdges++;
    }
    while (fscanf(stdin, "%d %d", &startEdge, &endEdge) != EOF) {
        head = addEdge(head, startEdge, endEdge);
        numEdges++;
    }
    dfs(head, 0);
    removeList(head);
    free(vertexes);
    return 0;
}