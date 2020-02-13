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
	//next�� ���Ḯ��Ʈ�� ���� ����̴ϱ� �����ͷ�!
	Node* next;

	//data�� �ڷḦ ��� �κ��̶� �����͸� �����ϰ� �׳� ����ü�� �����߾�!
	Data data;
};

Node* head;

void Free() {
	//curr�� ���Ḯ��Ʈ ó������ ������ �ؾ��ϴ� curr�� head�� ����Ų��
	Node* curr = head;

	//curr�� null �� �� ����!
	while (curr != NULL) {      //�����Ҵ� ���� �ݺ���   

								//�Ҵ����� ����ü�迭�� �����ϴ� �κ��̴ϱ� head�� ����ص� ����! (���� ������� �Ŵϱ�!)
								//a-b-c-... ���� head�� a���� b�� �̵�
		head = head->next;

		//ó���� curr�� ���� head (a)�� ����Ű�� �ִ�.
		//a�Ҵ� ����
		free(curr);

		//���� head�� a���� b�� �̵������� curr�� b�� ����Ų��.
		curr = head;
	}
}

void create() {
	//���Ḯ��Ʈ�� �Ӹ� ���� head�� �׻� ����
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

	//������ �޴� char�� �迭
	char input[512];
	Node* current = head;

	while (fgets(input, 512, fp) != NULL) {   //total�� �л� ���� ����
											  //data �ޱ�
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

	//curr�� next�� null �� �� ����
	//������ curr�� next�� null�̴�
	while (curr->next != NULL) {
		//curr ������ ���
		printf("%s\t %s\t %s\t %s\t %s\t %s\t %s\n", curr->data.name, curr->data.sex, 
			curr->data.live, curr->data.major, curr->data.score, 
			curr->data.height, curr->data.weight);

		//curr�� ���� curr->next�� �̵�
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
	//curr�� ���Ḯ��Ʈ ó������ ������ �ؾ��ϴ� curr�� head�� ����Ų��
	Node* curr = head;

	if (head->data.name == name) {
		Node* nodeTmp = head;
		head = head->next;
		free(nodeTmp);
		return;
	}

	//curr�� next�� null �� �� ����
	//������ curr�� next�� null�̴�
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