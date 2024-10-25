#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define MAX_VERTICES 1000
#define INF 1000

int parent[MAX_VERTICES];

//집합 초기화하는 함수
void set_init(int n)
{
    //모든 노드의 부모를 -1로 초기화
    for (int i = 0; i < n; i++)
        parent[i] = -1;
}

//집합에서 부모 찾는 함수
int set_find(int curr)
{
    //반복문을 사용하여 최상위 부모를 찾기
    if (parent[curr] == -1)
        return curr;
    while (parent[curr] != -1)
        curr = parent[curr];
    return curr;
}

//두 집합을 합치는 함수
void set_union(int a, int b)
{
    //각 집합으이 최상위 부모를 찾아내 하나의 집합으로 만들기
    int root1 = set_find(a);
    int root2 = set_find(b);
    if (root1 != root2)
        parent[root1] = root2;
}

//엣지 구조체 정의
struct Edge {
    int start, end, weight; //시작, 끝, 가중치
};

//그래프 구조체 정의
typedef struct GraphType {
    int num_edges; //엣지
    int num_vertices; //정점
    struct Edge edges[2 * MAX_VERTICES];
} GraphType;

//그래프 초기화하는 함수
void graph_init(GraphType* g, int vertices)
{
    g->num_edges = 0;
    g->num_vertices = vertices;
    //모든 엣지를 기본값으로 초기화하기
    for (int i = 0; i < 2 * MAX_VERTICES; i++) {
        g->edges[i].start = 0;
        g->edges[i].end = 0;
        g->edges[i].weight = INF;
    }
}

//엣지를 삽입하는 함수
void insert_edge(GraphType* g, int start, int end, int w)
{
    if (g->num_edges < 2 * MAX_VERTICES) { //최대 엣지 수를 체크하기
        g->edges[g->num_edges].start = start - 1; //시작 노드
        g->edges[g->num_edges].end = end - 1; //끝 노드
        g->edges[g->num_edges].weight = w; //가중치
        g->num_edges++;
    }
    else {
        printf("Edge array is full.\n"); //꽉 찼을 경우
    }
}

//Quick Sort 기반 Kruskal 알고리즘에서 엣지의 가중치를 비교하는 함수
int compare(const void* a, const void* b)
{
    struct Edge* x = (struct Edge*)a;
    struct Edge* y = (struct Edge*)b;
    return (x->weight - y->weight);  //엣지의 가중치를 비교하여 정렬
}

//Quick Sort 기반 Kruskal 알고리즘 함수
void QuickKruskal(GraphType* g)
{
    int edge_accepted = 0; //MST에 포함된 엣지 개수
    int uset, vset;
    struct Edge e;

    set_init(g->num_vertices); //집합 초기화
    qsort(g->edges, g->num_edges, sizeof(struct Edge), compare);  //가중치에 따라 엣지 정렬

    printf("Quick Based Kruskal\n");
    int i = 0;
    while (edge_accepted < (g->num_vertices - 1) && i < g->num_edges) {
        e = g->edges[i];
        uset = set_find(e.start); //시작 노드의 집합 찾기
        vset = set_find(e.end); //끝 노드의 집합 찾기
        //두 집합이 다를 경우 MST에 추가
        if (uset != vset) {
            printf("Edge (%d,%d) select %d\n", e.start + 1, e.end + 1, e.weight);
            edge_accepted++;
            set_union(uset, vset); //합치기
        }
        i++;
    }
}

//MinHeap 기반 Kruskal 스왑 함수
void swap(struct Edge* a, struct Edge* b) {
    struct Edge temp = *a;
    *a = *b;
    *b = temp;
}

//MinHeap을 위한 heapify 함수, 최소힙 속성을 유지
void heapify(struct Edge heap[], int n, int i) {
    int smallest = i; //현재 노드를 가장 작은 노드로 가정
    int left = 2 * i + 1; 
    int right = 2 * i + 2;

    //왼쪽 자식이 존재하고, 현재 노드보다 작다면 smallest를 왼쪽 자식으로 갱신
    if (left < n && heap[left].weight < heap[smallest].weight)
        smallest = left;
    
    //오른쪽 자식이 존재하고, 현재 노드보다 작다면 smallest를 오른쪽 자식으로 갱신
    if (right < n && heap[right].weight < heap[smallest].weight)
        smallest = right;

    //smallest가 i와 다르다면
    if (smallest != i) {
        swap(&heap[i], &heap[smallest]); //현재 노드와 smallest 위치를 교환
        heapify(heap, n, smallest); //교환된 노드를 기준으로 heapify를 호출하여 최소힙 속성 유지
    }
}

//MinHeap에서 최소 엣지를 추출하는 함수
struct Edge extract_min(struct Edge heap[], int* n) {
    struct Edge root = heap[0];
    heap[0] = heap[--(*n)];
    heapify(heap, *n, 0);
    return root;
}

//MinHeap 생성하는 함수
void build_min_heap(struct Edge heap[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(heap, n, i);
    }
}

//MinHeap 기반 Kruskal 알고리즘 함수
void MinHeapKruskal(GraphType* g)
{
    int edge_accepted = 0;
    int uset, vset;
    int n = g->num_edges;

    struct Edge heap[MAX_VERTICES];
    for (int i = 0; i < n; i++) {
        heap[i] = g->edges[i];
    }

    build_min_heap(heap, n); //최소힙 생성
    set_init(g->num_vertices); //집합 초기화

    printf("\nMinHeap Based Kruskal\n");
    while (edge_accepted < (g->num_vertices - 1) && n > 0) {
        struct Edge e = extract_min(heap, &n); //최소 엣지 추출
        uset = set_find(e.start); //시작 노드의 집합 찾기
        vset = set_find(e.end); //끝 노드의 집합 찾기
        if (uset != vset) { //두 집합이 다를 경우 MST에 추가
            printf("Edge (%d,%d) select %d\n", e.start + 1, e.end + 1, e.weight);
            edge_accepted++;
            set_union(uset, vset); //두 집합 합치기
        }
    }
}

//그래프 생성
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
    graph_init(g, 10); //그래프 초기화

    GenerateGraph(g); //그래프 만들기

    QuickKruskal(g);    //Quick Sort 기반 Kruskal
    MinHeapKruskal(g);  //MinHeap 기반 Kruskal

    free(g);
    return 0;
}
