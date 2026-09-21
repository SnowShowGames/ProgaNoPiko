#include <iostream>
#include <clocale>
#include <windows.h>
#include <string>
#include <fstream>

using namespace std;

struct Person
{
	char name[20];
	int weight;
	int height;
}B;

int main()
{
	setlocale(LC_ALL, "RUS");
	int handshake;
	long size_pred;
	ifstream fileRequest;
	ofstream fileAnswer;
	const char* nameR = "C:/REQUEST.bin";
	const char* nameA = "C:/ANSWER.bin";
	cout << "Server online :)" << endl;
	fileRequest.open(nameR, ios::binary);
	fileRequest.seekg(0, ios::end);
	size_pred=fileRequest.tellg();
	fileRequest.close();
	while (true)
	{
		fileRequest.open(nameR, ios::binary);
		fileRequest.seekg(0, ios::end);
		while (size_pred >= fileRequest.tellg())
		{
			Sleep(100);
			fileRequest.seekg(0, ios::end);
		}
		fileRequest.seekg(size_pred, ios::beg);
		fileRequest.read((char*)&B, sizeof(B));
		size_pred = fileRequest.tellg();
		fileRequest.close();

		double IMT = B.weight / (0.01 * B.height) / (0.01 * B.height);
		if (18.5 <= IMT && IMT < 25) handshake = 1;
		if (18.5 > IMT) handshake = 0;	
		if (IMT > 25) handshake = 2;

		fileAnswer.open(nameA,ios::binary | ios::app);
		fileAnswer.write((char*)&handshake, sizeof(handshake));
		fileAnswer.close();
	}
}
