#include <Windows.h>
#include <clocale>
#include <fstream>>
#include <iostream>

using namespace std;

struct Student
{
	char name[25];
	int marks[4];
}B;

struct Responce 
{
	int status;
	int debts;
}resp;

int main()
{
	setlocale(LC_ALL, "RUS");
	const char* nameReq = "E:/REQUEST_DEK.bin";
	const char* nameAns = "E:/ANSWER_DEK.bin";

	ofstream prepareReq(nameReq, ios::binary | ios::app);
	prepareReq.close();

	ifstream fileRequest;
	ofstream fileAnswer;
	int stipendType;

	fileRequest.open(nameReq, ios::binary);
	fileRequest.seekg(0, ios::end);
	long size_pred = fileRequest.tellg();
	fileRequest.close();

	cout << "Server online :)" << endl;

	while (true)
	{
		fileRequest.open(nameReq, ios::binary);
		fileRequest.seekg(0, ios::end);

		while (size_pred >= fileRequest.tellg())
		{
			Sleep(100);
			fileRequest.clear();
			fileRequest.seekg(0, ios::end);
		}

		fileRequest.seekg(size_pred, ios::beg);
		fileRequest.read((char*)&B, sizeof(B));
		size_pred = fileRequest.tellg();
		fileRequest.close();

		bool hasThreesOrFails = false;
		bool hasFours = false;
		int TwosCNT = 0;

		for (int i = 0; i < 4; i++)
		{
			if (B.marks[i] == 2) {
				TwosCNT++;
			}
			if (B.marks[i] <= 3) {
				hasThreesOrFails = true;
			}
			if (B.marks[i] == 4) {
				hasFours = true;
			}
		}

		resp.debts = TwosCNT;

		if (hasThreesOrFails) {
			stipendType = 0;
		}
		else if (hasFours) {
			stipendType = 1;
		}
		else {
			stipendType = 2;
		}

		fileAnswer.open(nameAns, ios::binary | ios::app);
		fileAnswer.write((char*)&stipendType, sizeof(stipendType));
		fileAnswer.write((char*)&resp, sizeof(resp));
		fileAnswer.close();

		cout << "Обработан студент: " << B.name
			<< " | Оценки: " << B.marks[0] << " " << B.marks[1] << " " << B.marks[2] << " " << B.marks[3]
			<< " | Долгов у студента: " << resp.debts
			<< " | Код ответа: " << stipendType << endl;
	}

	return 0;
}
