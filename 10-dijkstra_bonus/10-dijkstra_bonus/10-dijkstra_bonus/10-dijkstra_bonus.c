#include <stdio.h>
#include <stdlib.h>

#define INF 1000L
#define MAX_VERTICES 10

//인접 리스트로 그래프의 노드 구조체 정의
typedef struct Node {
    int vertex; //정점의 번호
    int weight; //해당 간선의 가중치
    struct Node* next; //다음 노드를 가리키는 포인터
} Node;

//인접 리스트로 표현된 그래프 구조체
typedef struct {
    int n;  //정점의 개수
    Node* adj[MAX_VERTICES];  //인접 리스트 배열
} GraphType;

//최소 힙의 노드 구조체
typedef struct {
    int vertex;
    int distance;
} HeapNode;

//최소 힙 구조체
typedef struct {
    HeapNode heap[MAX_VERTICES];
    int size;
} MinHeap;

//최소 힙 초기화 함수
void init_min_heap(MinHeap* h) {
    h->size = 0;
}

//최소 힙 삽입 함수
void insert_min_heap(MinHeap* h, int vertex, int distance) {
    int i = h->size++; //새로운 요소 삽입 위치 설정 후 힙 크기 증가
    //삽입
    while (i > 0 && distance < h->heap[(i - 1) / 2].distance) {
        h->heap[i] = h->heap[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    h->heap[i].vertex = vertex;
    h->heap[i].distance = distance;
}

//최소 힙 삭제 함수
HeapNode delete_min_heap(MinHeap* h) {
    HeapNode min_node = h->heap[0]; //최소값 저장
    HeapNode last = h->heap[--h->size]; //마지막 요소 가져오기
    int parent = 0, child = 1; //부모, 자식 변수 초기화

    //최소 요소 삭제
    while (child < h->size) {
        if (child + 1 < h->size && h->heap[child].distance > h->heap[child + 1].distance)
            child++;
        if (last.distance <= h->heap[child].distance) break;
        h->heap[parent] = h->heap[child];
        parent = child;
        child = 2 * parent + 1;
    }
    h->heap[parent] = last; //재정렬 후 마지막 요소 위치 지정
    return min_node; //최소값 반환
}

//그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = MAX_VERTICES;
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->adj[i] = NULL;
    }
}

//간선 삽입 함수
void insert_edge(GraphType* g, int start, int end, int weight) {
    Node* node = (Node*)malloc(sizeof(Node)); //노드 생성
    node->vertex = end - 1; //연결될 정점 번호 설정
    node->weight = weight; //간선 가중치 설정
    node->next = g->adj[start - 1]; //start의 인접 리스트 앞에 삽입
    g->adj[start - 1] = node; //start 정점의 인접 리스트 업데이트

    //반대방향
    node = (Node*)malloc(sizeof(Node));
    node->vertex = start - 1;
    node->weight = weight;
    node->next = g->adj[end - 1];
    g->adj[end - 1] = node;
}

//그래프 생성 함수
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

//다익스트라 알고리즘(최소 힙 사용)
void dijkstra_min_heap(GraphType* g, int start) {
    int distance[MAX_VERTICES]; //최단거리 저장 배열
    int found[MAX_VERTICES] = { 0 }; //방문 여부 배열
    int FoundOrder[MAX_VERTICES] = { 0 }; //탐색 순서 배열 추가
    MinHeap heap;
    int order = 1; //탐색 순서 초기화
    init_min_heap(&heap); //힙 초기화

    //초기 거리 값 설정
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF; //초기 거리는 무한대
    }
    distance[start] = 0; //시작 정점 거리는 0
    insert_min_heap(&heap, start, 0); //힙에 시작 정점 삽입

    //다익스트라 알고리즘 수행
    while (heap.size > 0) {
        HeapNode min_node = delete_min_heap(&heap); //최단거리 정점 가져오기
        int u = min_node.vertex; //해당 정점 번호 저장

        if (found[u]) continue; //이미 방문한 경우 무시
        found[u] = 1; //방문 표시
        FoundOrder[u] = order++; // 탐색 순서 기록

        //현재 상태 거리 배열과 방문 배열 출력
        printf("Distance : ");
        for (int d = 0; d < MAX_VERTICES; d++) {
            if (distance[d] == INF) printf("* "); //무한대의 경우 *
            else printf("%d ", distance[d]); //정점까지의 거리 출력
        }
        printf("\nFound : ");
        for (int f = 0; f < MAX_VERTICES; f++) {
            printf("%d ", found[f]); //방문 여부 출력
        }
        printf("\n\n");

        Node* node = g->adj[u];
        while (node != NULL) {
            int v = node->vertex;
            //아직 방문하지 않았고, 최단 거리 갱신이 필요한 경우
            if (!found[v] && distance[u] + node->weight < distance[v]) {
                distance[v] = distance[u] + node->weight; //최단 거리 갱신
                insert_min_heap(&heap, v, distance[v]); //힙에 추가
            }
            node = node->next; //다음 노드로 이동
        }
    }

    //모든 정점 최종 방문 순서 출력
    printf("Found Order: ");
    for (int o = 0; o < MAX_VERTICES; o++) {
        printf("%d ", FoundOrder[o]);
    }
    printf("\n");
}

int main() {
    GraphType g;
    graph_init(&g); //그래프초기화
    GenerateGraph(&g); //그래프 생성

    printf("다익스트라 알고리즘(min heap사용):\n");
    dijkstra_min_heap(&g, 0);  // 정점 1부터 시작 (index 0에 해당)

    return 0;
}
