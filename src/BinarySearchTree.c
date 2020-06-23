#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 40

typedef struct TreeNode{//트리노드 정의
	char cData;
	struct TreeNode *ptLeft;
	struct TreeNode *ptRight;
}BSTREENODE;

typedef struct Tree{//트리 정의
	int nTreeSize;
	BSTREENODE *ptRoot;
}BSTREE;

void initTree(BSTREE *ptTree);//트리 초기화
void printTree(BSTREE *ptTree);//트리 출력함수
void printTreeSub(BSTREENODE *ptNode, int nDepth);//트리 출력 서브함수
int isEmpty(BSTREE *ptTree);//트리가 비었는지 확인
int isFull(BSTREE *ptTree);//트리가 full인지 확인
void insertTree(BSTREE *ptTree, char cData);//트리 노드삽입
void insertTreeSub(BSTREENODE *ptCurrent, BSTREENODE *ptInsertNode);//삽입 서브함수
int searchItem(BSTREE *ptTree, char cData);//search함수
char searchItemSub(BSTREENODE *ptCurrent, char cData);//search 서브함수
void traverseInorder(BSTREENODE *ptNode);//중위 순회함수
void traversePreorder(BSTREENODE *ptNode);//전위 순회함수
void traversePostorder(BSTREENODE *ptNode);//후위 순회함수

