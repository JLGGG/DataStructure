#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX 10//리스트의 최대 크기

#define true 1
#define false 0

struct ListNode{//리스트 노드 구조체
	char data;//저장 data
	struct ListNode *next;//다음 노드의 포인터
	struct ListNode *previous;//이전 노드의 포인터
};
typedef struct ListNode LISTNODE;

struct List{//리스트 구조체
	int listSize;//리스트의 크기
	LISTNODE *cursor;//현재 cursor의 위치
	LISTNODE *first;//첫번째 노드의 주소
};
typedef struct List LIST;

void initList(LIST *list);//리스트 초기화 함수
void printList(LIST *list);//리스트 출력 함수
int isEmpty(LIST *list);//리스트가 비어있는지 확인하는 함수
int isFull(LIST *list);//리스트가 가득 차 있는 지 확인하는 함수
void insertListItem(LIST *list, char data);//리스트에 data를 입력하는 함수
void deleteListItem(LIST *list, char *data);//리스트에 data를 삭제하는 함수
void moveLeft(LIST *list);//리스트에서 cursor를 왼쪽으로 이동시키는 함수
void moveRight(LIST *list);//리스트에서 cursor를 오른쪽으로 이동시키는 함수

void main()
{
	LIST *list;
	char cmd;
	char data;

	printf("**************Choose Command!!*************\n");
	printf("+: insert, -: delete, F: full check, E: empty check\n");
	printf("L: move left, R: move right, Q: Quit\n");
	printf("*******************************************\n");
	list = (LIST *)malloc(sizeof(LIST));//동적 메모리 할당

	initList(list);//리스트 초기화

	do{//커맨드 입력
		printf("Command: ");
		cmd = getch();
		putch(cmd);
		printf("\n");
		cmd = toupper(cmd);//대문자로 변환

		switch (cmd)
		{
		case'+'://data 입력
			printf("Type the item that be inserted :");
			data = getch();
			putch(data);
			printf("\n");
			insertListItem(list, data);
			break;
		case '-'://data 삭제
			deleteListItem(list, &data);
			printf("Deleted item : %c\n", data);
			break;
		case 'E'://비어있는 지 확인
			if (isEmpty(list)) printf("List is empty!\n");
			else printf("List isn't empty\n");
			break;
		case 'F'://가득찼는 지 확인
			if (isFull(list)) printf("List is full!\n");
			else printf("List isn't full!\n");
			break;
		case 'L'://왼쪽으로 cursor 이동
			moveLeft(list);
			break;
		case 'R'://오른쪽으로 cursor 이동
			moveRight(list);
			break;
		case 'Q'://종료
			break;
		default://잘못된 커맨드 입력 시
			printf("\nWrong command! Retry!\n");
		}

		printList(list);//리스트 출력
	} while (cmd != 'Q');
}
void initList(LIST *list)//리스트 초기화 함수
{
	list->listSize = 0;//리스트 크기 0
	list->cursor = NULL;
	list->first = NULL;
}
void printList(LIST *list)//리스트 출력
{
	LISTNODE *tempCursor;//임시 사용 포인터 선언
	tempCursor = list->first;

	if (isEmpty(list))//리스트가 비어있는 경우
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
			tempCursor = tempCursor->next;//다음 위치로 cursor 이동
		} while (tempCursor != list->first);//리스트의 모든 노드 순회
		printf("\n");
	}
}
int isEmpty(LIST *list)//리스트가 비어있는지 확인
{
	if (list->first == NULL) return true;
	else return false;
}
int isFull(LIST *list)//리스트가 가득찼는지 확인
{
	if (list->listSize == MAX) return true;
	else return false;
}
//원형 이중 연결리스트에 data를 입력하는 함수
void insertListItem(LIST *list, char data)
{
	if (isFull(list))
	{
		printf("List is full! can't insert.\n");
	}
	else
	{
		LISTNODE *tempNode;//새로운 노드 선언
		tempNode = (LISTNODE*)malloc(sizeof(LISTNODE));
		tempNode->data = data;
		if (isEmpty(list))//리스트가 비어있는 경우
		{
			tempNode->next = tempNode;
			tempNode->previous = tempNode;
			list->first = tempNode;
			list->cursor = tempNode;
		}
		else if (list->cursor->next == list->first)//리스트가 마지막인 경우
		{
			tempNode->next = list->cursor->next;
			tempNode->previous = list->cursor;
			list->cursor->next = tempNode;
			list->first->previous=tempNode;
			list->cursor = tempNode;
		}
		else//리스트가 중간인 경우
		{
			tempNode->next = list->cursor->next;
			tempNode->previous = list->cursor;
			list->cursor->next->previous = tempNode;
			list->cursor->next = tempNode;
			list->cursor = tempNode;
		}
		list->listSize++;//리스트 크기 증가
	
	}
}
//원형 이중 연결리스트에서 data를 삭제하는 함수
void deleteListItem(LIST *list, char *data)
{
	//삭제된 data를 저장할 임시 변수
	char deleted = NULL;
	if (isEmpty(list))
	{
		printf("List is empty! can't delete\n");
	}
	else
	{
		//임시로 사용할 포인터 선언
		LISTNODE *tempNode;

		tempNode = list->cursor;//삭제될 노드의 위치
		deleted = list->cursor->data;

		//리스트에 노드가 한개만 있는 경우
		if (list->listSize == 1)
		{
			list->cursor = NULL;
			list->first = NULL;
		}
		//cursor가 리스트의 첫 노드에 있는 경우
		else if (list->first == list->cursor)
		{
			list->first = list->cursor->next;
			list->cursor->next->previous = list->cursor->previous;
			list->cursor->next->previous->next=list->cursor->next;
			list->cursor = list->cursor->next;
			
		}
		//cursor가 리스트의 마지막 노드에 있는 경우
		else if (list->cursor->next == list->first)
		{
			list->cursor->previous->next=list->first;
			list->first->previous=list->cursor->previous;
			list->cursor=list->cursor->previous;
		}
		else//그 외의 경우
		{
			list->cursor->previous->next = list->cursor->next;
			list->cursor->next->previous = list->cursor->previous;
			list->cursor = list->cursor->next;
		}
		list->listSize--;

		free(tempNode);//삭제할 노드의 메모리 해제
	}

	*data = deleted;//삭제된 data를 반환
}
void moveLeft(LIST *list)//cursor를 왼쪽으로 이동시키는 함수
{
	if (isEmpty(list))
	{
		printf("List is empty! Can't move.\n");
	}
	else
	{
		//리스트에 노드가 1개밖에 없거나 cursor가 첫 노드에 있는 경우
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
void moveRight(LIST *list)//cursor를 오른쪽으로 이동시키는 함수
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

