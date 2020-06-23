#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

#define MAX_VERTICES 50//최대 정점의 개수
#define MAX_QUEUE_SIZE 100

int visited[MAX_VERTICES];//정점 방문 확인 배열

typedef int element;
typedef struct{
	element queue[MAX_QUEUE_SIZE];//큐 정의
	int front, rear;
}QueueType;

typedef struct GraphType{
	int n;//그래프 노드의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];//인접행렬
}GraphType;

void init(QueueType *q)
{
	q->front = q->rear = 0;//큐 초기화 함수
}
int is_empty(QueueType *q)
{
	return (q->front == q->rear);//큐가 빈 경우
}
int is_full(QueueType *q)//큐가 full인 함수
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
void enqueue(QueueType *q, element item)
{//큐 삽입
	if (is_full(q))
		fprintf(stderr, "큐가 포화상태\n");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
element dequeue(QueueType *q)
{//큐 추출
	if (is_empty(q))
		fprintf(stderr, "큐가 공백상태\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

void graph_init(GraphType *g)
{//그래프 초기화 함수
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;

}
void insert_vertex(GraphType *g, int v)
{//정점 삽입 함수
	if (((g->n) + 1) > MAX_VERTICES){
		return;
	}
	g->n = v + 1;
}
void insert_edge(GraphType *g, int start, int end)
{//간선 삽입 함수
	if (start >= g->n || end >= g->n)
		return;
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
}
void dfs(GraphType *g, int v)
{//dfs함수
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
{//너비우선탐색 함수
	int w;
	QueueType q;
	init(&q);
	visited[v] = 1;//시작정점을 방문한다.
	printf("%3d", v);
	enqueue(&q, v);//시작정점을 큐에 넣는다.
	while (!is_empty(&q)){
		v = dequeue(&q);//정점을 큐에서 추출한다.
		for (w = 1; w <= g->n; w++)
			//정점v와 정점w가 연결되어 있고, 정점w가 방문되지 않았으면 실행
			if (g->adj_mat[v][w] && !visited[w]){
				visited[w] = 1;//w방문
				printf("%3d", w);
				enqueue(&q, w);//정점 w 큐에 삽입
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
			dfs(&g, start_vertex);//dfs 호출
			puts("");
			break;
		case'B':
			for (i = 0; i < MAX_VERTICES; i++)
				visited[i] = 0;
			printf("\n Start Vertex: ");
			scanf_s("%d", &start_vertex);
			bfs(&g, start_vertex);//bfs 호출
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
