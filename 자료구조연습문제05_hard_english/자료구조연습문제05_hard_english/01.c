#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node node;
struct Node {
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

void change(char* str, char*new) {
		int a = 0, b = 0;
		while (str[a] != '\n') {
			if (str[a] >= 65 && str[a] <= 90)
				new[b++] = str[a] + 32;
			else if (str[a] >= 97 && str[a] <= 122)
				new[b++] = str[a];
			a++;
		}
		new[b] = 0;
	}

int main() {
	FILE* fp = fopen("test2.txt", "r+t");
	if (fp == NULL) 
		printf("File Null\n");
	
	char str[512], new[512];

	while (fgets(str, 512, fp) != NULL) {
		change(str, new);
		int stringLen = strlen(new) + 1;
		int loop = stringLen / 2;

		printf("original : %s \nchange : %s \n", str, new);

		Init();

		for (int i = 0; i < stringLen/2; i++)
			Push(new[i]);
		
		if (stringLen % 2 == 0)
			Pop();

		for (int i = loop; i < stringLen - 1; i++)
			if (new[i] != Pop())
				break;
		
		if (Is_empty())
			printf("회문\n\n");
		else
			printf("회문X\n\n");
	}
	fclose(fp);
	return 0;
}