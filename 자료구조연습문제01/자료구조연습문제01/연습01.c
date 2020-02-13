#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct data{
	char name[20];
	char sex;
	char live[20];
	char major[20];
	float score;
	int height, weight;
}Data;


void Data_input(FILE *fp, Data *total, int count){
	for (int i = 0; i < count; i++) {
		if (feof(fp))
			break;
		fscanf(fp, "%s %c %s %s %f %d %d", total[i].name, &total[i].sex, total[i].live, total[i].major, &total[i].score, &total[i].height, &total[i].weight);

	}
}

void Print(int count, Data* total) {
	int i;
	for (i = 0; i<count; i++)
		printf("%3s\t %3c\t %3s\t %3s\t %3.1f\t %3d\t %3d\n", total[i].name, total[i].sex, total[i].live, total[i].major, total[i].score, total[i].height, total[i].weight);
}

int Count(Data* fp) {
	char str[256];
	int count = 0;

	while (fgets(str, 256, fp) != NULL)
		count++;

	fseek(fp, 0, SEEK_SET);

	return count;
}
int main(void){
	FILE *fp=fopen("list.txt", "r");
	if (fp==NULL) {
		printf("파일을 찾을 수 없습니다.\n");
		return 0;
	}

	int count = Count(fp);
	Data* total=(Data*)malloc(sizeof(Data)*count);

	Data_input(fp, total, count);
	Print(count, total);

	fclose(fp);
	free(total);

	
	return 0;
}