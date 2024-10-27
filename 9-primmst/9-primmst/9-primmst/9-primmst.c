#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000L 

//그래프 구조체 정의
typedef struct {
    int n;  //정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES]; //가중치 행렬
} GraphType;

int selected[MAX_VERTICES];  //선택된 정점을 추적하는 배열
int distance[MAX_VERTICES];  //각 정점까지의 최소 거리 저장

//최소 거리 값을 가진 정점을 반환하는 함수
int get_min_vertex(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected[i]) {  //아직 선택되지 않은 정점
            v = i;
            break;
        }
    }

    for (int i = 0; i < n; i++) {
        if (!selected[i] && distance[i] < distance[v]) {
            v = i;
        }
    }
    return v;
}

//Prim 알고리즘을 사용하여 MST를 찾는 함수
void FindPrimMST(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;  //모든 정점까지의 거리를 무한대로 초기화
        selected[i] = FALSE; //모든 정점을 선택되지 않음으로 초기화
    }

    distance[0] = 0;  //시작 정점의 거리 값을 0으로 설정
    printf("Prim MST Algorithm\n");

    //모든 정점을 대상으로 반복
    for (int i = 0; i < g->n; i++) {
        int u = get_min_vertex(g->n);  //최소 거리 값을 가진 정점 선택
        selected[u] = TRUE;  //해당 정점을 선택

        if (distance[u] == INF) return; //거리 값이 무한대이면 종료

        printf("정점 %d 추가\n", u + 1);  //정점 추가를 출력

        //선택된 정점과 인접한 모든 정점의 거리 값 갱신
        for (int v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];  //최소 거리 값으로 갱신
            }
        }
    }
}

//그래프 초기화 함수
void graph_init(GraphType* g) {
    g->n = MAX_VERTICES;  //정점 수 설정 (10개)
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;  //모든 가중치를 무한대로 초기화
        }
    }
}

//간선 삽입 함수
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start - 1][end - 1] = w;  //가중치 설정
    g->weight[end - 1][start - 1] = w;  //양방향 간선 처리
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

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));  //그래프 메모리 할당
    graph_init(g);  //그래프 초기화

    //그래프를 생성하는 함수
    GenerateGraph(g);

    //Prim 알고리즘을 사용하여 MST를 찾는 함수 호출
    FindPrimMST(g);  //Prim을 이용해 MST를 찾음

    free(g);  //메모리 해제
    return 0;
}
