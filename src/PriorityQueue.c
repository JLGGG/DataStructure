#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<memory.h>

#define PQUEUE_CAPACITY 200

typedef struct Element{//element ����
	int key;
}Element;

typedef struct HeapType{//heap ����
	Element *heap;
	int heapSize;
	int capacity;
}HeapType;

void PQueueInit(HeapType *heapType, int capacity);//heap �ʱ�ȭ �Լ�
void PQueueInsertMaxHeap(HeapType *heapType, Element item);//�ִ� �� ���� �Լ�
Element PQueueDeleteMaxHeap(HeapType *heapType);//�� ���� �Լ�
void PQueueDestoy(HeapType *heapType);//�� �ı� �Լ�


int main(int argc, char **argv){
	HeapType heapType = { 0, };//�� ����
	Element item = { 0, };
	int i;


	printf("Initialize priority queue\n");
	PQueueInit(&heapType, PQUEUE_CAPACITY);

	printf("Insert node to priority queue : 10, 5, 20, 40, 30\n");

	//heapƮ���� �� ����
	item.key = 10;
	PQueueInsertMaxHeap(&heapType, item);
	item.key = 5;
	PQueueInsertMaxHeap(&heapType, item);
	item.key = 20;
	PQueueInsertMaxHeap(&heapType, item);
	item.key = 40;
	PQueueInsertMaxHeap(&heapType, item);
	item.key = 30;
	PQueueInsertMaxHeap(&heapType, item);

	printf("Delete node from priority queue:");

	for (i = 0; i < 5; i++)
	{
		printf("%d ", PQueueDeleteMaxHeap(&heapType).key);

	}

	printf("\nDestroy priority queue\n");
	PQueueDestoy(&heapType);

	return EXIT_SUCCESS;
}
void PQueueInit(HeapType *heapType, int capacity)//�� �ʱ�ȭ �Լ�
{
	assert(heapType != NULL);
	heapType->heap = (Element*)malloc(sizeof(Element) * capacity);
	if (heapType->heap == NULL) {
		return;
	}
	memset(heapType->heap, 0, sizeof(Element)*capacity);
	heapType->heapSize = 0;
	heapType->capacity = capacity;
}
void PQueueInsertMaxHeap(HeapType *heapType, Element item)
{//�� ��� ���� �Լ�
	int i = 0;
	assert(heapType != NULL);
	i = ++(heapType->heapSize);

	//heapSize�� 0�� �ƴϰ� ��Ʈ ��尡 �ƴϰ� �Է��Ϸ��� ���� �θ��� ���� ū ���
	while (heapType->heapSize != 0 && i != 1 && item.key > heapType->heap[i / 2].key)
	{
		heapType->heap[i] = heapType->heap[i / 2];//�ڽ� ��忡 �θ� ��� ���� ����
		i /= 2;//�θ� ���� �̵�
	}
	heapType->heap[i] = item;//�� ����
}


Element PQueueDeleteMaxHeap(HeapType *heapType)
{//�� ���� �Լ�
	int parent = 0, child = 0;
	Element item, temp;

	assert(heapType != NULL);

	item = heapType->heap[1];//��Ʈ ��带 ����
	temp = heapType->heap[(heapType->heapSize)--];//���� �� ���� ��带 �����ϰ�, heap ����� 1 ����
	parent = 1;
	child = 2;
	while (child <= heapType->heapSize){
		//child ���� heapSize�� ���� �ʰ� �ڽ� ����߿��� ���� ��尡 �� ũ�� ���� ����
		if (child < heapType->heapSize && heapType->heap[child].key < heapType->heap[child + 1].key)
			child++;
		if (temp.key >= heapType->heap[child].key) break;//�ڽ� ��庸�� ũ�� ����

		heapType->heap[parent] = heapType->heap[child];//�ڽ� ��尡 �� ũ�� �θ� ��忡 �� ����
		parent = child;//�� �ܰ� �Ʒ��� �̵�
		child *= 2;//�ڽ� ������ �� �ܰ� �Ʒ� ���� ���� �̵�
	}
	heapType->heap[parent] = temp;
	return item;
}


void PQueueDestoy(HeapType *heapType)//�� �ı�
{
	memset(heapType->heap, 0, sizeof(Element) *heapType->capacity);
	free(heapType->heap);
}
