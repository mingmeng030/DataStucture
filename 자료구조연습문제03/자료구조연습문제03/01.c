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

int count = 0;
int n;
Data* total;

void process_create() {	//동적할당 함수
	total=(Data*)malloc(sizeof(Data) * 100);
}

void sort() {	//swap을 이용한 오름차순 정렬 함수
	for (int i = 0; i < count; i++) {
		for (int j = 0; j < count - 1; j++) {
			if (strcmp(total[j].name, total[j + 1].name) > 0) {

				Data tmp = total[j];
				total[j] = total[j + 1];
				total[j + 1] = tmp;
			}
		}
	}
}

void process_load(char *file) {	//파일에서 정보를 불러와 저장하는 load 함수
	FILE *fp1 = fopen(file, "r");
	Data list;
	char str[512];

	while (fgets(str, 512, fp1) != NULL) {	//total에 학생 정보 저장
		sscanf(str, "%s%s%s%s%s%s%s", total[count].name, total[count].sex, total[count].live, 
			total[count].major, total[count].score, total[count].height, total[count].weight);

		count++;
	}
	sort();
}

void process_insert(char insertName[32], char insertSex[32], char insertLive[32], 
	char insertMajor[32], char insertScore[32], char insertHeight[32], char insertWeight[32]) {

	strcpy(total[count].name, insertName);
	strcpy(total[count].sex, insertSex);
	strcpy(total[count].live, insertLive);
	strcpy(total[count].major, insertMajor);
	strcpy(total[count].score, insertScore);
	strcpy(total[count].height, insertHeight);
	strcpy(total[count].weight, insertWeight);

	count++;
	sort();
}

void process_delete(char *delete){
		for (int i = 0; i < count; i++) {
			if (strcmp(total[i].name, delete) == 0) {
				for (int j = i; j < count - 1; j++) {
					total[j] = total[j + 1];
				}
				count--;
				printf("delete %s\n\n", delete);
				return;
			}
		}
	}

void process_search(char *search) {
	for (int i = 0; i < count; i++) {
		if (strcmp(total[i].name, search) == 0) {
			printf("%s %s %s %s %s %s %s\n\n",
				total[i].name, total[i].sex, total[i].live, total[i].major, 
				total[i].score, total[i].height, total[i].weight);
			return;
		}
	}
	printf("%s 은(는) 파일에 없음.\n\n", search);
}

void  process_print() {
	int i;
	for (i = 0; i< count; i++)
		printf("%3s\t %3s\t %3s\t %3s\t %3s\t %3s\t %3s\n", 
			total[i].name, total[i].sex, total[i].live, total[i].major,
			total[i].score, total[i].height, total[i].weight);
}

int main(void) {
	FILE *fp = fopen("input.txt", "r+t");
	char input[512];
	char tok1[32], tok2[32], tok3[32], tok4[32], tok5[32], tok6[32], tok7[32], tok8[32], tok9[32];

	while (fgets(input, 512, fp) != NULL) {
		sscanf(input, "%s %s %s %s %s %s %s %s %s", tok1, tok2, tok3, tok4, tok5, tok6, tok7, tok8, tok9);
		if (strcmp(tok1, "CREATE") == 0) {
			process_create(total);
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "LOAD") == 0) {
			process_load(tok2);
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "PRINT") == 0) {
			process_print();
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "INSERT") == 0) {
			process_insert(tok2, tok3, tok4, tok5, tok6, tok7, tok8);
			printf("%s done=========================================\n\n", tok1);
		}
		else if(strcmp(tok1, "DELETE") == 0) {
			process_delete(tok2);
			printf("%s done=========================================\n\n", tok1);
		}
		else if (strcmp(tok1, "SEARCH") == 0) {
			process_search(tok2);
			printf("%s done=========================================\n\n", tok1);
		}
		else {
			printf("%s is not a keyword.\n\n", tok1);
		}
	}

	fclose(fp);
	free(total);

	return 0;
}