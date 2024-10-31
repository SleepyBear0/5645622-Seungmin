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

//�ּ� ���� ��� ����ü
typedef struct {
    int vertex;
    int distance;
} HeapNode;

//�ּ� �� ����ü
typedef struct {
    HeapNode heap[MAX_VERTICES];
    int size;
} MinHeap;

//�ּ� �� �ʱ�ȭ �Լ�
void init_min_heap(MinHeap* h) {
    h->size = 0;
}

//�ּ� �� ���� �Լ�
void insert_min_heap(MinHeap* h, int vertex, int distance) {
    int i = h->size++; //���ο� ��� ���� ��ġ ���� �� �� ũ�� ����
    //����
    while (i > 0 && distance < h->heap[(i - 1) / 2].distance) {
        h->heap[i] = h->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;
}

//�ּ� �� ���� �Լ�
HeapNode delete_min_heap(MinHeap* h) {
    HeapNode min_node = h->heap[0]; //�ּҰ� ����
    HeapNode last = h->heap[--h->size]; //������ ��� ��������
    int parent = 0, child = 1; //�θ�, �ڽ� ���� �ʱ�ȭ

    //�ּ� ��� ����
    while (child < h->size) {
        if (child + 1 < h->size && h->heap[child].distance > h->heap[child + 1].distance)
            child++;
        if (last.distance <= h->heap[child].distance) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = 2 * parent + 1;
    }
    h->heap[parent] = last; //������ �� ������ ��� ��ġ ����
    return min_node; //�ּҰ� ��ȯ
}

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

//���ͽ�Ʈ�� �˰���(�ּ� �� ���)
void dijkstra_min_heap(GraphType* g, int start) {
    int distance[MAX_VERTICES]; //�ִܰŸ� ���� �迭
    int found[MAX_VERTICES] = { 0 }; //�湮 ���� �迭
    int FoundOrder[MAX_VERTICES] = { 0 }; //Ž�� ���� �迭 �߰�
    MinHeap heap;
    int order = 1; //Ž�� ���� �ʱ�ȭ
    init_min_heap(&heap); //�� �ʱ�ȭ

    //�ʱ� �Ÿ� �� ����
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF; //�ʱ� �Ÿ��� ���Ѵ�
    }
    distance[start] = 0; //���� ���� �Ÿ��� 0
    insert_min_heap(&heap, start, 0); //���� ���� ���� ����

    //���ͽ�Ʈ�� �˰��� ����
    while (heap.size > 0) {
        HeapNode min_node = delete_min_heap(&heap); //�ִܰŸ� ���� ��������
        int u = min_node.vertex; //�ش� ���� ��ȣ ����

        if (found[u]) continue; //�̹� �湮�� ��� ����
        found[u] = 1; //�湮 ǥ��
        FoundOrder[u] = order++; // Ž�� ���� ���

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

        Node* node = g->adj[u];
        while (node != NULL) {
            int v = node->vertex;
            //���� �湮���� �ʾҰ�, �ִ� �Ÿ� ������ �ʿ��� ���
            if (!found[v] && distance[u] + node->weight < distance[v]) {
                distance[v] = distance[u] + node->weight; //�ִ� �Ÿ� ����
                insert_min_heap(&heap, v, distance[v]); //���� �߰�
            }
            node = node->next; //���� ���� �̵�
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

    printf("���ͽ�Ʈ�� �˰���(min heap���):\n");
    dijkstra_min_heap(&g, 0);  // ���� 1���� ���� (index 0�� �ش�)

    return 0;
}
