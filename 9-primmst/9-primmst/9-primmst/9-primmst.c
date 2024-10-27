#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 10
#define INF 1000L 

//�׷��� ����ü ����
typedef struct {
    int n;  //������ ����
    int weight[MAX_VERTICES][MAX_VERTICES]; //����ġ ���
} GraphType;

int selected[MAX_VERTICES];  //���õ� ������ �����ϴ� �迭
int distance[MAX_VERTICES];  //�� ���������� �ּ� �Ÿ� ����

//�ּ� �Ÿ� ���� ���� ������ ��ȯ�ϴ� �Լ�
int get_min_vertex(int n) {
    int v = -1;
    for (int i = 0; i < n; i++) {
        if (!selected[i]) {  //���� ���õ��� ���� ����
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

//Prim �˰����� ����Ͽ� MST�� ã�� �Լ�
void FindPrimMST(GraphType* g) {
    for (int i = 0; i < g->n; i++) {
        distance[i] = INF;  //��� ���������� �Ÿ��� ���Ѵ�� �ʱ�ȭ
        selected[i] = FALSE; //��� ������ ���õ��� �������� �ʱ�ȭ
    }

    distance[0] = 0;  //���� ������ �Ÿ� ���� 0���� ����
    printf("Prim MST Algorithm\n");

    //��� ������ ������� �ݺ�
    for (int i = 0; i < g->n; i++) {
        int u = get_min_vertex(g->n);  //�ּ� �Ÿ� ���� ���� ���� ����
        selected[u] = TRUE;  //�ش� ������ ����

        if (distance[u] == INF) return; //�Ÿ� ���� ���Ѵ��̸� ����

        printf("���� %d �߰�\n", u + 1);  //���� �߰��� ���

        //���õ� ������ ������ ��� ������ �Ÿ� �� ����
        for (int v = 0; v < g->n; v++) {
            if (g->weight[u][v] != INF && !selected[v] && g->weight[u][v] < distance[v]) {
                distance[v] = g->weight[u][v];  //�ּ� �Ÿ� ������ ����
            }
        }
    }
}

//�׷��� �ʱ�ȭ �Լ�
void graph_init(GraphType* g) {
    g->n = MAX_VERTICES;  //���� �� ���� (10��)
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->weight[i][j] = INF;  //��� ����ġ�� ���Ѵ�� �ʱ�ȭ
        }
    }
}

//���� ���� �Լ�
void insert_edge(GraphType* g, int start, int end, int w) {
    g->weight[start - 1][end - 1] = w;  //����ġ ����
    g->weight[end - 1][start - 1] = w;  //����� ���� ó��
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

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));  //�׷��� �޸� �Ҵ�
    graph_init(g);  //�׷��� �ʱ�ȭ

    //�׷����� �����ϴ� �Լ�
    GenerateGraph(g);

    //Prim �˰����� ����Ͽ� MST�� ã�� �Լ� ȣ��
    FindPrimMST(g);  //Prim�� �̿��� MST�� ã��

    free(g);  //�޸� ����
    return 0;
}
