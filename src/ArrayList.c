#include<stdio.h>
#include<stdlib.h>

#define MAX_LIST_SIZE 50 //�迭 ����Ʈ�� �ִ� ũ��

typedef int element;//�迭 ��� Ÿ�� ����

typedef struct{
	int list[MAX_LIST_SIZE];//�迭 ����
	int length;//���� �迭�� ����� �׸���� ����
}ArrayListType;

void initList(ArrayListType*L);//����Ʈ �ʱ�ȭ �Լ�
void printList(ArrayListType*L);//����Ʈ ��� �Լ�
int is_empty(ArrayListType*L);//����Ʈ�� ����ִ��� Ȯ���ϴ� �Լ�
int is_full(ArrayListType*L);//����Ʈ�� ���� �� �ִ� �� Ȯ���ϴ� �Լ�
void add(ArrayListType*L, int position, element item);//����Ʈ L�� position ��ġ�� item�� �߰�
element rem(ArrayListType*L, int position);//����Ʈ���� position ��ġ�� item�� ����

void main()
{
	element item;

	ArrayListType*L = (ArrayListType*)malloc(sizeof(ArrayListType));//�����Ҵ�
	initList(L);//�迭 �ʱ�ȭ

	printf("�ʱ� ������\t: ");
	printList(L);
	printf("\n");

	add(L, 2, 30);
	printf("30�� �߰���\t: ");
	printList(L);
	printf("\n");

	item = rem(L, 5);
	if (item != -1) printf("%d �����Ͱ� ������\t: ", item);
	printList(L);
	printf("\n");

	add(L, 5, 60);
	printf("60�� �߰���\t:");
	printList(L);
	printf("\n");

	item = rem(L, 8);
	if (item != -1)printf("%d �����Ͱ� ������\t", item);
	printList(L);
	printf("\n\n");

	free(L);//�����Ҵ� ����
}
//����Ʈ �ʱ�ȭ �Լ�
void initList(ArrayListType*L)
{
	int initArray[] = { 10, 20, 40, 50, 110, 70, 80, 300, 90, 100 };
	int cnt = 0;

	for (cnt = 0; cnt < sizeof(initArray) / sizeof(int); cnt++)
		L->list[cnt] = initArray[cnt];

	L->length = sizeof(initArray) / sizeof(int);
}
//����Ʈ�� ����ִ��� Ȯ��
int is_empty(ArrayListType*L)
{
	return(L->length == 0);
}
//����Ʈ�� ����á���� Ȯ��
int is_full(ArrayListType*L)
{
	return(L->length == MAX_LIST_SIZE);

}
//����Ʈ ���
void printList(ArrayListType*L)
{
	int i;

	if (is_empty(L))//����Ʈ�� ����ִ� ���
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
//����Ʈ position��ġ�� item�� �Է��ϴ� �Լ�
void add(ArrayListType*L, int position, element item)
{
	if (is_full(L))
		printf("List is full! Can't insert.\n");
	else if ((position >= 0) && (position <= L->length))
	{
		int i;
		for (i = L->length - 1; i >= position; i--)
		{
			L->list[i + 1] = L->list[i];//������ ��ġ�� ���� ���ؼ� �����͵��� �� ĭ�� �ڷ� �̵�
		}
		L->list[position] = item;//item ����
		L->length++;//�迭 ���� ����

	}
	else
	{
		printf("���� ��ġ ����!");
	}
}
//����Ʈ���� item�� �����ϴ� �Լ�
element rem(ArrayListType*L, int position)
{
	int i;
	element item;

	if (position < 0 || position >= L->length)
	{
		printf("���� ��ġ ����!");
		return(-1);
	}

	item = L->list[position];//������ ������ ���

	for (i = position; i < L->length - 1; i++)
		L->list[i] = L->list[i + 1];//������ ��ġ�� ���� ����� ���ؼ� �ڿ� �ִ� ������ ���� �����.

	L->length--;//�迭 ���� ����
	return item;//����� ������ ��ȯ
}
