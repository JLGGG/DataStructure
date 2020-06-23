#include<stdio.h>
#include<stdlib.h>
#define IS_FULL(ptr) (!(ptr))

typedef struct listNode* listPointer;
typedef struct listNode{
	int data;
	listPointer link;
}listNode;//��弱��

listPointer create2();//����Ʈ �����Լ�
void insert(listPointer *first, listPointer x, int number);//�����Լ�
void delete2(listPointer *first, listPointer trail, listPointer x);//�����Լ�
void printList(listPointer first);//����Ʈ���

void main()
{
	listPointer first;
	first = create2();//����Ʈ �ʱ����

	insert(&first, first->link, 50);//�� ��° 50 ����
	printList(first);

	insert(&first, first, 30);//�� ��° 30 ����
	printList(first);

	delete2(&first, first, first->link);//�� ��° 30 ����
	printList(first);

	delete2(&first, NULL, first);//ù ��° 10 ����
	printList(first);

	delete2(&first, first, first->link);//������ 50 ����
	printList(first);
}
listPointer create2()
{
	listPointer first, second;
	first = (listPointer)malloc(sizeof(listNode));//��� 2�� ����
	second = (listPointer)malloc(sizeof(listNode));

	first->data = 10;
	second->data = 20;
	first->link = second;//��忬��
	second->link = NULL;//����Ʈ�� ���� NULL

	return first;//����Ʈ ��ȯ
}
void insert(listPointer *first, listPointer x, int number)//��� ����
{
	listPointer temp;
	temp = (listPointer)malloc(sizeof(listNode));
	if (IS_FULL(temp)){//����ó��
		printf("The memory is full\n");
		exit(1);
	}

	temp->data = number;
	if (*first){//first�� null�� �ƴ� ��� �������� �Է��� ����
		temp->link = x->link;
		x->link = temp;
		
	}
	else//first�� null�� ��� �������� �Է��� ����
	{
		temp->link=NULL;
		*first=temp;
	}
}
void delete2(listPointer *first, listPointer trail, listPointer x)//��� ����
{
	if (trail!=NULL)//�����尡 NULL�� �ƴѰ�� ����
		trail->link = x->link;
	else//NULL�� ���
		(*first) = (*first)->link;

	free(x);//�� ����
}
void printList(listPointer first)//����Ʈ ���
{
	listPointer temp = first;

	printf("The list contains: ");
	for (; temp != NULL; temp = temp->link)
		printf("%d ", temp->data);
	printf("\n");
}