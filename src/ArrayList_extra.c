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
void add(ArrayListType*L, int position, element item,int length);//����Ʈ L�� position ��ġ�� item�� �߰�
element rem(ArrayListType*L, int position, element item);//����Ʈ���� position ��ġ�� item�� ����

void main()
{
	element item;

	ArrayListType*L = (ArrayListType*)malloc(sizeof(ArrayListType));//�����Ҵ�
	initList(L);//�迭 �ʱ�ȭ

	printf("�ʱ� ������\t: ");
	printList(L);
	printf("\n");

	add(L, 2, 30, L->length-1);
	printf("30�� �߰���\t: ");
	printList(L);
	printf("\n");

	item = rem(L, 5, 0);
	if (item != -1) printf("%d �����Ͱ� ������\t: ", item);
	printList(L);
	printf("\n");

	add(L, 5, 60, L->length-1);
	printf("60�� �߰���\t:");
	printList(L);
	printf("\n");

	item = rem(L, 8, 0);
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
//����Ʈ position��ġ�� item�� �����ϴ� �Լ�
void add(ArrayListType*L, int position, element item,int length)
{
   if(is_full(L))
      printf("List is full! can't insert.\n");
   else if((position>=0)&&(position<=L->length))
   {
        L->list[length+1]=L->list[length];//������ �ڷ� �̵�

        if(length!=position)
           add(L,position,item,length-1);//add�Լ� ����� ȣ��
        else if(length==position)
        {
            L->list[position]=item;//item����
            L->length++;//�迭 ���� ����
        }
   }
}
//����Ʈ���� item�� �����ϴ� �Լ�
element rem(ArrayListType*L, int position,element item)
{
    if(position<0 || position>=L->length)
    {
       printf("���� ��ġ ����!");
       return (-1);
    }
    if(item==0)//�Լ� �ʱ� ���� �� ������ ������ ���
       item=L->list[position];

    L->list[position]=L->list[position+1];//������ ��ĭ ������ �̵�

    if(position<L->length-2)
        rem(L,position+1,item);//rem�Լ� ����� ȣ��
    else if(position==L->length-2)
    {
       L->length--;//�迭 ���� ����
       return item;//��� ������ ��ȯ
    }
}

