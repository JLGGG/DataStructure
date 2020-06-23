#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<memory.h>

#ifndef BOOL 
#define BOOL int
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif 

#define RANDOMIZE() srand((unsigned)time(NULL))//���� ����
#define TABLESIZE 100//�ؽ� ���̺��� ũ��
#define TESTSIZE 200

typedef struct _LinkedChain{//�ؽ����̺� ��� ����ü
	int num;
	struct _LinkedChain *next;
}LinkedChain;

typedef struct _ChainHashTable{//�ؽ����̺�
	LinkedChain * hashtable[TABLESIZE];
	int collision;
}ChainHashTable;

int hashFunc(int num);//hashing �Լ�
void initHashTable(ChainHashTable *cht);//hash ���̺��� TableSize��ŭ �ʱ�ȭ
void insertHashTable(ChainHashTable *cht, int num);//hash ���̺� random number(num)�� ����
void printHashTable(ChainHashTable *cht);
void destroyHashTable(ChainHashTable *cht);

int main(){
	int i = 0;
	ChainHashTable cht;

	RANDOMIZE();

	initHashTable(&cht);

	for (i = 0; i < TESTSIZE; i++){//200���� ���� ���ڸ� �����Ͽ� �ؽ����̺� ����
		int num = rand() % 10000 + 1;
		insertHashTable(&cht, num);
	}

	printHashTable(&cht);

	printf("\n");
	printf("[ �� �浹Ƚ��: %d]\n", cht.collision);
	destroyHashTable(&cht);

	return 0;
}
void initHashTable(ChainHashTable *cht){//�ؽ� ���̺� �ʱ�ȭ
	int i = 0;
	for (i = 0; i < TABLESIZE; i++){
		cht->hashtable[i] = (LinkedChain*)malloc(sizeof(LinkedChain));//�ؽ� ���̺� �����Ҵ�
		cht->hashtable[i]->next = NULL;
		cht->hashtable[i]->num = 0;
	}
	cht->collision = 0;

}
int hashFunc(int num){//�ؽ� �Լ�
	return num%TABLESIZE;//�����Լ� ���
}
void insertHashTable(ChainHashTable *cht, int num)//�ؽ����̺� ��� ����
{
	int key = hashFunc(num);

	LinkedChain *ptr;//�����
	LinkedChain *node_before = NULL;//���� ���
	LinkedChain *node = cht->hashtable[key];

	while (node){//key ��ġ�� �̹� �ٸ� ��尡 �ִ� ���
		if (node_before != NULL){
			cht->collision++;//�浹 Ƚ��
		}
		node_before = node;
		node = node->next;
	}

	ptr = (LinkedChain*)malloc(sizeof(LinkedChain));//�� ��� ����
	ptr->num = num;
	ptr->next = NULL;

	if (node_before != NULL){//������ ����Ʈ�� �����ϸ�
		node_before->next = ptr;
	}
	else//������ ����Ʈ�� �������� ������
		cht->hashtable[key] = ptr;
}


void printHashTable(ChainHashTable *cht)//�ؽ� ���̺� ���
{
	int i = 0;
	for (i = 0; i < TABLESIZE; i++){
		LinkedChain *current = cht->hashtable[i];

		while (current != NULL){
			printf("[%2d] : %d\t", i, current->num);
			current = current->next;
		}
		printf("\n");

	}

}
void destroyHashTable(ChainHashTable *cht)//�ؽ� ���̺� �ı�
{
	int i = 0;
	LinkedChain *temp = NULL, *current = NULL;
	for (i = 0; i < TABLESIZE; i++){
		current = cht->hashtable[i];
		while (current != NULL){
			temp = current->next;
			free(current);
			current = temp;
		}
	}
	memset(cht, 0, sizeof(ChainHashTable));

}
