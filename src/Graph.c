#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

#define MAX_VERTICES 50//�ִ� ������ ����
int visited[MAX_VERTICES];//���� �湮 Ȯ�� �迭

typedef struct GraphType{
	int n;//�׷��� ����� ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];//�������
}GraphType;

void graph_init(GraphType *g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;//������� �ʱ�ȭ

}
void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES){
		return;
	}
	g->n = v + 1;//���� �߰�
}
void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n)//����ó��
		return;
	g->adj_mat[start][end] = 1;//���� ����
	g->adj_mat[end][start] = 1;
}
void dfs(GraphType *g, int v)
{//���̿켱Ž�� ����
	int w;

	visited[v] = 1;//���� �湮 ǥ��
	printf("%3d", v);//���� ���

	for (w = 1; w <= 6; w++)
	{//���� ������ w������ ����Ǿ� �ְ�, w������ �湮���� ���� ��쿡 ����
		if (g->adj_mat[v][w] && !visited[w])
			dfs(g, w);//DFS ���ȣ��
	}
}
void main()
{
	char c;
	int start_vertex;
	int i;
	int v = 6;

	GraphType g;
	graph_init(&g);//�׷��� �ʱ�ȭ

	insert_vertex(&g, v);//���� ����
	insert_edge(&g, 1, 2);//���� ����
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 2, 6);
	insert_edge(&g, 3, 4);

	printf("D : DFS, Q : Quit\n");

	while (1)
	{
		printf("Command > ");
		c = _getche();
		c = toupper(c);

		switch (c)
		{
		case 'D':
			for (i = 0; i < MAX_VERTICES; i++)
				visited[i] = 0;
			printf("\n Start Vertex: ");
			scanf_s("%d", &start_vertex);
			dfs(&g, start_vertex);//���̿켱Ž��
			puts("");
			break;
		case'Q':
			exit(1);

		default:
			printf("\nCommand is undefined\n\n");
			break;
		}
	}
}