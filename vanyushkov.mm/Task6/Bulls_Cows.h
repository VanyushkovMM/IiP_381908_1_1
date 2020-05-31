#pragma once
#include <string>
#include <ctime>
#include <cstdlib>

class Bulls_Cows
{
	int* number; // ������������ �����
	int length;  // ���������� �������� � �����

public:
	Bulls_Cows();  // �����������
	~Bulls_Cows(); // ����������

	// ����� ����� (� ����������� ���� ����� ����� 4)
	bool newNumber(const int length = 4); 

	// �������� ���������� ����� �������������
	bool checkCorrect(const std::string num); 

	// �������� �� ����� ���� � ������� ���������� ����� � �����
	bool checkBullCow(std::string num, int& bull, int& cow); 
};
