#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100  //�׷������� �ִ� ��� ��

//�׷��� ����ü ����
typedef struct GraphType {
    int adj_mat[MAX_VERTICES][MAX_VERTICES]; //���� ���
    int visited[MAX_VERTICES]; //�湮 ����
} GraphType;

//�׷��� �ʱ�ȭ
void init(GraphType* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        g->visited[i] = 0; //�湮 ���� �ʱ�ȭ(�湮���� �ʾ��� ��� 0)
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adj_mat[i][j] = 0; //���� ��� �ʱ�ȭ
        }
    }
}

//���� ���� ����
void insert_edge(GraphType* g, int start, int end) {
    g->adj_mat[start][end] = 1;
    g->adj_mat[end][start] = 1;
}

//���� �켱 Ž�� (DFS)
void dfs(GraphType* graph, int start, int target) {
    int stack[MAX_VERTICES], top = -1; //����
    int visitedCount = -1; //�湮�� ��� ��
    int found = 0; //��ǥ �߰� ����

    //�湮 ��θ� ������ �迭
    int path[MAX_VERTICES * 10]; //����� ū ũ��� ����
    int pathIndex = 0;

    stack[++top] = start; //���� ��� ���ÿ� �߰�
    graph->visited[start] = 1; //���� ��� �湮 ó��

    while (top != -1) {
        int current = stack[top];

        //�湮 ��� ���� �� �湮 ī��Ʈ ����
        path[pathIndex++] = current;
        visitedCount++;
        printf("%d ", current); //�湮�� ��� ���

        //��ǥ �߰�
        if (current == target) {
            found = 1; //��ǥ �߰�
            break; //Ž�� ����
        }

        //���� ��� Ž��
        int hasUnvisitedNeighbor = 0; //�湮���� ���� �̿� ��尡 �ִ��� Ȯ��
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph->adj_mat[current][i] == 1) { //�̿� ��尡 ������
                if (!graph->visited[i]) {
                    stack[++top] = i; //�湮���� ���� ��带 ���ÿ� �߰�
                    graph->visited[i] = 1; //�湮 ó��
                    hasUnvisitedNeighbor = 1; //�̿� ��� �߰�
                    break; //Ž�� ���
                }
            }
        }

        //�湮�� �̿� ��尡 ������ ���ÿ��� ����
        if (!hasUnvisitedNeighbor) {
            top--;
        }
    }

    if (found) {
        printf("\nŽ�� ����: %d\n", target);
        printf("�湮�� ����� ��: %d\n", visitedCount);
    }
    else {
        printf("\nŽ�� ����: %d\n", target);
    }

    //�湮 �迭 �ʱ�ȭ
    for (int i = 0; i < MAX_VERTICES; i++) {
        graph->visited[i] = 0;
    }
}

//�ʺ� �켱 Ž�� (BFS)
void bfs(GraphType* graph, int start, int target) {
    int queue[MAX_VERTICES], front = 0, rear = 0; //ť
    int visitedCount = -1; //�湮�� ��� ��
    int found = 0; //��ǥ �߰� ����

    //�湮 ��θ� ������ �迭
    int path[MAX_VERTICES * 10]; //����� ū ũ��� ����
    int pathIndex = 0;

    queue[rear++] = start; //���� ��� ť�� �߰�
    graph->visited[start] = 1; //���� ��� �湮 ó��

    while (front < rear) {
        int current = queue[front++];

        //�湮 ��� ����
        path[pathIndex++] = current;
        visitedCount++;
        printf("%d ", current); //�湮�� ��� ���

        if (current == target) {
            found = 1; //��ǥ �߰�
            break; //Ž�� ����
        }

        //�̿� ��� Ž��
        for (int i = 0; i < MAX_VERTICES; i++) {
            if (graph->adj_mat[current][i] == 1 && !graph->visited[i]) {
                queue[rear++] = i; //�̿� ��带 ť�� �߰�
                graph->visited[i] = 1; //�湮 ó��
            }
        }
    }

    if (found) {
        printf("\nŽ�� ����: %d\n", target);
        printf("�湮�� ����� ��: %d\n", visitedCount);
    }
    else {
        printf("\nŽ�� ����: %d\n", target);
    }
}

//���� �Լ�
int main() {
    GraphType graph;
    init(&graph);

    //�׷��� �����
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
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");
    printf(" 1\t : ���� �켱 Ž��\t |\n");
    printf(" 2\t : �ʺ� �켱 Ž��\t |\n");
    printf(" 3\t : ����\t\t\t |\n");
    printf("�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n");

    //�޴� �Է� ���� �ݺ�
    //1�� ������ dfs ����
    //2�� ������ bfs ����
    //3�� ������ ����
    do {
        printf("\n�޴� �Է�: ");
        scanf_s("%d", &choice);

        if (choice == 1 || choice == 2) {
            printf("���� ��ȣ�� Ž���� �� �Է�: ");
            scanf_s("%d %d", &start, &target);

            if (choice == 1) {
                dfs(&graph, start, target);
            }
            else {
                bfs(&graph, start, target);
            }
        }

    } while (choice != 3);

    printf("���α׷� ����\n");
    return 0;
}