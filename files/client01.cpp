#include <iostream>
#include <clocale>
#include <windows.h>
#include <fstream>

using namespace std;

struct Person
{
	char name[20];
	int height;
	int weight;
}A;

void main()
{
	setlocale(LC_ALL, "RUS");
	const char* nameR = "C:/REQUEST.bin";
	const char* nameA = "C:/ANSWER.bin";

	ofstream file_REQ;
	ifstream file_ANS;
	long pred_size;
	int answer;

	while (true)
	{
		cout << "Введите запрос: Фамилия Рост Вес" << endl;
		cin >> A.name >> A.height >> A.weight;
		cout << A.name << A.height << A.weight;
		file_REQ.open(nameR, ios::binary | ios::app);
		file_REQ.write((char*)&A, sizeof(A));
		file_REQ.close();

		//ОТВЕТ ОТ СЕРВЕРА
		file_REQ.open(nameA,ios::binary);
		file_ANS.seekg(0, ios::end);
		pred_size = file_ANS.tellg();
		while (pred_size >= file_ANS.tellg())
		{
			Sleep(100);
			file_ANS.seekg(0,ios::end);
		}
		file_ANS.seekg(0, ios::beg);
		file_ANS.read((char*)&answer, sizeof(answer));
		file_ANS.close();


		switch (answer) {
		case 0: { cout << "Недостаток веса \n"; break; }
		case 1: { cout << "Норма веса \n"; break; }
		case 2: { cout << "Избыток веса \n"; break; }
			  //default;
		}
	}	
}
