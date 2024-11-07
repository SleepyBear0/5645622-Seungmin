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

//방문하지 않은 정점 중 최단 거리를 가진 정점을 찾는 함수
int get_min_vertex(int distance[], int found[]) {
    int min = INF, min_pos = -1;
    for (int i = 0; i < MAX_VERTICES; i++) {
        if (!found[i] && distance[i] < min) {
            min = distance[i]; //최단 거리 현재 거리로 업데이트
            min_pos = i; //최단 거리 정점 위치
        }
    }
    return min_pos;
}

//Dijkstra 알고리즘 함수 (인접(연결) 리스트 사용)
void dijkstra(GraphType* g, int start) {
    int distance[MAX_VERTICES];
    int found[MAX_VERTICES] = { 0 }; //방문한 여부 기록하는 배열
    int FoundOrder[MAX_VERTICES] = { 0 };  //탐색 순서 저장 배열
    int order = 1;

    //초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        distance[i] = INF;
    }
    distance[start] = 0;

    //최단 경로 찾는 반복문
    for (int i = 0; i < MAX_VERTICES; i++) {
        int u = get_min_vertex(distance, found);
        if (u == -1) break; //정점이 없으면 종료

        found[u] = 1; //선택된 정점을 방문으로 표시
        FoundOrder[u] = order++;  //탐색 순서 저장

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

        //선택된 정점 u의 인접 리스트를 순회하면서 거리를 갱신
        Node* node = g->adj[u];
        while (node != NULL) {
            int v = node->vertex;
            if (!found[v] && distance[u] + node->weight < distance[v]) {
                distance[v] = distance[u] + node->weight;
            }
            node = node->next;
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

    printf("다익스트라 알고리즘(연결리스트):\n");
    dijkstra(&g, 0);  //다익스트라 알고리즘 실행

    return 0;
}
