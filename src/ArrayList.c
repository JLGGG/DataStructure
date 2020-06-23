#include<stdio.h>
#include<stdlib.h>

#define MAX_LIST_SIZE 50 //배열 리스트의 최대 크기

typedef int element;//배열 요소 타입 정의

typedef struct{
	int list[MAX_LIST_SIZE];//배열 정의
	int length;//현재 배열에 저장된 항목들의 개수
}ArrayListType;

void initList(ArrayListType*L);//리스트 초기화 함수
void printList(ArrayListType*L);//리스트 출력 함수
int is_empty(ArrayListType*L);//리스트가 비어있는지 확인하는 함수
int is_full(ArrayListType*L);//리스트가 가득 차 있는 지 확인하는 함수
void add(ArrayListType*L, int position, element item);//리스트 L의 position 위치에 item을 추가
element rem(ArrayListType*L, int position);//리스트에서 position 위치의 item을 삭제

void main()
{
	element item;

	ArrayListType*L = (ArrayListType*)malloc(sizeof(ArrayListType));//동적할당
	initList(L);//배열 초기화

	printf("초기 데이터\t: ");
	printList(L);
	printf("\n");

	add(L, 2, 30);
	printf("30이 추가됨\t: ");
	printList(L);
	printf("\n");

	item = rem(L, 5);
	if (item != -1) printf("%d 데이터가 삭제됨\t: ", item);
	printList(L);
	printf("\n");

	add(L, 5, 60);
	printf("60이 추가됨\t:");
	printList(L);
	printf("\n");

	item = rem(L, 8);
	if (item != -1)printf("%d 데이터가 삭제됨\t", item);
	printList(L);
	printf("\n\n");

	free(L);//동적할당 해제
}
//리스트 초기화 함수
void initList(ArrayListType*L)
{
	int initArray[] = { 10, 20, 40, 50, 110, 70, 80, 300, 90, 100 };
	int cnt = 0;

	for (cnt = 0; cnt < sizeof(initArray) / sizeof(int); cnt++)
		L->list[cnt] = initArray[cnt];

	L->length = sizeof(initArray) / sizeof(int);
}
//리스트가 비어있는지 확인
int is_empty(ArrayListType*L)
{
	return(L->length == 0);
}
//리스트가 가득찼는지 확인
int is_full(ArrayListType*L)
{
	return(L->length == MAX_LIST_SIZE);

}
//리스트 출력
void printList(ArrayListType*L)
{
	int i;

	if (is_empty(L))//리스트가 비어있는 경우
	{
		printf("List is empty!\n");
	}
	else
	{
		printf("( ");
		for (i = 0; i < L->length; i++)
		{
			printf("%d ", L->list[i]);
		}
		if (i == L->length)
			printf(")");
	}
}
//리스트 position위치에 item을 입력하는 함수
void add(ArrayListType*L, int position, element item)
{
	if (is_full(L))
		printf("List is full! Can't insert.\n");
	else if ((position >= 0) && (position <= L->length))
	{
		int i;
		for (i = L->length - 1; i >= position; i--)
		{
			L->list[i + 1] = L->list[i];//삽입할 위치를 비우기 위해서 데이터들을 한 칸식 뒤로 이동
		}
		L->list[position] = item;//item 삽입
		L->length++;//배열 길이 증가

	}
	else
	{
		printf("삽입 위치 오류!");
	}
}
//리스트에서 item을 삭제하는 함수
element rem(ArrayListType*L, int position)
{
	int i;
	element item;

	if (position < 0 || position >= L->length)
	{
		printf("삭제 위치 오류!");
		return(-1);
	}

	item = L->list[position];//삭제할 데이터 백업

	for (i = position; i < L->length - 1; i++)
		L->list[i] = L->list[i + 1];//삭제할 위치의 값을 지우기 위해서 뒤에 있는 값으로 덮어 씌운다.

	L->length--;//배열 길이 감소
	return item;//백업된 데이터 반환
}
