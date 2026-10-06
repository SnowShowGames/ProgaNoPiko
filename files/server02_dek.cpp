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

int main()
{
	setlocale(LC_ALL, "RUS");
	const char* nameReq = "D:/REQUEST_DEK.bin";
	const char* nameAns = "D:/ANSWER_DEK.bin";

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

		// Ожидание появления новых данных от клиента
		while (size_pred >= fileRequest.tellg())
		{
			Sleep(100);
			fileRequest.clear(); // Сброс флагов ошибок (в т.ч. EOF)
			fileRequest.seekg(0, ios::end);
		}

		// Чтение записи студента
		fileRequest.seekg(size_pred, ios::beg);
		fileRequest.read((char*)&B, sizeof(B));
		size_pred = fileRequest.tellg();
		fileRequest.close();

		// Проверка оценок и определение типа стипендии
		bool hasThreesOrFails = false;
		bool hasFours = false;

		for (int i = 0; i < 4; i++)
		{
			if (B.marks[i] <= 3) {
				hasThreesOrFails = true;
			}
			if (B.marks[i] == 4) {
				hasFours = true;
			}
		}

		if (hasThreesOrFails) {
			stipendType = 0; // Нет стипендии (есть тройки или двойки)
		}
		else if (hasFours) {
			stipendType = 1; // Обычная стипендия (учится на 4 и 5)
		}
		else {
			stipendType = 2; // Повышенная стипендия (все 5)
		}

		// Запись ответа для клиента
		fileAnswer.open(nameAns, ios::binary | ios::app);
		fileAnswer.write((char*)&stipendType, sizeof(stipendType));
		fileAnswer.close();

		cout << "Обработан студент: " << B.name
			<< " | Оценки: " << B.marks[0] << " " << B.marks[1] << " " << B.marks[2] << " " << B.marks[3]
			<< " | Код ответа: " << stipendType << endl;
	}

	return 0;
	}

