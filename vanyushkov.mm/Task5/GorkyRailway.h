#pragma once
#include <iostream>

// �����
constexpr int LASTOCHKA = 100;
constexpr int RESERVED = 27; // 54
constexpr int COUPE = 18;    // 36
constexpr int SV = 18;
// ����
constexpr float priceL = 705.25;
constexpr float firmS  = 752.50;
constexpr float firmC  = 698.00;
constexpr float firmR  = 524.75;
constexpr float fastC  = 711.25;
constexpr float fastR  = 542.50;


class GorkyRailway
{
	int lastochka   [3][8]; // �����, �����

	int firmSV      [2];    // �����
	int firmCoupe   [6][2]; // �����, �����
	int firmReserved[4][2]; // �����, �����

	int fastCoupe   [4][2]; // �����, �����
	int fastReserved[8][2]; // �����, �����

public:
	GorkyRailway();
	int carReservate(const int train, const int passengers);
	void typeCar(const int train, const int passengers, const int carriage, int** seats);
	float price(const int train, const int carriage, const int passengers);
};

