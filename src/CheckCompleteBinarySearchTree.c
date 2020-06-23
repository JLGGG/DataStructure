#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>
#include<memory.h>

#define MAX 40

typedef struct TreeNode{//Ʈ����� ����
	char cData;
	struct TreeNode *ptLeft;
	struct TreeNode *ptRight;
	int numNode;
}BSTREENODE;

typedef struct Tree{//Ʈ�� ����
	int nTreeSize;
	BSTREENODE *ptRoot;
}BSTREE;

void initTree(BSTREE *ptTree);//Ʈ�� �ʱ�ȭ
void printTree(BSTREE *ptTree);//Ʈ�� ����Լ�
void printTreeSub(BSTREENODE *ptNode, int nDepth);//Ʈ�� ��� �����Լ�
int isEmpty(BSTREE *ptTree);//Ʈ���� ������� Ȯ��
int isFull(BSTREE *ptTree);//Ʈ���� full���� Ȯ��
void insertTree(BSTREE *ptTree, char cData);//Ʈ�� ��� ����
void insertTreeSub(BSTREENODE *ptCurrent, BSTREENODE *ptInsertNode, int depth);//���� �����Լ�
int searchItem(BSTREE *ptTree, char cData);//search�Լ�
char searchItemSub(BSTREENODE *ptCurrent, char cData);//serarch �����Լ�
void traverseInorder(BSTREENODE *ptNode);//���� ��ȸ�Լ�
void traversePreorder(BSTREENODE *ptNode);//���� ��ȸ�Լ�
void traversePostorder(BSTREENODE *ptNode);//���� ��ȸ�Լ�
int isPerfect(BSTREE *ptTree, int *perfectArr);//���� ���� Ʈ�� Ȯ�� �Լ�
void isPerfectSub(BSTREENODE *ptCurrent, int *perfectArr);//isPerfect �����Լ�


