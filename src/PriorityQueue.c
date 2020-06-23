#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<memory.h>

#define PQUEUE_CAPACITY 200

typedef struct Element{//element 정의
	int key;
}Element;

typedef struct HeapType{//heap 정의
	Element *heap;
	int heapSize;
	int capacity;
}HeapType;

void PQueueInit(HeapType *heapType, int capacity);//heap 초기화 함수
void PQueueInsertMaxHeap(HeapType *heapType, Element item);//최대 힙 생성 함수
Element PQueueDeleteMaxHeap(HeapType *heapType);//힙 삭제 함수
void PQueueDestoy(HeapType *heapType);//힙 파괴 함수


int main(int argc, char **argv){
	HeapType heapType = { 0, };//힙 생성
	Element item = { 0, };
	int i;


	printf("Initialize priority queue\n");
	PQueueInit(&heapType, PQUEUE_CAPACITY);

	printf("Insert node to priority queue : 10, 5, 20, 40, 30\n");

	//heap트리에 값 삽입
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
void PQueueInit(HeapType *heapType, int capacity)//힙 초기화 함수
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
{//힙 요소 삽입 함수
	int i = 0;
	assert(heapType != NULL);
	i = ++(heapType->heapSize);

	//heapSize가 0이 아니고 루트 노드가 아니고 입력하려는 값이 부모노드 보다 큰 경우
	while (heapType->heapSize != 0 && i != 1 && item.key > heapType->heap[i / 2].key)
	{
		heapType->heap[i] = heapType->heap[i / 2];//자식 노드에 부모 노드 값을 대입
		i /= 2;//부모 노드로 이동
	}
	heapType->heap[i] = item;//값 삽입
}


Element PQueueDeleteMaxHeap(HeapType *heapType)
{//힙 삭제 함수
	int parent = 0, child = 0;
	Element item, temp;

	assert(heapType != NULL);

	item = heapType->heap[1];//루트 노드를 삭제
	temp = heapType->heap[(heapType->heapSize)--];//힙에 최 말단 노드를 추출하고, heap 사이즈를 1 감소
	parent = 1;
	child = 2;
	while (child <= heapType->heapSize){
		//child 값이 heapSize를 넘지 않고 자식 노드중에서 우측 노드가 더 크면 조건 성립
		if (child < heapType->heapSize && heapType->heap[child].key < heapType->heap[child + 1].key)
			child++;
		if (temp.key >= heapType->heap[child].key) break;//자식 노드보다 크면 종료

		heapType->heap[parent] = heapType->heap[child];//자식 노드가 더 크면 부모 노드에 값 삽입
		parent = child;//한 단계 아래로 이동
		child *= 2;//자식 지시자 한 단계 아래 좌측 노드로 이동
	}
	heapType->heap[parent] = temp;
	return item;
}


void PQueueDestoy(HeapType *heapType)//힙 파괴
{
	memset(heapType->heap, 0, sizeof(Element) *heapType->capacity);
	free(heapType->heap);
}