void main()
{
	BSTREE *ptTree;//트리 선언
	char cCommand, cData;

	printf("*******************Choose Command!! ************************\n");
	printf("+ : insert S: search item\n");
	printf("I : inorder P : preorder O : postorder \n");
	printf("F : full check, E: empty check, Q :Quit\n");
	printf("************************************************************\n");

	ptTree=(BSTREE*)malloc(sizeof(BSTREE));//트리 생성

	initTree(ptTree);//트리 초기화

	do{
		printf("Command :");
		cCommand=_getch();
		cCommand=toupper(cCommand);
		_putch(cCommand);
		printf("\n");

		switch(cCommand)
		{
		case'+'://노드 추가
			printf("Insert data : ");
			cData=_getch();
			_putch(cData);
			printf("\n");
			insertTree(ptTree, cData);
			break;
		case 'E'://트리 비었는지 확인
			if(isEmpty(ptTree)) printf("Tree is empty\n");
			else printf("Tree isn't full!\n");
			break;
		case 'F'://트리가 full인지 확인
			if(isFull(ptTree)) printf("Tree is full!\n");
			else printf("Tree isn't full!\n");
			break;
		case 'S'://노드 탐색
			printf("Search : ");
			cData=_getch();
			_putch(cData);
			printf("\n");
			if(searchItem(ptTree, cData))
				printf("%c exists in the tree.\n", cData);
			else printf("%c doesn't exist in the tree.\n", cData);
			break;

		case'I'://중위 순회출력
			if(isEmpty(ptTree)) printf("Tree is empty!\n");
			else
			{
				printf("Inorder traversal : ");
				traverseInorder(ptTree->ptRoot);
				printf("\n");
			}
			break;
		case'P'://전위 순회출력
			if(isEmpty(ptTree)) printf("Tree is empty!\n");
			else{
				printf("Preorder traversal :");
				traversePreorder(ptTree->ptRoot);
				printf("\n");
			}
			break;
		case'O'://후위 순회출력
			if(isEmpty(ptTree)) printf("Tree is empty!\n");
			else {
				printf("Postorder traversal : ");
				traversePostorder(ptTree->ptRoot);
				printf("\n");
			}
			break;
		case 'Q':
			break;
		default :
			printf("\nWrong command! Retry!\n");
		}
		printTree(ptTree);
	}while(cCommand !='Q');
}
void initTree(BSTREE *ptTree)//트리 초기화 함수 정의
{
	ptTree->nTreeSize=0;
	ptTree->ptRoot=NULL;
}
int isEmpty(BSTREE *ptTree)//empty함수 정의
{
	if(ptTree->nTreeSize==0) return 1;
	else return 0;
}
int isFull(BSTREE *ptTree)//full함수 정의
{
	if(ptTree->nTreeSize==MAX) return 1;
	else return 0;
}
void printTree(BSTREE *ptTree)//트리 모양 출력
{
	int nDepth=0;
	printTreeSub(ptTree->ptRoot, nDepth);
}
void printTreeSub(BSTREENODE *ptNode, int nDepth)
{//트리 모양 서브함수, 재귀호출을 이용해서 트리 모양을 출력
	int i;
	if(ptNode!=NULL)
	{
		nDepth+=2;
		printTreeSub(ptNode->ptLeft, nDepth);

		for(i=1; i<nDepth; i++) printf(" ");

		printf(" %c ", ptNode->cData);

		if((ptNode->ptLeft!=NULL) && (ptNode->ptRight !=NULL)) printf("<");
		else if(ptNode->ptRight !=NULL) printf("＼");
		else if(ptNode->ptLeft !=NULL) printf("/");

		printf("\n");

		printTreeSub(ptNode->ptRight, nDepth);
		nDepth-=2;
	}
}
void insertTree(BSTREE *ptTree, char cData)//insert함수 정의
{
	if(isFull(ptTree))
	{
		printf("Tree is full. Can't insert.");
	}
	else
	{
		BSTREENODE *ptTempNode;//임시 노드생성
		ptTempNode=(BSTREENODE *)malloc(sizeof(BSTREENODE));

		ptTempNode->ptLeft=NULL;//노드 초기화
		ptTempNode->ptRight=NULL;
		ptTempNode->cData=cData;

		if(isEmpty(ptTree))//트리가 비었으면 임시노드가 루트
			ptTree->ptRoot=ptTempNode;
		else{
			if(!searchItem(ptTree, cData))//트리에 삽입하려는 데이터가 존재하는지 확인
				insertTreeSub(ptTree->ptRoot, ptTempNode);//데이터가 없으면 삽입
			else{
				printf("This data already exist in the tree. Can't be inserted!\n");
				free(ptTempNode);//데이터가 있으면 삽입 불가, 임시노드 동적할당 해제
			}
		}
		ptTree->nTreeSize++;//트리 크기 1증가
	}
}
void insertTreeSub(BSTREENODE *ptCurrent, BSTREENODE *ptInsertNode)
{//트리 삽입 서브함수
	//삽입하려는 데이터가 ptCurrent의 데이터보다 크고 ptCurrent의 우측 노드가 존재하면 실행
	if(ptCurrent->cData < ptInsertNode->cData && ptCurrent->ptRight != NULL)
		insertTreeSub(ptCurrent->ptRight, ptInsertNode);//우측 방향으로 재귀호출
	//삽입하려는 데이터가 ptCurrent의 데이터보다 작고 ptCurrent의 좌측 노드가 존재하면 실행
	else if(ptCurrent->cData > ptInsertNode->cData && ptCurrent->ptLeft != NULL)
		insertTreeSub(ptCurrent->ptLeft, ptInsertNode);//좌측 방향으로 재귀호출
	//삽입하려는 데이터가 ptCurrent의 데이터보다 크고 ptCurrent의 우측 노드가 존재하지 않으면 실행
	else if(ptCurrent->cData < ptInsertNode->cData && ptCurrent->ptRight == NULL)
	ptCurrent->ptRight=ptInsertNode; //ptCurrent의 우측 방향에 노드 삽입
	//삽입하려는 데이터가 ptCurrent의 데이터보다 작고 ptCurrent의 좌측 노드가 존재하지 않으면 실행
	else
	ptCurrent->ptLeft=ptInsertNode; //ptCurrent의 좌측 방향에 노드 삽입
}
int searchItem(BSTREE *ptTree, char cData)//search함수 정의
{
	char cResultItem=NULL;
	cResultItem=searchItemSub(ptTree->ptRoot, cData);//서브함수 호출

	if(cResultItem==NULL) return 0;
	else return 1;
}
char searchItemSub(BSTREENODE *ptCurrent, char cData)
{//search 서브함수 재귀 호출을 이용해서 데이터 탐색
	if(ptCurrent != NULL)
	{
		if(ptCurrent->cData < cData)//찾는 값이 크면 우측 방향으로 재귀 호출
			searchItemSub(ptCurrent->ptRight, cData);
		else if(ptCurrent->cData > cData)//찾는 값이 작으면 좌측 방향으로 재귀 호출
			searchItemSub(ptCurrent->ptLeft, cData);
		else//노드의 값과 찾는 값이 일치하면 값 반환
			return ptCurrent->cData;
	}
	else return NULL;//값이 존재하지 않으면 NULL반환
}
void traverseInorder(BSTREENODE *ptNode)
{//중위 순회함수 정의
	if(ptNode){
		traverseInorder(ptNode->ptLeft);
		printf("%c ",ptNode->cData);
		traverseInorder(ptNode->ptRight);
	}
}
void traversePreorder(BSTREENODE *ptNode)
{//전위 순회함수 정의
	if(ptNode){
		printf("%c ",ptNode->cData);
		traversePreorder(ptNode->ptLeft);
		traversePreorder(ptNode->ptRight);
	}
}
void traversePostorder(BSTREENODE *ptNode)
{//후위 순회함수 정의
	if(ptNode){
		traversePostorder(ptNode->ptLeft);
		traversePostorder(ptNode->ptRight);
		printf("%c ", ptNode->cData);
	}
}

