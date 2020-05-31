#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
class Passenger
{
	std::string surname;    // �������
	std::string name;       // ���
	std::string patronymic; // ��������
	std::string date;       // ���� �����������
	std::string depTime;    // ����� �����������
	std::string arrTime;    // ����� ��������
	int train;              // ����� ������
	int carriage;           // ����� ������
	int typeCar;            // ��� ������
	int seat;               // �����
	std::string departure;  // ������� �����������
	std::string arrival;    // ������� ��������

public:
	Passenger(const std::string surname = "", const std::string name = "", const std::string patronymic = "");
	Passenger(const Passenger& passenger);

	Passenger& operator= (const Passenger& passenger);
	bool operator== (const Passenger& passenger);
	void newSeatInfo(const int train, const std::string depTime, const std::string arrTime, const int carriage, const int typeCar,
		const int seat, const std::string departure, const std::string arrival, const std::string date);

	// ����-����� �������
	friend std::istream& operator>> (std::istream& stream, Passenger& passenger);
	friend std::ostream& operator<< (std::ostream& stream, const Passenger& passenger);
};

