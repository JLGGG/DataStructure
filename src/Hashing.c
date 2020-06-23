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

#define RANDOMIZE() srand((unsigned)time(NULL))//난수 설정
#define TABLESIZE 100//해쉬 테이블의 크기
#define TESTSIZE 200

typedef struct _LinkedChain{//해쉬테이블 요소 구조체
	int num;
	struct _LinkedChain *next;
}LinkedChain;

typedef struct _ChainHashTable{//해쉬테이블
	LinkedChain * hashtable[TABLESIZE];
	int collision;
}ChainHashTable;

int hashFunc(int num);//hashing 함수
void initHashTable(ChainHashTable *cht);//hash 테이블을 TableSize만큼 초기화
void insertHashTable(ChainHashTable *cht, int num);//hash 테이블에 random number(num)를 삽입
void printHashTable(ChainHashTable *cht);
void destroyHashTable(ChainHashTable *cht);

int main(){
	int i = 0;
	ChainHashTable cht;

	RANDOMIZE();

	initHashTable(&cht);

	for (i = 0; i < TESTSIZE; i++){//200개의 랜덤 숫자를 생성하여 해쉬테이블에 삽입
		int num = rand() % 10000 + 1;
		insertHashTable(&cht, num);
	}

	printHashTable(&cht);

	printf("\n");
	printf("[ 총 충돌횟수: %d]\n", cht.collision);
	destroyHashTable(&cht);

	return 0;
}
void initHashTable(ChainHashTable *cht){//해쉬 테이블 초기화
	int i = 0;
	for (i = 0; i < TABLESIZE; i++){
		cht->hashtable[i] = (LinkedChain*)malloc(sizeof(LinkedChain));//해쉬 테이블 동적할당
		cht->hashtable[i]->next = NULL;
		cht->hashtable[i]->num = 0;
	}
	cht->collision = 0;

}
int hashFunc(int num){//해쉬 함수
	return num%TABLESIZE;//제산함수 사용
}
void insertHashTable(ChainHashTable *cht, int num)//해쉬테이블에 노드 삽입
{
	int key = hashFunc(num);

	LinkedChain *ptr;//새노드
	LinkedChain *node_before = NULL;//이전 노드
	LinkedChain *node = cht->hashtable[key];

	while (node){//key 위치에 이미 다른 노드가 있는 경우
		if (node_before != NULL){
			cht->collision++;//충돌 횟수
		}
		node_before = node;
		node = node->next;
	}

	ptr = (LinkedChain*)malloc(sizeof(LinkedChain));//새 노드 생성
	ptr->num = num;
	ptr->next = NULL;

	if (node_before != NULL){//기존의 리스트가 존재하면
		node_before->next = ptr;
	}
	else//기존의 리스트가 존재하지 않으면
		cht->hashtable[key] = ptr;
}


void printHashTable(ChainHashTable *cht)//해쉬 테이블 출력
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
void destroyHashTable(ChainHashTable *cht)//해쉬 테이블 파괴
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
