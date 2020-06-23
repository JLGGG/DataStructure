#include<stdio.h>
#include<stdlib.h>
#include<memory.h>
#include<string.h>

#define ERR_MSG(msg) printf("Error : %s (function : %s, line : %d)\n", msg, __FUNCTION__, __LINE__)
#define DEF_BUF_SIZE 100
#define STACK_DEF_SIZE 100
#define POSTFIX_NUM_BUF 20

#ifndef BOOL
typedef enum BOOL { FALSE, TRUE } BOOL;
#endif

typedef int element;
typedef struct Stack{
	element *ary;
	int capacity;
	int sp;
}Stack;

void stackInit(Stack *stack, int size);//스택의 초기화
void stackDestroy(Stack *stack);//스택의 파괴
BOOL stackPush(Stack *stack, element elem);//스택의 push연산
BOOL stackPop(Stack *stack, element *outElem);//스택의 pop연산
BOOL stackPeek(Stack *stack, element *outElem);//스택의 peek연산
BOOL stackIsFull(Stack *stack);//스택이 가득차있는지를 판단
BOOL stackIsEmpty(Stack *stack);//스택이 비어있는지를 판단
void stackDescription(Stack *stack);//스택 내용 출력


BOOL infixToPostfix(char *infix, char *outPostfix);//infix에서 postfix로 변환
BOOL getOperatorPriority(char op, int *out);//연산자 우선순위를 가져옴

BOOL postFixCalc(char *postFix, int *outResult);//postfix 수식을 계산

int main(int argc, char **argv){
	char inputBuf[DEF_BUF_SIZE] = { 0, };//사용자 입력 버퍼
	char postfixBuf[DEF_BUF_SIZE] = { 0, };//postfix결과 저장을 위한 버퍼
	int calcResult = 0;//계산결과

	printf("Input expression : ");//사용자 입력을 받는다.

	fgets(inputBuf, DEF_BUF_SIZE - 1, stdin);
	inputBuf[strlen(inputBuf) - 1] = '\0';//개행문자는 제거한다.
	printf("Your input : %s\n", inputBuf);//사용자 입력을 확인한다.

	if (infixToPostfix(inputBuf, postfixBuf) == FALSE) { return EXIT_FAILURE; }//postfix로 변환
	printf("Convert to postfix : %s\n", postfixBuf);

	if (postFixCalc(postfixBuf, &calcResult) == FALSE) { return EXIT_FAILURE; }//postfix식 계산
	printf("Calculating result = %d\n", calcResult);

	return EXIT_SUCCESS;
}
void stackInit(Stack *stack, int size)//스택 초기화 함수
{
	stack->ary = (element *)malloc(sizeof(element)*size);//스택 공간 생성
	memset(stack->ary, 0, size * sizeof(element));//스택 공간 0으로 초기화
	stack->capacity = size;//스택의 크기
	stack->sp = -1;//스택 지시자
}
void stackDestroy(Stack *stack)//스택 파괴 함수
{
	free(stack->ary);//동적할당 해제
}
BOOL stackPush(Stack *stack, element elem)//push함수
{
	if (stackIsFull(stack) == TRUE){//예외처리
		ERR_MSG("stack is full");
		return FALSE;
	}
	stack->ary[++(stack->sp)] = elem;//스택의 값 입력

	return TRUE;
}
BOOL stackPop(Stack *stack, element *outElem)//pop함수
{
	if (stackIsEmpty(stack) == TRUE){//예외처리
		ERR_MSG("stack is empty");
		return FALSE;
	}
	if (outElem != NULL) { *outElem = stack->ary[stack->sp]; }

	if (stack->sp >= 0)//스택에 값이 있는지 확인
	{
		stack->sp--;//스택의 개수 감소
	}
	return TRUE;
}
BOOL stackPeek(Stack *stack, element *outElem)//peek함수
{
	if (stackIsEmpty(stack) == TRUE){//예외처리
		ERR_MSG("stack is empty");
		return FALSE;
	}
	*outElem = stack->ary[stack->sp];//스택에서 값 추출
	return TRUE;
}
BOOL stackIsFull(Stack *stack)//full함수
{
	if (stack->sp == stack->capacity - 1) { return TRUE; }
	return FALSE;
}
BOOL stackIsEmpty(Stack *stack)//empty함수
{
	if (stack->sp == -1) { return TRUE; }
	return FALSE;
}
void stackDescription(Stack *stack)//출력 함수
{
	int cnt = 0;
	printf("<stack : %p\n", stack);
	while (cnt < stack->capacity){
		printf("\t[%3d] : %d", cnt, stack->ary[cnt]);
		if (cnt == stack->sp){
			printf(" <- Top");
		}
		printf("\n");
		cnt++;
	}
	printf(">\n");
}

