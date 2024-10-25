#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 1000
#define INF 1000

int parent[MAX_VERTICES];

//���� �ʱ�ȭ�ϴ� �Լ�
void set_init(int n)
{
    //��� ����� �θ� -1�� �ʱ�ȭ
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

//���տ��� �θ� ã�� �Լ�
int set_find(int curr)
{
    //�ݺ����� ����Ͽ� �ֻ��� �θ� ã��
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

//�� ������ ��ġ�� �Լ�
void set_union(int a, int b)
{
    //�� �������� �ֻ��� �θ� ã�Ƴ� �ϳ��� �������� �����
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

//���� ����ü ����
struct Edge {
    int start, end, weight; //����, ��, ����ġ
};

//�׷��� ����ü ����
typedef struct GraphType {
    int num_edges; //����
    int num_vertices; //����
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

//�׷��� �ʱ�ȭ�ϴ� �Լ�
void graph_init(GraphType* g, int vertices)
{
    g->num_edges = 0;
    g->num_vertices = vertices;
    //��� ������ �⺻������ �ʱ�ȭ�ϱ�
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

//������ �����ϴ� �Լ�
void insert_edge(GraphType* g, int start, int end, int w)
{
    if (g->num_edges < 2 * MAX_VERTICES) { //�ִ� ���� ���� üũ�ϱ�
        g->edges[g->num_edges].start = start - 1; //���� ���
        g->edges[g->num_edges].end = end - 1; //�� ���
        g->edges[g->num_edges].weight = w; //����ġ
        g->num_edges++;
    }
    else {
        printf("Edge array is full.\n"); //�� á�� ���
    }
}

//Quick Sort ��� Kruskal �˰��򿡼� ������ ����ġ�� ���ϴ� �Լ�
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);  //������ ����ġ�� ���Ͽ� ����
}

//Quick Sort ��� Kruskal �˰��� �Լ�
void QuickKruskal(GraphType* g)
{
    int edge_accepted = 0; //MST�� ���Ե� ���� ����
    int uset, vset;
    struct Edge e;

    set_init(g->num_vertices); //���� �ʱ�ȭ
    qsort(g->edges, g->num_edges, sizeof(struct Edge), compare);  //����ġ�� ���� ���� ����

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->num_vertices - 1) && i < g->num_edges) {
        e = g->edges[i];
        uset = set_find(e.start); //���� ����� ���� ã��
        vset = set_find(e.end); //�� ����� ���� ã��
        //�� ������ �ٸ� ��� MST�� �߰�
        if (uset != vset) {
            printf("Edge (%d,%d) select %d\n", e.start + 1, e.end + 1, e.weight);
            edge_accepted++;
            set_union(uset, vset); //��ġ��
        }
        i++;
    }
}

//MinHeap ��� Kruskal ���� �Լ�
void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

//MinHeap�� ���� heapify �Լ�, �ּ��� �Ӽ��� ����
void heapify(struct Edge heap[], int n, int i) {
    int smallest = i; //���� ��带 ���� ���� ���� ����
    int left = 2 * i + 1; 
    int right = 2 * i + 2;

    //���� �ڽ��� �����ϰ�, ���� ��庸�� �۴ٸ� smallest�� ���� �ڽ����� ����
    if (left < n && heap[left].weight < heap[smallest].weight)
        smallest = left;
    
    //������ �ڽ��� �����ϰ�, ���� ��庸�� �۴ٸ� smallest�� ������ �ڽ����� ����
    if (right < n && heap[right].weight < heap[smallest].weight)
        smallest = right;

    //smallest�� i�� �ٸ��ٸ�
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]); //���� ���� smallest ��ġ�� ��ȯ
        heapify(heap, n, smallest); //��ȯ�� ��带 �������� heapify�� ȣ���Ͽ� �ּ��� �Ӽ� ����
    }
}

//MinHeap���� �ּ� ������ �����ϴ� �Լ�
struct Edge extract_min(struct Edge heap[], int* n) {
    struct Edge root = heap[0];
    heap[0] = heap[--(*n)];
    heapify(heap, *n, 0);
    return root;
}

//MinHeap �����ϴ� �Լ�
void build_min_heap(struct Edge heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

//MinHeap ��� Kruskal �˰��� �Լ�
void MinHeapKruskal(GraphType* g)
{
    int edge_accepted = 0;
    int uset, vset;
    int n = g->num_edges;

    struct Edge heap[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        heap[i] = g->edges[i];
    }

    build_min_heap(heap, n); //�ּ��� ����
    set_init(g->num_vertices); //���� �ʱ�ȭ

    printf("\nMinHeap Based Kruskal\n");
    while (edge_accepted < (g->num_vertices - 1) && n > 0) {
        struct Edge e = extract_min(heap, &n); //�ּ� ���� ����
        uset = set_find(e.start); //���� ����� ���� ã��
        vset = set_find(e.end); //�� ����� ���� ã��
        if (uset != vset) { //�� ������ �ٸ� ��� MST�� �߰�
            printf("Edge (%d,%d) select %d\n", e.start + 1, e.end + 1, e.weight);
            edge_accepted++;
            set_union(uset, vset); //�� ���� ��ġ��
        }
    }
}

//�׷��� ����
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

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g, 10); //�׷��� �ʱ�ȭ

    GenerateGraph(g); //�׷��� �����

    QuickKruskal(g);    //Quick Sort ��� Kruskal
    MinHeapKruskal(g);  //MinHeap ��� Kruskal

    free(g);
    return 0;
}