void main()
{
	BSTREE *ptTree;//Ʈ�� ����
	char cCommand, cData;
	int perfectArr[MAX];

	printf("*******************Choose Command!! ************************\n");
	printf("+ : insert S: search item\n");
	printf("I : inorder P : preorder O : postorder \n");
	printf("F : full check, E: empty check, C : complete binary tree, Q :Quit\n");
	printf("************************************************************\n");

	ptTree=(BSTREE*)malloc(sizeof(BSTREE));//Ʈ�� ����

	initTree(ptTree);//Ʈ�� �ʱ�ȭ

	do{
		printf("Command :");
		cCommand=_getch();
		cCommand=toupper(cCommand);
		_putch(cCommand);
		printf("\n");

		switch(cCommand)
		{
		case'+'://��� �߰�
			printf("Insert data : ");
			cData=_getch();
			_putch(cData);
			printf("\n");
			insertTree(ptTree, cData);
			break;
		case 'E'://Ʈ�� ������� Ȯ��
			if(isEmpty(ptTree)) printf("Tree is empty\n");
			else printf("Tree isn't full!\n");
			break;
		case 'F'://Ʈ���� full���� Ȯ��
			if(isFull(ptTree)) printf("Tree is full!\n");
			else printf("Tree isn't full!\n");
			break;
		case 'S'://��� Ž��
			printf("Search : ");
			cData=_getch();
			_putch(cData);
			printf("\n");
			if(searchItem(ptTree, cData))
				printf("%c exists in the tree.\n", cData);
			else printf("%c doesn't exist in the tree.\n", cData);
			break;

		case'I'://���� ��ȸ���
			if(isEmpty(ptTree)) printf("Tree is empty!\n");
			else
			{
				printf("Inorder traversal : ");
				traverseInorder(ptTree->ptRoot);
				printf("\n");
			}
			break;
		case'P'://���� ��ȸ���
			if(isEmpty(ptTree)) printf("Tree is empty!\n");
			else{
				printf("Preorder traversal :");
				traversePreorder(ptTree->ptRoot);
				printf("\n");
			}
			break;
		case'O'://���� ��ȸ���
			if(isEmpty(ptTree)) printf("Tree is empty!\n");
			else {
				printf("Postorder traversal : ");
				traversePostorder(ptTree->ptRoot);
				printf("\n");
			}
			break;
		case'C'://��������Ʈ�� Ȯ��
			memset(perfectArr, 0, sizeof(int)*MAX);
			if(isPerfect(ptTree, perfectArr))
				printf("Complete binary tree\n");
			else printf("Binary Tree is not completely\n");
			break;
		case 'Q':
			break;
		default :
			printf("\nWrong command! Retry!\n");
		}
		printTree(ptTree);
	}while(cCommand !='Q');
}
void initTree(BSTREE *ptTree)//Ʈ�� �ʱ�ȭ �Լ� ����
{
	ptTree->nTreeSize=0;
	ptTree->ptRoot=NULL;
}
int isEmpty(BSTREE *ptTree)//empty�Լ� ����
{
	if(ptTree->nTreeSize==0) return 1;
	else return 0;
}
int isFull(BSTREE *ptTree)//full�Լ� ����
{
	if(ptTree->nTreeSize==MAX) return 1;
	else return 0;
}
void printTree(BSTREE *ptTree)//Ʈ�� ��� ���
{
	int nDepth=0;
	printTreeSub(ptTree->ptRoot, nDepth);
}
void printTreeSub(BSTREENODE *ptNode, int nDepth)
{//Ʈ�� ��� �����Լ�, ���ȣ���� �̿��ؼ� Ʈ�� ����� ���
	int i;
	if(ptNode!=NULL)
	{
		nDepth+=2;
		printTreeSub(ptNode->ptLeft, nDepth);

		for(i=1; i<nDepth; i++) printf(" ");

		printf(" %c ", ptNode->cData);

		if((ptNode->ptLeft!=NULL) && (ptNode->ptRight !=NULL)) printf("<");
		else if(ptNode->ptRight !=NULL) printf("��");
		else if(ptNode->ptLeft !=NULL) printf("/");

		printf("\n");

		printTreeSub(ptNode->ptRight, nDepth);
		nDepth-=2;
	}
}
void insertTree(BSTREE *ptTree, char cData)//insert�Լ� ����
{
	int num=1;

	if(isFull(ptTree))
	{
		printf("Tree is full. Can't insert.");
	}
	else
	{
		BSTREENODE *ptTempNode;//�ӽ� ������
		ptTempNode=(BSTREENODE *)malloc(sizeof(BSTREENODE));

		ptTempNode->ptLeft=NULL;//��� �ʱ�ȭ
		ptTempNode->ptRight=NULL;
		ptTempNode->cData=cData;
		ptTempNode->numNode=num;

		if(isEmpty(ptTree))//Ʈ���� ������� �ӽó�尡 ��Ʈ
			ptTree->ptRoot=ptTempNode;
		else{
			if(!searchItem(ptTree, cData))//Ʈ���� �����Ϸ��� �����Ͱ� �����ϴ��� Ȯ��
				insertTreeSub(ptTree->ptRoot, ptTempNode, num);//�����Ͱ� ������ ����
			else{
				printf("This data already exist in the tree. Can't be inserted!\n");
				free(ptTempNode);//�����Ͱ� ������ ���� �Ұ�, �ӽó�� �����Ҵ� ����
			}
		}
		ptTree->nTreeSize++;//Ʈ�� ũ�� 1����
	}
}
void insertTreeSub(BSTREENODE *ptCurrent, BSTREENODE *ptInsertNode, int depth)
{//�Ű�����depth�� ���ԵǴ� ����� ��ġ �ε����� ���Ѵ�.
	//�����Ϸ��� �����Ͱ� ptCurrent�� �����ͺ��� ũ�� ptCurrent�� ���� ��尡 �����ϸ� ����
	if(ptCurrent->cData < ptInsertNode->cData && ptCurrent->ptRight != NULL)
		insertTreeSub(ptCurrent->ptRight, ptInsertNode, (depth*2)+1);//depth�� *2+1�� �Ѵ�.
	//�����Ϸ��� �����Ͱ� ptCurrent�� �����ͺ��� �۰� ptCurrent�� ���� ��尡 �����ϸ� ����
	else if(ptCurrent->cData > ptInsertNode->cData && ptCurrent->ptLeft != NULL)
		insertTreeSub(ptCurrent->ptLeft, ptInsertNode, (depth*2));//depth�� *2�� �Ѵ�.
	//�����Ϸ��� �����Ͱ� ptCurrent�� �����ͺ��� ũ�� ptCurrent�� ���� ��尡 �������� ������ ����
	else if(ptCurrent->cData < ptInsertNode->cData && ptCurrent->ptRight == NULL)
	{
		ptCurrent->ptRight=ptInsertNode; //ptCurrent�� ���� ���⿡ ��� ����
		ptInsertNode->numNode=(depth*2)+1;//Ʈ���� ���ԵǴ� ����� ��ġ �ε����� �־��ش�.
	}
	//�����Ϸ��� �����Ͱ� ptCurrent�� �����ͺ��� �۰� ptCurrent�� ���� ��尡 �������� ������ ����
	else{
		ptCurrent->ptLeft=ptInsertNode; //ptCurrent�� ���� ���⿡ ��� ����
		ptInsertNode->numNode=(depth*2);
	}
}
int searchItem(BSTREE *ptTree, char cData)//search�Լ� ����
{
	char cResultItem=NULL;
	cResultItem=searchItemSub(ptTree->ptRoot, cData);//�����Լ� ȣ��

	if(cResultItem==NULL) return 0;
	else return 1;
}
char searchItemSub(BSTREENODE *ptCurrent, char cData)
{//search �����Լ� ��� ȣ���� �̿��ؼ� ������ Ž��
	if(ptCurrent != NULL)
	{
		if(ptCurrent->cData < cData)//ã�� ���� ũ�� ���� �������� ��� ȣ��
			searchItemSub(ptCurrent->ptRight, cData);
		else if(ptCurrent->cData > cData)//ã�� ���� ������ ���� �������� ��� ȣ��
			searchItemSub(ptCurrent->ptLeft, cData);
		else//����� ���� ã�� ���� ��ġ�ϸ� �� ��ȯ
			return ptCurrent->cData;
	}
	else return NULL;//���� �������� ������ NULL��ȯ
}
void traverseInorder(BSTREENODE *ptNode)
{//���� ��ȸ�Լ� ����
	if(ptNode){
		traverseInorder(ptNode->ptLeft);
		printf("%c ",ptNode->cData);
		traverseInorder(ptNode->ptRight);
	}
}
void traversePreorder(BSTREENODE *ptNode)
{//���� ��ȸ�Լ� ����
	if(ptNode){
		printf("%c ",ptNode->cData);
		traversePreorder(ptNode->ptLeft);
		traversePreorder(ptNode->ptRight);
	}
}
void traversePostorder(BSTREENODE *ptNode)
{//���� ��ȸ�Լ� ����
	if(ptNode){
		traversePostorder(ptNode->ptLeft);
		traversePostorder(ptNode->ptRight);
		printf("%c ", ptNode->cData);
	}
}
int isPerfect(BSTREE *ptTree, int *perfectArr)
{//��������Ʈ�� Ȯ�� �Լ� ����
	int i;
	isPerfectSub(ptTree->ptRoot, perfectArr);//�����Լ� ȣ��

	//���Ե� ����� ������ŭ �迭�� ��ȸ�Ͽ� 0�� �߰ߵǸ� ��������Ʈ�� �ƴ�
	for(i=1; i<=ptTree->nTreeSize; i++)
	{
		if(perfectArr[i]==0)
			return 0;
	}
	return 1;
}
void isPerfectSub(BSTREENODE *ptCurrent, int *perfectArr)
{
	if(ptCurrent){//Ʈ���� �ִ� ���� ��ġ �ε����� ������ �����Ƿ� ��ġ �ε����� �̿��ؼ� �迭�� ����
		isPerfectSub(ptCurrent->ptLeft, perfectArr);
		perfectArr[ptCurrent->numNode]=ptCurrent->cData;
		isPerfectSub(ptCurrent->ptRight, perfectArr);
	}
}