#include<stdio.h>
#include<stdlib.h>
#define IS_FULL(ptr) (!(ptr))

typedef struct listNode* listPointer;
typedef struct listNode{
	int data;
	listPointer link;
}listNode;//노드선언

listPointer create2();//리스트 생성함수
void insert(listPointer *first, listPointer x, int number);//삽입함수
void delete2(listPointer *first, listPointer trail, listPointer x);//삭제함수
void printList(listPointer first);//리스트출력

void main()
{
	listPointer first;
	first = create2();//리스트 초기생성

	insert(&first, first->link, 50);//세 번째 50 삽입
	printList(first);

	insert(&first, first, 30);//두 번째 30 삽입
	printList(first);

	delete2(&first, first, first->link);//두 번째 30 삭제
	printList(first);

	delete2(&first, NULL, first);//첫 번째 10 삭제
	printList(first);

	delete2(&first, first, first->link);//마지막 50 삭제
	printList(first);
}
listPointer create2()
{
	listPointer first, second;
	first = (listPointer)malloc(sizeof(listNode));//노드 2개 생성
	second = (listPointer)malloc(sizeof(listNode));

	first->data = 10;
	second->data = 20;
	first->link = second;//노드연결
	second->link = NULL;//리스트의 끝은 NULL

	return first;//리스트 반환
}
void insert(listPointer *first, listPointer x, int number)//노드 삽입
{
	listPointer temp;
	temp = (listPointer)malloc(sizeof(listNode));
	if (IS_FULL(temp)){//예외처리
		printf("The memory is full\n");
		exit(1);
	}

	temp->data = number;
	if (*first){//first가 null이 아닌 경우 데이터의 입력을 수행
		temp->link = x->link;
		x->link = temp;
		
	}
	else//first가 null인 경우 데이터의 입력을 수행
	{
		temp->link=NULL;
		*first=temp;
	}
}
void delete2(listPointer *first, listPointer trail, listPointer x)//노드 삭제
{
	if (trail!=NULL)//선행노드가 NULL이 아닌경우 실행
		trail->link = x->link;
	else//NULL인 경우
		(*first) = (*first)->link;

	free(x);//힙 비우기
}
void printList(listPointer first)//리스트 출력
{
	listPointer temp = first;

	printf("The list contains: ");
	for (; temp != NULL; temp = temp->link)
		printf("%d ", temp->data);
	printf("\n");
}