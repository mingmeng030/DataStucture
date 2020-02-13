#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node node;
struct Node{
	char data;
	node* next;
};

node* head;
node* top;
int stacksize = 0;

void Init() {
	head = (node*)malloc(sizeof(node));
	top = head;
}

int Is_full() {
	if (stacksize == 0)
		return 0;
	else 
		return 1;
}

int Is_empty() {
	if (stacksize == 0)
		return 1;
	else
		return 0;
}

void Push(char c) {
	if (stacksize == 0) {	//스택에 아무것도 없을 때
		top->next = (node*)malloc(sizeof(node));
		top->data = c;
	}
	else {	//스택에 이미 데이터가 있을 때
		top->next = (node*)malloc(sizeof(node));
		top = top->next;
		top->data = c;
	}
	stacksize++;
}

char Pop() {
	node* Dnode = top;
	char popnode = Dnode->data;
	stacksize--;

	top = head;
	for (int i = 0; i < stacksize - 1; i++) {
		top = top->next;
	}
	free(Dnode);
	return popnode;
}

char Top() {
	return (top->data);
}

int main() {
	FILE* fp = fopen("text.txt", "r+t");
	char str[512];
	int result=0,loop = 0;

	if (fp == NULL) {
		printf("File Null\n");
	}

	while (fgets(str, 512, fp) != NULL) {

		int stringLen = strlen(str);
		printf("%s : ", str);
		if (stringLen == 2) {
			printf("회문\n\n");
			continue;
		}

		Init();
		for (int i = 0; i<stringLen / 2; i++)
			Push(str[i]);


		int start;
		if (stringLen % 2 == 0) {
			Pop();
			start = stringLen / 2;
		}
		else start = stringLen / 2;


		for (int i = start; i < stringLen - 1; i++) {
			if (str[i] != Pop()) {
				result++;
				break;
			}
		}

		if (stacksize + result == 0)
			printf("회문\n\n");
		else printf("회문 X\n\n");
	}

	fclose(fp);
	return 0;
}
