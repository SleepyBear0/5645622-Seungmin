#include <stdio.h>
#include <stdlib.h>

#define INF 1000L
#define MAX_VERTICES 10

//���� ����Ʈ�� �׷����� ��� ����ü ����
typedef struct Node {
    int vertex; //������ ��ȣ
    int weight; //�ش� ������ ����ġ
    struct Node* next; //���� ��带 ����Ű�� ������
} Node;

//���� ����Ʈ�� ǥ���� �׷��� ����ü
typedef struct {
    int n;  //������ ����
    Node* adj[MAX_VERTICES];  //���� ����Ʈ �迭
} GraphType;

//�׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    g->n = MAX_VERTICES;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj[i] = NULL;
    }
}

//���� ���� �Լ�
void insert_edge(GraphType* g, int start, int end, int weight) {
    Node* node = (Node*)malloc(sizeof(Node)); //��� ����
    node->vertex = end - 1; //����� ���� ��ȣ ����
    node->weight = weight; //���� ����ġ ����
    node->next = g->adj[start - 1]; //start�� ���� ����Ʈ �տ� ����
    g->adj[start - 1] = node; //start ������ ���� ����Ʈ ������Ʈ

    //�ݴ����
    node = (Node*)malloc(sizeof(Node));
    node->vertex = start - 1;
    node->weight = weight;
    node->next = g->adj[end - 1];
    g->adj[end - 1] = node;
}

//�׷��� ���� �Լ�
void GenerateGraph(GraphType* g) {
    insert_edge(g, 1, 2, 3);
    insert_edge(g, 1, 6, 11);
    insert_edge(g, 1, 7, 12);
    insert_edge(g, 2, 3, 5);
    insert_edge(g, 2, 4, 4);
    insert_edge(g, 2, 5, 1);
    insert_edge(g, 2, 6, 7);
    insert_edge(g, 2, 7, 8);
    insert_edge(g, 3, 4, 2);
    insert_edge(g, 3, 7, 6);
    insert_edge(g, 3, 8, 5);
    insert_edge(g, 4, 5, 13);
    insert_edge(g, 4, 8, 14);
    insert_edge(g, 4, 10, 16);
    insert_edge(g, 5, 6, 9);
    insert_edge(g, 5, 9, 18);
    insert_edge(g, 5, 10, 17);
    insert_edge(g, 7, 8, 13);
    insert_edge(g, 8, 10, 15);
    insert_edge(g, 9, 10, 10);
}

//�湮���� ���� ���� �� �ִ� �Ÿ��� ���� ������ ã�� �Լ�
int get_min_vertex(int distance[], int found[]) {
    int min = INF, min_pos = -1;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!found[i] && distance[i] < min) {
            min = distance[i]; //�ִ� �Ÿ� ���� �Ÿ��� ������Ʈ
            min_pos = i; //�ִ� �Ÿ� ���� ��ġ
        }
    }
    return min_pos;
}

//Dijkstra �˰��� �Լ� (����(����) ����Ʈ ���)
void dijkstra(GraphType* g, int start) {
    int distance[MAX_VERTICES];
    int found[MAX_VERTICES] = { 0 }; //�湮�� ���� ����ϴ� �迭
    int FoundOrder[MAX_VERTICES] = { 0 };  //Ž�� ���� ���� �迭
    int order = 1;

    //�ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;

    //�ִ� ��� ã�� �ݺ���
    for (int i = 0; i < MAX_VERTICES; i++) {
        int u = get_min_vertex(distance, found);
        if (u == -1) break; //������ ������ ����

        found[u] = 1; //���õ� ������ �湮���� ǥ��
        FoundOrder[u] = order++;  //Ž�� ���� ����

        //���� ���� �Ÿ� �迭�� �湮 �迭 ���
        printf("Distance : ");
        for (int d = 0; d < MAX_VERTICES; d++) {
            if (distance[d] == INF) printf("* "); //���Ѵ��� ��� *
            else printf("%d ", distance[d]); //���������� �Ÿ� ���
        }
        printf("\nFound : ");
        for (int f = 0; f < MAX_VERTICES; f++) {
            printf("%d ", found[f]); //�湮 ���� ���
        }
        printf("\n\n");

        //���õ� ���� u�� ���� ����Ʈ�� ��ȸ�ϸ鼭 �Ÿ��� ����
        Node* node = g->adj[u];
        while (node != NULL) {
            int v = node->vertex;
            if (!found[v] && distance[u] + node->weight < distance[v]) {
                distance[v] = distance[u] + node->weight;
            }
            node = node->next;
        }
    }

    //��� ���� ���� �湮 ���� ���
    printf("Found Order: ");
    for (int o = 0; o < MAX_VERTICES; o++) {
        printf("%d ", FoundOrder[o]);
    }
    printf("\n");
}

int main() {
    GraphType g;
    graph_init(&g); //�׷����ʱ�ȭ
    GenerateGraph(&g); //�׷��� ����

    printf("���ͽ�Ʈ�� �˰���(���Ḯ��Ʈ):\n");
    dijkstra(&g, 0);  //���ͽ�Ʈ�� �˰��� ����

    return 0;
}
