#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 10//����Ʈ�� �ִ� ũ��

#define true 1
#define false 0

struct ListNode{//����Ʈ ��� ����ü
	char data;//���� data
	struct ListNode *next;//���� ����� ������
	struct ListNode *previous;//���� ����� ������
};
typedef struct ListNode LISTNODE;

struct List{//����Ʈ ����ü
	int listSize;//����Ʈ�� ũ��
	LISTNODE *cursor;//���� cursor�� ��ġ
	LISTNODE *first;//ù��° ����� �ּ�
};
typedef struct List LIST;

void initList(LIST *list);//����Ʈ �ʱ�ȭ �Լ�
void printList(LIST *list);//����Ʈ ��� �Լ�
int isEmpty(LIST *list);//����Ʈ�� ����ִ��� Ȯ���ϴ� �Լ�
int isFull(LIST *list);//����Ʈ�� ���� �� �ִ� �� Ȯ���ϴ� �Լ�
void insertListItem(LIST *list, char data);//����Ʈ�� data�� �Է��ϴ� �Լ�
void deleteListItem(LIST *list, char *data);//����Ʈ�� data�� �����ϴ� �Լ�
void moveLeft(LIST *list);//����Ʈ���� cursor�� �������� �̵���Ű�� �Լ�
void moveRight(LIST *list);//����Ʈ���� cursor�� ���������� �̵���Ű�� �Լ�

