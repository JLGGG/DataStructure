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

void stackInit(Stack *stack, int size);//������ �ʱ�ȭ
void stackDestroy(Stack *stack);//������ �ı�
BOOL stackPush(Stack *stack, element elem);//������ push����
BOOL stackPop(Stack *stack, element *outElem);//������ pop����
BOOL stackPeek(Stack *stack, element *outElem);//������ peek����
BOOL stackIsFull(Stack *stack);//������ �������ִ����� �Ǵ�
BOOL stackIsEmpty(Stack *stack);//������ ����ִ����� �Ǵ�
void stackDescription(Stack *stack);//���� ���� ���


BOOL infixToPostfix(char *infix, char *outPostfix);//infix���� postfix�� ��ȯ
BOOL getOperatorPriority(char op, int *out);//������ �켱������ ������

BOOL postFixCalc(char *postFix, int *outResult);//postfix ������ ���

int main(int argc, char **argv){
	char inputBuf[DEF_BUF_SIZE] = { 0, };//����� �Է� ����
	char postfixBuf[DEF_BUF_SIZE] = { 0, };//postfix��� ������ ���� ����
	int calcResult = 0;//�����

	printf("Input expression : ");//����� �Է��� �޴´�.

	fgets(inputBuf, DEF_BUF_SIZE - 1, stdin);
	inputBuf[strlen(inputBuf) - 1] = '\0';//���๮�ڴ� �����Ѵ�.
	printf("Your input : %s\n", inputBuf);//����� �Է��� Ȯ���Ѵ�.

	if (infixToPostfix(inputBuf, postfixBuf) == FALSE) { return EXIT_FAILURE; }//postfix�� ��ȯ
	printf("Convert to postfix : %s\n", postfixBuf);

	if (postFixCalc(postfixBuf, &calcResult) == FALSE) { return EXIT_FAILURE; }//postfix�� ���
	printf("Calculating result = %d\n", calcResult);

	return EXIT_SUCCESS;
}
void stackInit(Stack *stack, int size)//���� �ʱ�ȭ �Լ�
{
	stack->ary = (element *)malloc(sizeof(element)*size);//���� ���� ����
	memset(stack->ary, 0, size * sizeof(element));//���� ���� 0���� �ʱ�ȭ
	stack->capacity = size;//������ ũ��
	stack->sp = -1;//���� ������
}
void stackDestroy(Stack *stack)//���� �ı� �Լ�
{
	free(stack->ary);//�����Ҵ� ����
}
BOOL stackPush(Stack *stack, element elem)//push�Լ�
{
	if (stackIsFull(stack) == TRUE){//����ó��
		ERR_MSG("stack is full");
		return FALSE;
	}
	stack->ary[++(stack->sp)] = elem;//������ �� �Է�

	return TRUE;
}
BOOL stackPop(Stack *stack, element *outElem)//pop�Լ�
{
	if (stackIsEmpty(stack) == TRUE){//����ó��
		ERR_MSG("stack is empty");
		return FALSE;
	}
	if (outElem != NULL) { *outElem = stack->ary[stack->sp]; }

	if (stack->sp >= 0)//���ÿ� ���� �ִ��� Ȯ��
	{
		stack->sp--;//������ ���� ����
	}
	return TRUE;
}
BOOL stackPeek(Stack *stack, element *outElem)//peek�Լ�
{
	if (stackIsEmpty(stack) == TRUE){//����ó��
		ERR_MSG("stack is empty");
		return FALSE;
	}
	*outElem = stack->ary[stack->sp];//���ÿ��� �� ����
	return TRUE;
}
BOOL stackIsFull(Stack *stack)//full�Լ�
{
	if (stack->sp == stack->capacity - 1) { return TRUE; }
	return FALSE;
}
BOOL stackIsEmpty(Stack *stack)//empty�Լ�
{
	if (stack->sp == -1) { return TRUE; }
	return FALSE;
}
void stackDescription(Stack *stack)//��� �Լ�
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
	char buf[POSTFIX_NUM_BUF] = { 0, };//������ �ӽ��������
	int bufPoint = 0, resultBufPoint = 0;

	Stack stack;//���� ����
	stackInit(&stack, STACK_DEF_SIZE);//���� �ʱ�ȭ

	while (*infix){
		switch (*infix){
		case' '://������ �Ѿ��.
			break;
		case'0':case'1':case'2':case'3':case'4':
		case'5':case'6':case'7':case'8':case'9':
			buf[bufPoint++] = *infix;//���ڸ��� �̻� ����� ���� �ӽ� ����
			break;
		case'+':case'-':case'*':case'/':
			strcat(outPostfix, buf);//�����ڰ� ������ ���ڴ� ���� ���̹Ƿ� �迭�� ����Ѵ�.
			resultBufPoint = strlen(outPostfix);
			outPostfix[resultBufPoint++] = ' ';//���� ����
			bufPoint = 0;
			memset(buf, 0, sizeof(char)*POSTFIX_NUM_BUF);//���� 0���� �ʱ�ȭ


			while (TRUE){
				if (!stackIsEmpty(&stack)){//������ ������� Ȯ��
					int stackOpPriority = 0, opPriority = 0;
					element stackOp = 0;

					stackPeek(&stack, &stackOp);//���ÿ��� ���� ������.
					getOperatorPriority((char)stackOp, &stackOpPriority);//������ ������ ���� ����
					getOperatorPriority(*infix, &opPriority);//�迭�� ������ ���� ����

					if (opPriority <= stackOpPriority){//������ �����ڰ� �� ũ�� ����
						stackPop(&stack, NULL);//������ sp 1����
						outPostfix[resultBufPoint++] = (char)stackOp;//������ ������ �迭�� ����
						outPostfix[resultBufPoint++] = ' ';//���� ����
					}
					else{
						stackPush(&stack, *infix);//�迭�� �����ڰ� �� ũ�� ������ ������ ���� ����
						break;
					}
				}
				else{//������ ��������� �迭�� ������ ���ÿ� ����
					stackPush(&stack, *infix);
					break;
				}
			}
			break;
		default:
			ERR_MSG("invalid character");
			return FALSE;
		}
		infix++;//������ �������� �迭 �̵�
	}

	strcat(outPostfix, buf);//���ۿ� �����ִ� �� �迭�� ����
	resultBufPoint = strlen(outPostfix);
	outPostfix[resultBufPoint++] = ' ';

	while (!stackIsEmpty(&stack)){//���ÿ� �����ڰ� ���������� ����
		element stackOp;
		 stackPop(&stack, &stackOp);//���ÿ��� �� ����
		outPostfix[resultBufPoint++] = (char)stackOp;//�迭�� ����
		outPostfix[resultBufPoint++] = ' ';
	}
	stackDestroy(&stack);//�����ı�

	return TRUE;
}
BOOL getOperatorPriority(char op, int *out)//������ �켱���� ����
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
BOOL postFixCalc(char *postFix, int *outResult)//postfix������ ����ϴ� �Լ�
{
	char *context = NULL, *token = NULL;
	int len = 0;

	Stack stack;
	stackInit(&stack, STACK_DEF_SIZE);
	while (token = strtok_s(postFix, " ", &context)){//�������� �� ��ū�� �����Ѵ�.
		len = strlen(token);
		if (len > 1) { stackPush(&stack, atoi(token)); }//2�ڸ� �� �̻��� ������ ���ڴ� ������ ��ȯ �� ���ÿ� ����
		else{//���̰� 1�̶�� ���� �Ǵ� �������̴�.
			if (*token >= '0' && *token <= '9'){
				stackPush(&stack, atoi(token));
			}
			else{//�����ڶ�� ����� �����Ѵ�.
				int rightOp = 0, leftOp = 0;
				stackPop(&stack, &rightOp);
				stackPop(&stack, &leftOp);
				switch (*token){//��� ����� �ٽ� ���ÿ� �����Ѵ�.
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
	stackPop(&stack, outResult);//���ÿ��� ��� �� ����
	stackDestroy(&stack);

	return TRUE;
}


