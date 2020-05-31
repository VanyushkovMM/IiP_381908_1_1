#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
class Passenger
{
	std::string surname;    // Фамилия
	std::string name;       // Имя
	std::string patronymic; // Отчество
	std::string date;       // Дата отправления
	std::string depTime;    // Время отправления
	std::string arrTime;    // Время прибытия
	int train;              // Номер поезда
	int carriage;           // Номер вагона
	int typeCar;            // Тип вагона
	int seat;               // Место
	std::string departure;  // Станция отправления
	std::string arrival;    // Станция прибытия

public:
	Passenger(const std::string surname = "", const std::string name = "", const std::string patronymic = "");
	Passenger(const Passenger& passenger);

	Passenger& operator= (const Passenger& passenger);
	bool operator== (const Passenger& passenger);
	void newSeatInfo(const int train, const std::string depTime, const std::string arrTime, const int carriage, const int typeCar,
		const int seat, const std::string departure, const std::string arrival, const std::string date);

	// Ввод-вывод консоли
	friend std::istream& operator>> (std::istream& stream, Passenger& passenger);
	friend std::ostream& operator<< (std::ostream& stream, const Passenger& passenger);
};

