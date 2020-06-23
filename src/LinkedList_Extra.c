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
listPointer circul_end(listPointer first);//���� ���� ����Ʈ�� ������ ��带 ã�� �Լ�
listPointer first_end_Link(listPointer first_node);//����Ʈ�� ó���� �������� �����ϴ� �Լ�
void delete_node_at(listPointer first, int pos);//������ ��带 �����ϴ� �Լ�

void main()
{
	listPointer first, p;
	first = create2();//����Ʈ �ʱ����

	insert(&first, first->link, 50);//�� ��° 50 ����
	printList(first);

	insert(&first, first, 30);//�� ��° 30 ����
	printList(first);

	delete2(&first, first, first->link);//�� ��° 30 ����
	printList(first);

	p=circul_end(first);//���� ����Ʈ�� ������ ��� ã�� �Լ� ȣ��
	delete2(&first, p, first);//ù ��° 10 ����
	printList(first);

	insert(&first, first, 70);//�� ��° 70 ����
	printList(first);

	insert(&first, first->link, 90);//�� ��° 90 ����
	printList(first);

	delete_node_at(first, 7);//�������� �ִ� 50 ����
	printList(first);
}
listPointer create2()
{// �� ���� ��带 ���� ���� ���Ḯ��Ʈ ����
	listPointer first, second;
	first = (listPointer)malloc(sizeof(listNode));//��� 2�� ����
	second = (listPointer)malloc(sizeof(listNode));

	first->data = 10;
	second->data = 20;
	first->link = second;//��忬��
	first=first_end_Link(first);//ù ���, ������ ��� ���� ���� �Լ�

	return first;//���� ����� ����Ʈ ��ȯ
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
	if (*first){
		temp->link = x->link;//��忬��
		x->link = temp;	
	}
	else
	{
		temp->link=NULL;
		*first=temp;
	}

}
void delete2(listPointer *first, listPointer trail, listPointer x)
{//����Ʈ�κ��� x ��带 ����, trail�� ������ x�� ���� ����̸� first�� ����Ʈ�� ����
	if (x == *first) {//������ ��尡 ����Ʈ�� ù ��° ����̸� ����
		trail->link = x->link;//x�� ������ ����Ʈ ����
		(*first)=trail->link;//*first�� ����Ʈ ��ü�̹Ƿ�, x�� free�ϸ� ����Ʈ�� ��������. �׷��Ƿ� x ���� ���� �̵�
	}
	else//x�� ù ��° ��尡 �ƴ� ���
		trail->link=x->link;

	free(x);//�� ����
}
void printList(listPointer first)//����Ʈ ���
{
	listPointer temp = first;

	printf("The list contains: ");
	do{//�������Ḯ��Ʈ�� do~while�� ����ؼ� ���
		printf("%d ", temp->data);
		temp = temp->link;
	} while (temp != first);//����Ʈ�� ���� ����Ʈ�� �Ӹ��� ���ؼ� ã�´�.
	printf("\n");
}
listPointer circul_end(listPointer first)
{//�������Ḯ��Ʈ�� ������ ��带 ã�� �Լ�
	listPointer p = first;

	while ((p->link) != first)
		p = p->link;

	return p;
}
listPointer first_end_Link(listPointer first_node)
{//ù ���� ������ ��带 �����ϴ� �Լ�
	first_node->link->link=first_node;

	return first_node;
}
void delete_node_at(listPointer first, int pos)
{//n��° ��带 �����ϴ� �Լ�, n�� 0���� ����
	int i;
	listPointer p=first;
	if(pos<0) return ;//�����̸� ����
	for(i=0; i<pos-1; i++)
		p=p->link;//�����带 ã���ش�.

	delete2(&first, p, p->link);//������� ������ ��带 �Լ��� �Ű������� ����
}