BOOL infixToPostfix(char *infix, char *outPostfix)
{
	char buf[POSTFIX_NUM_BUF] = { 0, };//숫자의 임시저장장소
	int bufPoint = 0, resultBufPoint = 0;

	Stack stack;//스택 선언
	stackInit(&stack, STACK_DEF_SIZE);//스택 초기화

	while (*infix){
		switch (*infix){
		case' '://공백은 넘어간다.
			break;
		case'0':case'1':case'2':case'3':case'4':
		case'5':case'6':case'7':case'8':case'9':
			buf[bufPoint++] = *infix;//한자리수 이상 계산을 위한 임시 저장
			break;
		case'+':case'-':case'*':case'/':
			strcat(outPostfix, buf);//연산자가 나오면 숫자는 끝난 것이므로 배열에 기록한다.
			resultBufPoint = strlen(outPostfix);
			outPostfix[resultBufPoint++] = ' ';//공백 삽입
			bufPoint = 0;
			memset(buf, 0, sizeof(char)*POSTFIX_NUM_BUF);//버퍼 0으로 초기화


			while (TRUE){
				if (!stackIsEmpty(&stack)){//스택이 비었는지 확인
					int stackOpPriority = 0, opPriority = 0;
					element stackOp = 0;

					stackPeek(&stack, &stackOp);//스택에서 값만 추출함.
					getOperatorPriority((char)stackOp, &stackOpPriority);//스택의 연산자 순위 결정
					getOperatorPriority(*infix, &opPriority);//배열의 연산자 순위 결정

					if (opPriority <= stackOpPriority){//스택의 연산자가 더 크면 실행
						stackPop(&stack, NULL);//스택의 sp 1감소
						outPostfix[resultBufPoint++] = (char)stackOp;//추출한 연산자 배열에 저장
						outPostfix[resultBufPoint++] = ' ';//공백 삽입
					}
					else{
						stackPush(&stack, *infix);//배열의 연산자가 더 크면 스택의 연산자 위에 삽입
						break;
					}
				}
				else{//스택이 비어있으면 배열의 연산자 스택에 삽입
					stackPush(&stack, *infix);
					break;
				}
			}
			break;
		default:
			ERR_MSG("invalid character");
			return FALSE;
		}
		infix++;//포인터 연산으로 배열 이동
	}

	strcat(outPostfix, buf);//버퍼에 남아있는 값 배열에 저장
	resultBufPoint = strlen(outPostfix);
	outPostfix[resultBufPoint++] = ' ';

	while (!stackIsEmpty(&stack)){//스택에 연산자가 남아있으면 실행
		element stackOp;
		 stackPop(&stack, &stackOp);//스택에서 값 추출
		outPostfix[resultBufPoint++] = (char)stackOp;//배열에 저장
		outPostfix[resultBufPoint++] = ' ';
	}
	stackDestroy(&stack);//스택파괴

	return TRUE;
}
BOOL getOperatorPriority(char op, int *out)//연산자 우선순위 결정
{
	switch (op){
	case'+':case'-':
		*out = 1;
		break;
	case'*':case'/':
		*out = 2;
		break;
	default:
		return FALSE;
	}
	return TRUE;
}
BOOL postFixCalc(char *postFix, int *outResult)//postfix수식을 계산하는 함수
{
	char *context = NULL, *token = NULL;
	int len = 0;

	Stack stack;
	stackInit(&stack, STACK_DEF_SIZE);
	while (token = strtok_s(postFix, " ", &context)){//공백으로 각 토큰을 구분한다.
		len = strlen(token);
		if (len > 1) { stackPush(&stack, atoi(token)); }//2자리 수 이상의 숫자형 문자는 정수로 변환 후 스택에 삽입
		else{//길이가 1이라면 숫자 또는 연산자이다.
			if (*token >= '0' && *token <= '9'){
				stackPush(&stack, atoi(token));
			}
			else{//연산자라면 계산을 수행한다.
				int rightOp = 0, leftOp = 0;
				stackPop(&stack, &rightOp);
				stackPop(&stack, &leftOp);
				switch (*token){//계산 결과는 다시 스택에 삽입한다.
				case'+':
					stackPush(&stack, leftOp + rightOp);
					break;
				case'-':
					stackPush(&stack, leftOp - rightOp);
					break;
				case'*':
					stackPush(&stack, leftOp * rightOp);
					break;
				case'/':
					stackPush(&stack, leftOp / rightOp);
					break;
				}
			}
		}
		postFix = context;
	}
	stackPop(&stack, outResult);//스택에서 결과 값 추출
	stackDestroy(&stack);

	return TRUE;
}


