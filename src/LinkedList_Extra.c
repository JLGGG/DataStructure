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
listPointer circul_end(listPointer first);//원형 연결 리스트의 마지막 노드를 찾는 함수
listPointer first_end_Link(listPointer first_node);//리스트의 처음과 마지막을 연결하는 함수
void delete_node_at(listPointer first, int pos);//지정된 노드를 삭제하는 함수

void main()
{
	listPointer first, p;
	first = create2();//리스트 초기생성

	insert(&first, first->link, 50);//세 번째 50 삽입
	printList(first);

	insert(&first, first, 30);//두 번째 30 삽입
	printList(first);

	delete2(&first, first, first->link);//두 번째 30 삭제
	printList(first);

	p=circul_end(first);//원형 리스트의 마지막 노드 찾는 함수 호출
	delete2(&first, p, first);//첫 번째 10 삭제
	printList(first);

	insert(&first, first, 70);//두 번째 70 삽입
	printList(first);

	insert(&first, first->link, 90);//세 번째 90 삽입
	printList(first);

	delete_node_at(first, 7);//마지막에 있는 50 삭제
	printList(first);
}
listPointer create2()
{// 두 개의 노드를 가진 원형 연결리스트 생성
	listPointer first, second;
	first = (listPointer)malloc(sizeof(listNode));//노드 2개 생성
	second = (listPointer)malloc(sizeof(listNode));

	first->data = 10;
	second->data = 20;
	first->link = second;//노드연결
	first=first_end_Link(first);//첫 노드, 마지막 노드 원형 연결 함수

	return first;//원형 연결된 리스트 반환
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
	if (*first){
		temp->link = x->link;//노드연결
		x->link = temp;	
	}
	else
	{
		temp->link=NULL;
		*first=temp;
	}

}
void delete2(listPointer *first, listPointer trail, listPointer x)
{//리스트로부터 x 노드를 삭제, trail은 삭제될 x의 선행 노드이며 first는 리스트의 시작
	if (x == *first) {//삭제될 노드가 리스트의 첫 번째 노드이면 실행
		trail->link = x->link;//x를 제외한 리스트 연결
		(*first)=trail->link;//*first는 리스트 자체이므로, x를 free하면 리스트가 지워진다. 그러므로 x 다음 노드로 이동
	}
	else//x가 첫 번째 노드가 아닌 경우
		trail->link=x->link;

	free(x);//힙 비우기
}
void printList(listPointer first)//리스트 출력
{
	listPointer temp = first;

	printf("The list contains: ");
	do{//원형연결리스트는 do~while를 사용해서 출력
		printf("%d ", temp->data);
		temp = temp->link;
	} while (temp != first);//리스트의 끝은 리스트의 머리와 비교해서 찾는다.
	printf("\n");
}
listPointer circul_end(listPointer first)
{//원형연결리스트의 마지막 노드를 찾는 함수
	listPointer p = first;

	while ((p->link) != first)
		p = p->link;

	return p;
}
listPointer first_end_Link(listPointer first_node)
{//첫 노드와 마지막 노드를 연결하는 함수
	first_node->link->link=first_node;

	return first_node;
}
void delete_node_at(listPointer first, int pos)
{//n번째 노드를 삭제하는 함수, n은 0부터 시작
	int i;
	listPointer p=first;
	if(pos<0) return ;//음수이면 종료
	for(i=0; i<pos-1; i++)
		p=p->link;//선행노드를 찾아준다.

	delete2(&first, p, p->link);//선행노드와 삭제할 노드를 함수의 매개변수로 전달
}