void main()
{
	LIST *list;
	char cmd;
	char data;

	printf("**************Choose Command!!*************\n");
	printf("+: insert, -: delete, F: full check, E: empty check\n");
	printf("L: move left, R: move right, Q: Quit\n");
	printf("*******************************************\n");
	list = (LIST *)malloc(sizeof(LIST));//���� �޸� �Ҵ�

	initList(list);//����Ʈ �ʱ�ȭ

	do{//Ŀ�ǵ� �Է�
		printf("Command: ");
		cmd = getch();
		putch(cmd);
		printf("\n");
		cmd = toupper(cmd);//�빮�ڷ� ��ȯ

		switch (cmd)
		{
		case'+'://data �Է�
			printf("Type the item that be inserted :");
			data = getch();
			putch(data);
			printf("\n");
			insertListItem(list, data);
			break;
		case '-'://data ����
			deleteListItem(list, &data);
			printf("Deleted item : %c\n", data);
			break;
		case 'E'://����ִ� �� Ȯ��
			if (isEmpty(list)) printf("List is empty!\n");
			else printf("List isn't empty\n");
			break;
		case 'F'://����á�� �� Ȯ��
			if (isFull(list)) printf("List is full!\n");
			else printf("List isn't full!\n");
			break;
		case 'L'://�������� cursor �̵�
			moveLeft(list);
			break;
		case 'R'://���������� cursor �̵�
			moveRight(list);
			break;
		case 'Q'://����
			break;
		default://�߸��� Ŀ�ǵ� �Է� ��
			printf("\nWrong command! Retry!\n");
		}

		printList(list);//����Ʈ ���
	} while (cmd != 'Q');
}
void initList(LIST *list)//����Ʈ �ʱ�ȭ �Լ�
{
	list->listSize = 0;//����Ʈ ũ�� 0
	list->cursor = NULL;
	list->first = NULL;
}
void printList(LIST *list)//����Ʈ ���
{
	LISTNODE *tempCursor;//�ӽ� ��� ������ ����
	tempCursor = list->first;

	if (isEmpty(list))//����Ʈ�� ����ִ� ���
	{
		printf("List is empty!\n");
	}
	else
	{
		printf("Item list.\n");
		do
		{
			if (tempCursor== list->cursor)
				printf("[%c] ", tempCursor->data);
			else
				printf(" %c ", tempCursor->data);
			tempCursor = tempCursor->next;//���� ��ġ�� cursor �̵�
		} while (tempCursor != list->first);//����Ʈ�� ��� ��� ��ȸ
		printf("\n");
	}
}
int isEmpty(LIST *list)//����Ʈ�� ����ִ��� Ȯ��
{
	if (list->first == NULL) return true;
	else return false;
}
int isFull(LIST *list)//����Ʈ�� ����á���� Ȯ��
{
	if (list->listSize == MAX) return true;
	else return false;
}
//���� ���� ���Ḯ��Ʈ�� data�� �Է��ϴ� �Լ�
void insertListItem(LIST *list, char data)
{
	if (isFull(list))
	{
		printf("List is full! can't insert.\n");
	}
	else
	{
		LISTNODE *tempNode;//���ο� ��� ����
		tempNode = (LISTNODE*)malloc(sizeof(LISTNODE));
		tempNode->data = data;
		if (isEmpty(list))//����Ʈ�� ����ִ� ���
		{
			tempNode->next = tempNode;
			tempNode->previous = tempNode;
			list->first = tempNode;
			list->cursor = tempNode;
		}
		else if (list->cursor->next == list->first)//����Ʈ�� �������� ���
		{
			tempNode->next = list->cursor->next;
			tempNode->previous = list->cursor;
			list->cursor->next = tempNode;
			list->first->previous=tempNode;
			list->cursor = tempNode;
		}
		else//����Ʈ�� �߰��� ���
		{
			tempNode->next = list->cursor->next;
			tempNode->previous = list->cursor;
			list->cursor->next->previous = tempNode;
			list->cursor->next = tempNode;
			list->cursor = tempNode;
		}
		list->listSize++;//����Ʈ ũ�� ����
	
	}
}
//���� ���� ���Ḯ��Ʈ���� data�� �����ϴ� �Լ�
void deleteListItem(LIST *list, char *data)
{
	//������ data�� ������ �ӽ� ����
	char deleted = NULL;
	if (isEmpty(list))
	{
		printf("List is empty! can't delete\n");
	}
	else
	{
		//�ӽ÷� ����� ������ ����
		LISTNODE *tempNode;

		tempNode = list->cursor;//������ ����� ��ġ
		deleted = list->cursor->data;

		//����Ʈ�� ��尡 �Ѱ��� �ִ� ���
		if (list->listSize == 1)
		{
			list->cursor = NULL;
			list->first = NULL;
		}
		//cursor�� ����Ʈ�� ù ��忡 �ִ� ���
		else if (list->first == list->cursor)
		{
			list->first = list->cursor->next;
			list->cursor->next->previous = list->cursor->previous;
			list->cursor->next->previous->next=list->cursor->next;
			list->cursor = list->cursor->next;
			
		}
		//cursor�� ����Ʈ�� ������ ��忡 �ִ� ���
		else if (list->cursor->next == list->first)
		{
			list->cursor->previous->next=list->first;
			list->first->previous=list->cursor->previous;
			list->cursor=list->cursor->previous;
		}
		else//�� ���� ���
		{
			list->cursor->previous->next = list->cursor->next;
			list->cursor->next->previous = list->cursor->previous;
			list->cursor = list->cursor->next;
		}
		list->listSize--;

		free(tempNode);//������ ����� �޸� ����
	}

	*data = deleted;//������ data�� ��ȯ
}
void moveLeft(LIST *list)//cursor�� �������� �̵���Ű�� �Լ�
{
	if (isEmpty(list))
	{
		printf("List is empty! Can't move.\n");
	}
	else
	{
		//����Ʈ�� ��尡 1���ۿ� ���ų� cursor�� ù ��忡 �ִ� ���
		if (list->first == list->cursor && list->listSize == 1)
		{
			printf("The cursor is in the first item! Can't move\n");
		}
		else
		{
			list->cursor = list->cursor->previous;
		}

	}
}
void moveRight(LIST *list)//cursor�� ���������� �̵���Ű�� �Լ�
{
	if (isEmpty(list))
	{
		printf("List is empty! Can't move.\n");
	}
	else
	{
		if (list->cursor->next == NULL && list->listSize == 1)
		{
			printf("The cursor is in the first item! Can't move\n");
		}
		else
		{
			list->cursor = list->cursor->next;
		}
	}
}

