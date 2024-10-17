#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  //그래프에서 최대 노드 수

//그래프 구조체 정의
typedef struct GraphType {
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; //인접 행렬
    int visited[MAX_VERTICES]; //방문 여부
} GraphType;

//그래프 초기화
void init(GraphType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->visited[i] = 0; //방문 여부 초기화(방문하지 않았을 경우 0)
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0; //인접 행렬 초기화
        }
    }
}

//간선 삽입 연산
void insert_edge(GraphType* g, int start, int end) {
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

//깊이 우선 탐색 (DFS)
void dfs(GraphType* graph, int start, int target) {
    int stack[MAX_VERTICES], top = -1; //스택
    int visitedCount = -1; //방문한 노드 수
    int found = 0; //목표 발견 여부

    //방문 경로를 저장할 배열
    int path[MAX_VERTICES * 10]; //충분히 큰 크기로 선언
    int pathIndex = 0;

    stack[++top] = start; //시작 노드 스택에 추가
    graph->visited[start] = 1; //시작 노드 방문 처리

    while (top != -1) {
        int current = stack[top];

        //방문 경로 저장 및 방문 카운트 증가
        path[pathIndex++] = current;
        visitedCount++;
        printf("%d ", current); //방문한 노드 출력

        //목표 발견
        if (current == target) {
            found = 1; //목표 발견
            break; //탐색 종료
        }

        //다음 노드 탐색
        int hasUnvisitedNeighbor = 0; //방문하지 않은 이웃 노드가 있는지 확인
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph->adj_mat[current][i] == 1) { //이웃 노드가 있으면
                if (!graph->visited[i]) {
                    stack[++top] = i; //방문하지 않은 노드를 스택에 추가
                    graph->visited[i] = 1; //방문 처리
                    hasUnvisitedNeighbor = 1; //이웃 노드 발견
                    break; //탐색 계속
                }
            }
        }

        //방문할 이웃 노드가 없으면 스택에서 제거
        if (!hasUnvisitedNeighbor) {
            top--;
        }
    }

    if (found) {
        printf("\n탐색 성공: %d\n", target);
        printf("방문한 노드의 수: %d\n", visitedCount);
    }
    else {
        printf("\n탐색 실패: %d\n", target);
    }

    //방문 배열 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = 0;
    }
}

//너비 우선 탐색 (BFS)
void bfs(GraphType* graph, int start, int target) {
    int queue[MAX_VERTICES], front = 0, rear = 0; //큐
    int visitedCount = -1; //방문한 노드 수
    int found = 0; //목표 발견 여부

    //방문 경로를 저장할 배열
    int path[MAX_VERTICES * 10]; //충분히 큰 크기로 선언
    int pathIndex = 0;

    queue[rear++] = start; //시작 노드 큐에 추가
    graph->visited[start] = 1; //시작 노드 방문 처리

    while (front < rear) {
        int current = queue[front++];

        //방문 경로 저장
        path[pathIndex++] = current;
        visitedCount++;
        printf("%d ", current); //방문한 노드 출력

        if (current == target) {
            found = 1; //목표 발견
            break; //탐색 종료
        }

        //이웃 노드 탐색
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph->adj_mat[current][i] == 1 && !graph->visited[i]) {
                queue[rear++] = i; //이웃 노드를 큐에 추가
                graph->visited[i] = 1; //방문 처리
            }
        }
    }

    if (found) {
        printf("\n탐색 성공: %d\n", target);
        printf("방문한 노드의 수: %d\n", visitedCount);
    }
    else {
        printf("\n탐색 실패: %d\n", target);
    }
}

//메인 함수
int main() {
    GraphType graph;
    init(&graph);

    //그래프 만들기
    insert_edge(&graph, 0, 2);
    insert_edge(&graph, 0, 5);
    insert_edge(&graph, 0, 6);
    insert_edge(&graph, 0, 9);
    insert_edge(&graph, 0, 4);
    insert_edge(&graph, 1, 4);
    insert_edge(&graph, 1, 5);
    insert_edge(&graph, 1, 7);
    insert_edge(&graph, 1, 10);
    insert_edge(&graph, 2, 3);
    insert_edge(&graph, 2, 4);
    insert_edge(&graph, 3, 5);
    insert_edge(&graph, 3, 4);
    insert_edge(&graph, 4, 6);
    insert_edge(&graph, 4, 7);
    insert_edge(&graph, 4, 5);
    insert_edge(&graph, 6, 7);
    insert_edge(&graph, 6, 8);
    insert_edge(&graph, 7, 10);
    insert_edge(&graph, 8, 9);
    insert_edge(&graph, 8, 10);

    int choice, start, target;
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
    printf(" 1\t : 깊이 우선 탐색\t |\n");
    printf(" 2\t : 너비 우선 탐색\t |\n");
    printf(" 3\t : 종료\t\t\t |\n");
    printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");

    //메뉴 입력 무한 반복
    //1을 누르면 dfs 실행
    //2를 누르면 bfs 실행
    //3을 누르면 종료
    do {
        printf("\n메뉴 입력: ");
        scanf_s("%d", &choice);

        if (choice == 1 || choice == 2) {
            printf("시작 번호와 탐색할 값 입력: ");
            scanf_s("%d %d", &start, &target);

            if (choice == 1) {
                dfs(&graph, start, target);
            }
            else {
                bfs(&graph, start, target);
            }
        }

    } while (choice != 3);

    printf("프로그램 종료\n");
    return 0;
}