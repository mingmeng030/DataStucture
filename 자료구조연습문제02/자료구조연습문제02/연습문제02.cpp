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

	//클래스의 멤버함수,메소드 선언
};

void Data::Read(ifstream &fp, int count) {		//파일 읽기 메소드 정의
	if (!fp.is_open()) {
		cout << "파일 열기 실패";
		exit(1);
	}
}

void Data::Show(ifstream &fp, Data &student){	//파일 출력 메소드 정의
	while (!fp.eof()) {
		fp >> name;
		fp >> gender;
		fp >> city;
		fp >> major;
		fp >> score;
		fp >> height;
		fp >> weight;
		//fp에 자료 저장
		cout << name << "\t" << gender << "\t" << city << "\t" << major << "\t" 
			<< score << "\t" << height << "\t" << weight << endl;
		//한 줄 씩 읽고 한 줄 씩 출력
	}
	fp.close();	//파일 닫기
}

int Data::Count(ifstream &fp) {//줄 수 세기
	int count = 0;
	char temp[128];
	while (!fp.eof()) {
		fp.getline(temp, 128);
		count++;
	}
	cout <<"파일의 총 줄 수:"<< count << endl<<endl;
	fp.seekg(0, ios::beg);	//파일 끝까지 탐색 후 맨 앞으로 이동
	return count;
}

int main() {
	ifstream fp("list.txt",ios::in);	//파일 불러오기

	Data p;	//클래스 p 생성
	int count = p.Count(fp);	//int형 변수 count에 Count 함수를 통해 파일의 줄 수를 저장
	
	Data *student;
	student=new Data[count];	//클래스 student 선언, 동적할당

	p.Read(fp, count); //파일 읽기 메소드
	p.Show(fp, p);		//파일 출력 메소드

	delete[] student;	//동적할당 해제
	printf("동적할당해제!\n");

	return 0;
}