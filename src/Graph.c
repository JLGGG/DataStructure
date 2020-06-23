#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>

#define MAX_VERTICES 50//최대 정점의 개수
int visited[MAX_VERTICES];//정점 방문 확인 배열

typedef struct GraphType{
	int n;//그래프 노드의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES];//인접행렬
}GraphType;

void graph_init(GraphType *g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
		for (c = 0; c < MAX_VERTICES; c++)
			g->adj_mat[r][c] = 0;//인접행렬 초기화

}
void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES){
		return;
	}
	g->n = v + 1;//정점 추가
}
void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n)//예외처리
		return;
	g->adj_mat[start][end] = 1;//간선 연결
	g->adj_mat[end][start] = 1;
}
void dfs(GraphType *g, int v)
{//깊이우선탐색 구현
	int w;

	visited[v] = 1;//정점 방문 표시
	printf("%3d", v);//정점 출력

	for (w = 1; w <= 6; w++)
	{//현재 정점과 w정점이 연결되어 있고, w정점이 방문되지 않은 경우에 실행
		if (g->adj_mat[v][w] && !visited[w])
			dfs(g, w);//DFS 재귀호출
	}
}
void main()
{
	char c;
	int start_vertex;
	int i;
	int v = 6;

	GraphType g;
	graph_init(&g);//그래프 초기화

	insert_vertex(&g, v);//정점 삽입
	insert_edge(&g, 1, 2);//간선 삽입
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
			dfs(&g, start_vertex);//깊이우선탐색
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