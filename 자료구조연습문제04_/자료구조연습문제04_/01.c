#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data {
	char name[20];
	char sex[3];
	char live[20];
	char major[20];
	char score[10];
	char height[10];
	char weight[10];
}Data;

typedef struct node Node;
struct node {
	//next는 연결리스트의 다음 노드이니까 포인터로!
	Node* next;

	//data는 자료를 담는 부분이라서 포인터를 사용안하고 그냥 구조체로 생성했어!
	Data data;
};

Node* head;

void Free() {
	//curr로 연결리스트 처음부터 끝까지 해야하니 curr는 head를 가리킨다
	Node* curr = head;

	//curr이 null 일 때 까지!
	while (curr != NULL) {      //동적할당 해제 반복문   

								//할당해준 구조체배열을 해제하는 부분이니까 head를 사용해도 무방! (점점 사라지는 거니까!)
								//a-b-c-... 에서 head를 a에서 b로 이동
		head = head->next;

		//처음에 curr은 이전 head (a)를 가리키고 있다.
		//a할당 해제
		free(curr);

		//지금 head는 a에서 b로 이동했으니 curr은 b를 가리킨다.
		curr = head;
	}
}

void create() {
	//연결리스트의 머리 생성 head는 항상 고정
	head = (Node*)malloc(sizeof(Node));
}

void sort() {
	Node *i, *j;
	Data nodeTmp;

	for (i = head; i->next != NULL; i = i->next) {
		for (j = head; j->next != NULL; j = j->next) {
			if (strcmp(i->data.name, j->data.name) < 0) {
				nodeTmp = i->data;
				i->data = j->data;
				j->data = nodeTmp;
			}
		}
	}
}

void load() {
	FILE* fp = fopen("list.txt", "rt");

	//데이터 받는 char형 배열
	char input[512];
	Node* current = head;

	while (fgets(input, 512, fp) != NULL) {   //total에 학생 정보 저장
											  //data 받기
		sscanf(input, "%s%s%s%s%s%s%s", current->data.name, current->data.sex, 
			current->data.live, current->data.major, current->data.score, 
			current->data.height, current->data.weight);

		current->next = (Node*)malloc(sizeof(Node));
		current = current->next;
		current->next = NULL;
	}

	sort();
}

void search(char*name) {
	Node* curr = head;

	while (curr->next != NULL) {
		if (strcmp(curr->data.name, name) == 0) {
			printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\n", curr->data.name, curr->data.sex, 
				curr->data.live, curr->data.major, curr->data.score, 
				curr->data.height, curr->data.weight);
			return;
		}
		curr = curr->next;
	}

	printf("data NULL\n");
}

void print() {
	
	Node* curr = head;

	//curr의 next가 null 일 때 까지
	//마지막 curr은 next가 null이다
	while (curr->next != NULL) {
		//curr 데이터 출력
		printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\n", curr->data.name, curr->data.sex, 
			curr->data.live, curr->data.major, curr->data.score, 
			curr->data.height, curr->data.weight);

		//curr을 현재 curr->next로 이동
		curr = curr->next;
	}
}

void insert(Node*insertNode) {
	Node *nodeTmp = head;
	head = insertNode;
	head->next = nodeTmp;
	sort();
}

void del(char *name) {
	//curr로 연결리스트 처음부터 끝까지 해야하니 curr는 head를 가리킨다
	Node* curr = head;

	if (head->data.name == name) {
		Node* nodeTmp = head;
		head = head->next;
		free(nodeTmp);
		return;
	}

	//curr의 next가 null 일 때 까지
	//마지막 curr은 next가 null이다
	while (curr->next != NULL) {
		if (strcmp(curr->next->data.name, name) == 0) {
			Node*nodeTmp = curr->next;
			curr->next = nodeTmp->next;
			free(nodeTmp);
			break;
		}
		curr = curr->next;
	}
}

int main() {
	FILE *fp = fopen("input.txt", "r+t");
	char input[512];
	char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];

	while (fgets(input, 512, fp) != NULL) {
		sscanf(input, "%s %s %s %s %s %s %s %s %s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);
		if (strcmp(tok1, "CREATE") == 0) {
			create();
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "LOAD") == 0) {
			load();
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "PRINT") == 0) {
			print();
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "INSERT") == 0) {
			Node *insertNode = (Node*)malloc(sizeof(Node));
			strcpy(insertNode->data.name, tok2);
			strcpy(insertNode->data.sex, tok3);
			strcpy(insertNode->data.live, tok4);
			strcpy(insertNode->data.major, tok5);
			strcpy(insertNode->data.score, tok6);
			strcpy(insertNode->data.height, tok7);
			strcpy(insertNode->data.weight, tok8);
			insert(insertNode);
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "DELETE") == 0) {
			del(tok2);
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "SEARCH") == 0) {
			search(tok2);
			printf("%s done=========================================\n\n", tok1);
		}
		else {
			printf("%s is not a keyword.\n\n", tok1);
		}
	}

	fclose(fp);
	Free();
	return 0;
}