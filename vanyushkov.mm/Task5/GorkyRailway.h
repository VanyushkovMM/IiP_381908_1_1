#pragma once
#include <iostream>

// Места
constexpr int LASTOCHKA = 100;
constexpr int RESERVED = 27; // 54
constexpr int COUPE = 18;    // 36
constexpr int SV = 18;
// Цены
constexpr float priceL = 705.25;
constexpr float firmS  = 752.50;
constexpr float firmC  = 698.00;
constexpr float firmR  = 524.75;
constexpr float fastC  = 711.25;
constexpr float fastR  = 542.50;


class GorkyRailway
{
	int lastochka   [3][8]; // Поезд, вагон

	int firmSV      [2];    // Вагон
	int firmCoupe   [6][2]; // Вагон, место
	int firmReserved[4][2]; // Вагон, место

	int fastCoupe   [4][2]; // Вагон, место
	int fastReserved[8][2]; // Вагон, место

public:
	GorkyRailway();
	int carReservate(const int train, const int passengers);
	void typeCar(const int train, const int passengers, const int carriage, int** seats);
	float price(const int train, const int carriage, const int passengers);
};

