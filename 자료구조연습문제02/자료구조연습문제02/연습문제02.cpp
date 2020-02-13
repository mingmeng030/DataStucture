#include <iostream>
#include <fstream>
using namespace std;

class Data {
private:
	char name[10];
	char gender[10];
	char city[20];
	char major[20];
	float score;
	int height;
	int weight;
public:
	void Read(ifstream &fp,int count);
	int Count(ifstream &fp);
	void Show(ifstream &fp, Data &student);

	//Ŭ������ ����Լ�,�޼ҵ� ����
};

void Data::Read(ifstream &fp, int count) {		//���� �б� �޼ҵ� ����
	if (!fp.is_open()) {
		cout << "���� ���� ����";
		exit(1);
	}
}

void Data::Show(ifstream &fp, Data &student){	//���� ��� �޼ҵ� ����
	while (!fp.eof()) {
		fp >> name;
		fp >> gender;
		fp >> city;
		fp >> major;
		fp >> score;
		fp >> height;
		fp >> weight;
		//fp�� �ڷ� ����
		cout << name << "\t" << gender << "\t" << city << "\t" << major << "\t" 
			<< score << "\t" << height << "\t" << weight << endl;
		//�� �� �� �а� �� �� �� ���
	}
	fp.close();	//���� �ݱ�
}

int Data::Count(ifstream &fp) {//�� �� ����
	int count = 0;
	char temp[128];
	while (!fp.eof()) {
		fp.getline(temp, 128);
		count++;
	}
	cout <<"������ �� �� ��:"<< count << endl<<endl;
	fp.seekg(0, ios::beg);	//���� ������ Ž�� �� �� ������ �̵�
	return count;
}

int main() {
	ifstream fp("list.txt",ios::in);	//���� �ҷ�����

	Data p;	//Ŭ���� p ����
	int count = p.Count(fp);	//int�� ���� count�� Count �Լ��� ���� ������ �� ���� ����
	
	Data *student;
	student=new Data[count];	//Ŭ���� student ����, �����Ҵ�

	p.Read(fp, count); //���� �б� �޼ҵ�
	p.Show(fp, p);		//���� ��� �޼ҵ�

	delete[] student;	//�����Ҵ� ����
	printf("�����Ҵ�����!\n");

	return 0;
}