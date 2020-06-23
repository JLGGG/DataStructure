#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

#define MAX_VERTICES 50//�ִ� ������ ����
#define MAX_QUEUE_SIZE 100

int visited[MAX_VERTICES];//���� �湮 Ȯ�� �迭

typedef int element;
typedef struct{
	element queue[MAX_QUEUE_SIZE];//ť ����
	int front, rear;
}QueueType;

typedef struct GraphType{
	int n;//�׷��� ����� ����
	int adj_mat[MAX_VERTICES][MAX_VERTICES];//�������
}GraphType;

void init(QueueType *q)
{
	q->front = q->rear = 0;//ť �ʱ�ȭ �Լ�
}
int is_empty(QueueType *q)
{
	return (q->front == q->rear);//ť�� �� ���
}
int is_full(QueueType *q)//ť�� full�� �Լ�
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType *q, element item)
{//ť ����
	if (is_full(q))
		fprintf(stderr, "ť�� ��ȭ����\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
element dequeue(QueueType *q)
{//ť ����
	if (is_empty(q))
		fprintf(stderr, "ť�� �������\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void graph_init(GraphType *g)
{//�׷��� �ʱ�ȭ �Լ�
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;

}
void insert_vertex(GraphType *g, int v)
{//���� ���� �Լ�
	if (((g->n) + 1) > MAX_VERTICES){
		return;
	}
	g->n = v + 1;
}
void insert_edge(GraphType *g, int start, int end)
{//���� ���� �Լ�
	if (start >= g->n || end >= g->n)
		return;
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
void dfs(GraphType *g, int v)
{//dfs�Լ�
	int w;

	visited[v] = 1;
	printf("%3d", v);

	for (w = 1; w <= 6; w++)
	{
		if (g->adj_mat[v][w] && !visited[w])
			dfs(g, w);
	}
}
void bfs(GraphType *g, int v)
{//�ʺ�켱Ž�� �Լ�
	int w;
	QueueType q;
	init(&q);
	visited[v] = 1;//���������� �湮�Ѵ�.
	printf("%3d", v);
	enqueue(&q, v);//���������� ť�� �ִ´�.
	while (!is_empty(&q)){
		v = dequeue(&q);//������ ť���� �����Ѵ�.
		for (w = 1; w <= g->n; w++)
			//����v�� ����w�� ����Ǿ� �ְ�, ����w�� �湮���� �ʾ����� ����
			if (g->adj_mat[v][w] && !visited[w]){
				visited[w] = 1;//w�湮
				printf("%3d", w);
				enqueue(&q, w);//���� w ť�� ����
			}
	}
}
void main()
{
	char c;
	int start_vertex;
	int i;
	int v = 6;

	GraphType g;
	graph_init(&g);

	insert_vertex(&g, v);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 5);
	insert_edge(&g, 2, 6);
	insert_edge(&g, 3, 4);

	printf("D : DFS, B : BFS, Q : Quit\n");

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
			dfs(&g, start_vertex);//dfs ȣ��
			puts("");
			break;
		case'B':
			for (i = 0; i < MAX_VERTICES; i++)
				visited[i] = 0;
			printf("\n Start Vertex: ");
			scanf_s("%d", &start_vertex);
			bfs(&g, start_vertex);//bfs ȣ��
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
